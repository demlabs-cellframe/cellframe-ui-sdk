/*
* Authors:
* Dmitriy Gerasimov <naeper@demlabs.net>
* Cellframe       https://cellframe.net
* DeM Labs Inc.   https://demlabs.net
* Copyright  (c) 2017-2019
* All rights reserved.

This file is part of CellFrame SDK the open source project

CellFrame SDK is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

CellFrame SDK is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with any CellFrame SDK based project.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <QtDebug>

#include "DapStreamer.h"
#include "DapStreamChChainVpnPacket.h"
#include "DapStreamChChainNetSrvVpn.h"

#if defined(Q_OS_UNIX)
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/select.h>

#elif defined(Q_OS_MACOS)
#elif defined (Q_OS_WIN)
#include <winsock2.h>
#endif

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#endif

#include <QProcess>
#include <QFile>


#include <fcntl.h>
#include <errno.h>
#include <string.h>

using namespace Dap;
using namespace Dap::Stream;

/**
 * @brief ChChainNetSrvVpn::delForwardingAll
 */
void ChChainNetSrvVpn::delForwardingAll()
{
    for (auto s : m_socketsIn)
        delete s;
    m_socketsIn.clear();

    for (auto s : m_servs)
        delete s;
    m_servs.clear();
}

/**
 * @brief ChChainNetSrvVpn::delForwarding
 * @param sockId
 */
void ChChainNetSrvVpn::delForwarding(int sockId)
{
    QTcpServer * serv = m_servs[sockId];
    if (serv) {
        m_servs.remove(sockId);
        delete serv;
    } else qDebug() << "Not found socket by id: " << sockId;
}

/**
 * @brief ChChainNetSrvVpn::onFwClientReadyRead
 */
void ChChainNetSrvVpn::onFwClientReadyRead()
{
    qDebug() << "[onFwClientReadyRead]";
    QTcpSocket * sock = qobject_cast<QTcpSocket*>(QObject::sender());
    if (sock) {
        QByteArray ba = sock->readAll();
        qDebug() << "From client's socket have read " << ba.length() << "bytes.";
        Dap::Stream::Packet* pkt = (Dap::Stream::Packet*) calloc(1, ba.length() + sizeof(pkt->header));
        memcpy(pkt->data, ba.constData(), ba.length());
        pkt->header.op_data.data_size = ba.length();
        pkt->header.op_code = STREAM_SF_PACKET_OP_CODE_SEND;
        pkt->header.socket_id = sock->socketDescriptor();
        packetOut(pkt);
    } else{
        qCritical() << "Cant cast sender() object of type "
                 <<QObject::sender()->metaObject()->className()<< " to QTcpSocket";
    }
}

/**
 * @brief ChChainNetSrvVpn::onFwClientDisconnected
 */
void ChChainNetSrvVpn::onFwClientDisconnected()
{
    QTcpSocket *sock = qobject_cast<QTcpSocket*>(QObject::sender());
    if(sock) {
        qDebug() << "Disconnected client " << sock->localAddress();
        m_socketsIn.remove(sock->socketDescriptor());

        Dap::Stream::Packet* pkt = (Dap::Stream::Packet*) calloc(1,sizeof(pkt->header) + 1);
        pkt->header.op_code = STREAM_SF_PACKET_OP_CODE_DISCONNECT;
        pkt->header.socket_id = sock->socketDescriptor();
        pkt->header.raw.data_size = 2; ///TODO prev value is 0
        packetOut(pkt);
    } else{
        qCritical() << "Cant cast sender() object of type "
                 <<QObject::sender()->metaObject()->className()<< " to QTcpSocket";
    }
}

/**
 * @brief ChChainNetSrvVpn::onFwServerConnected
 */
void ChChainNetSrvVpn::onFwServerConnected()
{
    qDebug() << "[onFwServerConnected()]";
    QTcpServer *serv = qobject_cast<QTcpServer*>(QObject::sender());
    QTcpSocket *sock;
    QByteArray remoteAddrBA;
    Dap::Stream::Packet *pkt;

    if(serv) {
        if(!serv->hasPendingConnections())
            qDebug() << "No pendidng connections on the server";
        else do {

            sock = serv->nextPendingConnection();
            remoteAddrBA = (m_servsRemoteAddr[serv->socketDescriptor()]).toLatin1();
            m_socketsIn.insert(sock->socketDescriptor(),sock);
            pkt = (Dap::Stream::Packet*) calloc(1, sizeof(pkt->header) +  remoteAddrBA.length());

            pkt->header.op_code = STREAM_SF_PACKET_OP_CODE_CONNECT;
            pkt->header.socket_id = sock->socketDescriptor();
            pkt->header.op_connect.addr_size = remoteAddrBA.length();

            memcpy(pkt->data, remoteAddrBA.constData(), pkt->header.op_connect.addr_size);

            pkt->header.op_connect.port = m_servsRemotePort[serv->socketDescriptor()];

            qDebug() << "New connection enstablished to "
                     << m_servsRemoteAddr[serv->socketDescriptor()]
                     << ":" << pkt->header.op_connect.port
                     << " addr size" << pkt->header.op_connect.addr_size;

            connect(sock, &QTcpSocket::readyRead, this, &ChChainNetSrvVpn::onFwClientReadyRead);
            connect(sock, &QTcpSocket::disconnected, this, &ChChainNetSrvVpn::onFwClientDisconnected);

            packetOut(pkt);

        } while( serv->hasPendingConnections() );
    } else
        qDebug() << "Can't cast object to QTcpServer";
}

