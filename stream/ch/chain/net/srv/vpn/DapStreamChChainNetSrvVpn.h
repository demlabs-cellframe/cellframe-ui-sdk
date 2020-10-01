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
#pragma once
#include "DapChBase.h"
#include "DapSession.h"

//#include "DapSockForwPacket.h"
#include "DapStreamChChainNetSrv.h"
#include "DapStreamChChainVpnPacket.h"
#include "DapTunNative.h"
#include "DapStreamer.h"

#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>



#define STREAM_SF_PACKET_OP_CODE_CONNECTED 0x000000a9
#define STREAM_SF_PACKET_OP_CODE_CONNECT 0x000000aa
#define STREAM_SF_PACKET_OP_CODE_DISCONNECT 0x000000ab
#define STREAM_SF_PACKET_OP_CODE_SEND 0x000000ac
#define STREAM_SF_PACKET_OP_CODE_RECV 0x000000ad
#define STREAM_SF_PACKET_OP_CODE_PROBLEM 0x000000ae

#define STREAM_SF_PROBLEM_CODE_NO_FREE_ADDR 0x00000001
#define STREAM_SF_PROBLEM_CODE_TUNNEL_DOWN  0x00000002
#define STREAM_SF_PROBLEM_CODE_PACKET_LOST  0x00000003

#define STREAM_SF_PACKET_OP_CODE_RAW_L3 0x000000b0
#define STREAM_SF_PACKET_OP_CODE_RAW_L2 0x000000b1
#define STREAM_SF_PACKET_OP_CODE_RAW_L3_ADDR_REQUEST 0x000000b2
#define STREAM_SF_PACKET_OP_CODE_RAW_L3_ADDR_REPLY 0x000000b3
#define STREAM_SF_PACKET_OP_CODE_RAW_L3_DEST_REPLY 0x000000b4

#define STREAM_SF_PACKET_OP_CODE_RAW_SEND 0x000000bc
#define STREAM_SF_PACKET_OP_CODE_RAW_RECV 0x000000bd

#define DAP_CHAIN_NET_SRV_VPN_ID


namespace Dap {
    namespace Chain {
        namespace NetSrv {
            const Uid UID_VPN = 0x0000000000000001;
        }
    }
    namespace Stream {

        class ChChainNetSrvVpn : public DapChBase
        {
            Q_OBJECT
        public:
        private:
            // DATAS
            DapStreamer * m_streamer;
            DapSession * m_mainDapSession;

            QMap<int, QTcpSocket* > m_socketsIn;
            QMap<int, QTcpServer* > m_servs;
            QMap<int, QString > m_servsRemoteAddr;
            QMap<int, quint16 > m_servsRemotePort;

            QMap<int, QTcpSocket* > m_socksIn;
            QMap<int, QTcpSocket* > m_socksOut;

            DapTunNative * tun;
            // METHODS
            QString m_addr, m_gw;
            QTcpServer *m_fdListener;
        private slots:
            void onFwServerConnected();
            void onFwClientReadyRead();
            void onFwClientDisconnected();

        signals:
            void bytesRead(int);
            void bytesWrite(int);

            void fwdDisconnected(int sockServ, int sockClient);
            void usrMsg(QString);
            void sigPacketRead();
            void sigPacketWrite();

            void sigTunNativeCreate();
            void sigNativeDestroy();

        public:
            ChChainNetSrvVpn(DapStreamer * a_streamer, DapSession * mainDapSession);

            bool isTunCreated(){return tun->isCreated();}
            void addNewUpstreamRoute(const QString &a_dest) {
                tun->addNewUpstreamRoute(a_dest);
            }

            QString upstreamAddress(){return tun->upstreamAddress();}

            void tunCreate (const QString& a_addr, const QString& a_gw);
            void workerStart(int a_tunSocket);
            int tunSocket();
            quint16 addForwarding(const QString remoteAddr, quint16 remotePort, quint16 localPort);
            void delForwarding(int sockId);
            void delForwardingAll();

            DapStreamer * streamer(){ return m_streamer; }
        signals:

            void netConfigReceived(QString,QString);
            void netConfigReceivedSame();
            void tunCreated();
            void tunDestroyed();
            void tunError(const QString&);
            void androidPermissionDenied();
            void tunWriteData();

            void sendCmdAll(const QString&);
        public slots:
            void onPktIn(DapChannelPacket *pkt) override;
            void packetOut(Dap::Stream::Packet *pkt);

            void requestIP(quint32);
            void netConfigClear();

            void tunCreate(); // create with all predefined before values
            void tunDestroy();
            void tunStandby();
        };

    }
}