/**
 * @brief ChChainNetSrvVpn::addForwarding
 * @param remoteAddr
 * @param remotePort
 * @param localPort
 * @return
 */
quint16 ChChainNetSrvVpn::addForwarding(const QString remoteAddr, quint16 remotePort, quint16 localPort)
{
    qDebug() << "addForwarding " << QString("127.0.0.1:%1 => %2:%3")
                                                                    .arg(localPort)
                                                                    .arg(remoteAddr)
                                                                    .arg(remotePort);
    QTcpServer *server = new QTcpServer;
    if(server->listen(QHostAddress("127.0.0.1"), localPort)) {
        qDebug() << "Sucessfully set up " << localPort << " to listening";
        m_servs.insert(server->socketDescriptor(), server);
        m_servsRemoteAddr.insert(server->socketDescriptor(), remoteAddr);
        m_servsRemotePort.insert(server->socketDescriptor(), remotePort);
        connect(server, &QTcpServer::newConnection, this, &ChChainNetSrvVpn::onFwServerConnected);
        connect(server, &QTcpServer::acceptError,[=]{
           qDebug() << "QTcpServer::acceptError() "<< server->errorString() ;
        });
        return server->serverPort();
    } else {
        qWarning() << "Can't open local port for listening";
        emit error(QString("Can't open local port %1").arg(localPort));
        delete server;
        return 0;
    }
}

/**
 * @brief ChChainNetSrvVpn::ChChainNetSrvVpn
 */
ChChainNetSrvVpn::ChChainNetSrvVpn(DapStreamer * a_streamer, DapSession * mainDapSession)
    :DapChBase(nullptr, 'S'), m_streamer(a_streamer), m_mainDapSession(mainDapSession)
{
    tun = new DapTunNative();
    m_fdListener = nullptr;
    connect(tun, &DapTunNative::created, this, &ChChainNetSrvVpn::tunCreated);
    connect(tun, &DapTunNative::destroyed, this, &ChChainNetSrvVpn::tunDestroyed);
    connect(tun, &DapTunNative::error , this, &ChChainNetSrvVpn::tunError);
    connect(tun, &DapTunNative::packetOut, this, &ChChainNetSrvVpn::packetOut);
    connect(tun, &DapTunNative::sendCmd, this, &ChChainNetSrvVpn::sendCmdAll);
    connect(tun, &DapTunNative::bytesRead, this, &ChChainNetSrvVpn::bytesRead);
    connect(tun, &DapTunNative::bytesWrite, this, &ChChainNetSrvVpn::bytesWrite);
    connect(tun, &DapTunNative::nativeCreateRequest, this, &ChChainNetSrvVpn::sigTunNativeCreate);
    connect(tun, &DapTunNative::nativeDestroyRequest, this, &ChChainNetSrvVpn::sigNativeDestroy);
}

/**
 * @brief ChChainNetSrvVpn::packetOut
 * @param pkt
 */
void ChChainNetSrvVpn::packetOut(Dap::Stream::Packet *pkt)
{
    DapChannelPacketHdr* hdr= (DapChannelPacketHdr *) ::calloc(1, sizeof(DapChannelPacketHdr));
    hdr->id='S';
    hdr->type=0x00;
    hdr->size=sizeof(pkt->header);
    switch(pkt->header.op_code){
        case STREAM_SF_PACKET_OP_CODE_SEND:
        case STREAM_SF_PACKET_OP_CODE_RECV:
        case STREAM_SF_PACKET_OP_CODE_RAW_SEND:
        case STREAM_SF_PACKET_OP_CODE_RAW_RECV:
        case STREAM_SF_PACKET_OP_CODE_RAW_L3_ADDR_REPLY:
        case STREAM_SF_PACKET_OP_CODE_RAW_L3:
        case STREAM_SF_PACKET_OP_CODE_RAW_L2:
        case STREAM_SF_PACKET_OP_CODE_RAW_L3_ADDR_REQUEST:
            hdr->size+=pkt->header.op_data.data_size;
        break;
    default:
        qWarning() << "Unknown packet code" << pkt->header.op_code;
    }
    emit pktChOut(hdr,pkt);
}

/**
 * @brief DapChSockForw::requestIP
 */
void ChChainNetSrvVpn::requestIP(quint32 a_usageId)
{
    emit netConfigRequested();
    Dap::Stream::Packet * pktOut = reinterpret_cast<Dap::Stream::Packet*>(::calloc(1 ,sizeof(pktOut->header)));
    pktOut->header.op_code=STREAM_SF_PACKET_OP_CODE_RAW_L3_ADDR_REQUEST;
    pktOut->header.usage_id = a_usageId;
    qInfo() << "Request for IP with usage_id: " << pktOut->header.usage_id;
    packetOut(pktOut);
    emit ipRequested();
}

/**
 * @brief DapChSockForw::netConfigClear
 */
void ChChainNetSrvVpn::netConfigClear()
{
    m_addr.clear();
    m_gw.clear();
    emit netConfigCleared();
}

/**
 * @brief ChChainNetSrvVpn::tunCreate
 * @param a_addr
 * @param a_gw
 */
void ChChainNetSrvVpn::tunCreate(const QString &a_addr, const QString &a_gw)
{
    m_addr = a_addr;
    m_gw = a_gw;
    tun->create(a_addr,
                a_gw,
                m_mainDapSession->upstreamAddress(),
                m_mainDapSession->upstreamPort(),
                streamer()->upstreamSocket());
}

/**
 * @brief ChChainNetSrvVpn::tunCreate
 */
void ChChainNetSrvVpn::tunCreate()
{
    qDebug()<< "tunCreate()";
    tun->create(m_addr,
                m_gw,
                m_mainDapSession->upstreamAddress(),
                m_mainDapSession->upstreamPort(),
                streamer()->upstreamSocket());
#ifdef ANDROID
    jint tunSocket = 0;
    for (; tunSocket == 0;) {
        QThread::msleep(1000);
        tunSocket = QtAndroid::androidService().callMethod<jint>("getTunSocket");
    }
    qInfo() << "Socket num: " << tunSocket;
    workerStart(tunSocket);
#else
    tun->workerStart();
#endif
}

//

void ChChainNetSrvVpn::tunDestroy()
{
    tun->destroy();
}

/**
 * @brief ChChainNetSrvVpn::afterTunCreate
 * @param a_tunSocket
 */
void ChChainNetSrvVpn::workerStart(int a_tunSocket)
{
    qDebug() << "set tun socket: " << a_tunSocket;
    tun->setTunSocket(a_tunSocket);
    tun->workerStart(); // start loop
}

/**
 * @brief ChChainNetSrvVpn::onPktIn
 * @param pkt
 */
void ChChainNetSrvVpn::onPktIn(DapChannelPacket* pkt)
{
    // qDebug() << "onPktIn: id ="<<pkt->hdr()->id << " type = "<< pkt->hdr()->type<< " ch_data_size = "<<pkt->hdr()->size;
    Dap::Stream::Packet * pktSF=(Dap::Stream::Packet *) pkt->data();
    //qDebug() << " onPktIn: SampSFPacket op_code ="<< pktSF->header.op_code;
    switch(pktSF->header.op_code){
        case STREAM_SF_PACKET_OP_CODE_SEND:
        case STREAM_SF_PACKET_OP_CODE_CONNECT:{
            qDebug() << "Backforward connection are not processed";
        } break;
        case STREAM_SF_PACKET_OP_CODE_DISCONNECT:{

            break;
            QTcpSocket *sc=m_socketsIn[pktSF->header.socket_id];
            if (sc) {
                m_socketsIn.remove(pktSF->header.socket_id);
                sc->close();
            } else {
                qDebug() <<" Unknown socket_id "<<pktSF->header.socket_id;
            }
        } break;
        case STREAM_SF_PACKET_OP_CODE_RECV:{
            QTcpSocket *sc=m_socketsIn[pktSF->header.socket_id];
            if (sc) {
                sc->write((const char*)pktSF->data, pktSF->header.op_data.data_size);
            } else {
                qDebug() <<" Unknown socket_id "<<pktSF->header.socket_id;
            }
        } break;
        case STREAM_SF_PACKET_OP_CODE_RAW_L3_ADDR_REPLY:{
            quint32 l_addr,l_gw;
            ::memcpy(&l_addr, pktSF->data,sizeof (l_addr));
            ::memcpy(&l_gw, pktSF->data+sizeof (l_addr),sizeof (l_addr));
            QString new_addr    = QHostAddress(  ntohl(l_addr) ).toString();
            QString new_gw      = QHostAddress( ntohl ( l_gw )).toString();
            if (m_addr == new_addr && new_gw == m_gw) {
                qDebug() << "Net config is the same, we don't touch Tun";
                emit netConfigReceivedSame();
            } else {
                m_addr = new_addr;
                m_gw = new_gw;
                emit netConfigReceived(m_addr,m_gw);
            }
        } break;
        case STREAM_SF_PACKET_OP_CODE_RAW_RECV:{
            pkt->unleashData(); // Uleash *data section from pkt object
            tun->tunWriteData(pktSF);
        }break;
        /*case STREAM_SF_PACKET_OP_CODE_CONNECTED:
            qDebug() << "[DapChSockForw] Get connected packet."; // Repsonse to the connect Packet
            tcp_sock = m_socketsIn[sockForwPacket->header.socket_id];
            if(tcp_sock)
                connect(tcp_sock, &QTcpSocket::readyRead, this, &DapChSockForw::onClientReadyRead);
            else
                qWarning() << ("[DapChSockForw] onPktIn() Not Find Socket by socket_id!");
            break;*/
    }

    delete pkt;
}







