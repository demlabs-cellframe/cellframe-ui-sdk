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
#include "dap_common.h"
#include "DapStreamChChainNetSrv.h"


// TYPE_REQUEST
typedef struct dap_stream_ch_chain_net_srv_pkt_request_hdr{
    dap_chain_net_id_t net_id;// Network id wheither to request
    dap_chain_hash_fast_t tx_cond; // Conditioned transaction with paymemt for
    dap_chain_net_srv_uid_t srv_uid;
    char token[DAP_CHAIN_TICKER_SIZE_MAX];
} DAP_ALIGN_PACKED dap_stream_ch_chain_net_srv_pkt_request_hdr_t;

typedef struct dap_stream_ch_chain_net_srv_pkt_request{
    dap_stream_ch_chain_net_srv_pkt_request_hdr_t hdr;
    uint8_t data[];
} DAP_ALIGN_PACKED dap_stream_ch_chain_net_srv_pkt_request_t;

typedef struct dap_stream_ch_chain_net_srv_pkt_success_hdr{
    uint32_t usage_id;
    dap_chain_net_id_t net_id;
    dap_chain_net_srv_uid_t srv_uid;
} DAP_ALIGN_PACKED dap_stream_ch_chain_net_srv_pkt_success_hdr_t;

typedef struct dap_stream_ch_chain_net_srv_pkt_success{
    dap_stream_ch_chain_net_srv_pkt_success_hdr_t hdr;
    uint8_t custom_data[];
} DAP_ALIGN_PACKED dap_stream_ch_chain_net_srv_pkt_success_t;

// TYPE_RESPONSE_ERROR
typedef struct dap_stream_ch_chain_net_srv_pkt_error{
    dap_chain_net_id_t net_id;
    dap_chain_net_srv_uid_t srv_uid;
    uint32_t usage_id;
    uint32_t code; // error code
} DAP_ALIGN_PACKED dap_stream_ch_chain_net_srv_pkt_error_t;

using namespace Dap;
using namespace Dap::Stream;
using namespace Dap::Chain;
using namespace Dap::Crypto;

/**
 * @brief ChChainNetSrv::ChChainNetSrv
 * @param a_streamer
 * @param a_mainDapSession
 */
ChChainNetSrv::ChChainNetSrv(DapStreamer * a_streamer, DapSession * a_mainDapSession)
                : DapChBase(nullptr, 'R'), m_streamer(a_streamer), m_mainDapSession(a_mainDapSession)
{

}

/**
 * @brief ChChainNetSrv::sendReceipt
 * @param receipt
 */
void ChChainNetSrv::sendReceipt(Chain::Receipt * receipt )
{
    sendPacket( get_id(),ChChainNetSrvPktType::SIGN_RESPONSE,receipt->value() ,receipt->size() );

    // To prevent double free
    receipt->release();
    delete receipt;
}

/**
 * @brief ChChainNetSrv::onPktIn
 * @param a_pkt
 */
void ChChainNetSrv::onPktIn(DapChannelPacket* a_pkt)
{
    switch (static_cast<ChChainNetSrvPktType>(a_pkt->hdr()->type) ) {
        case REQUEST:{
            qWarning() << "We don't serve any service so nothing todo with REQUEST. TODO: add service provide for this realization as well";
        } break;
        case SIGN_REQUEST:{
            Chain::Receipt * receipt = nullptr;
            try {
                receipt = new Chain::Receipt(a_pkt->data(), a_pkt->hdr()->size);
                emit sigReceiptToSign(receipt);
            } catch (Chain::Receipt::ThrowClass err) {
                switch (err) {
                    case Chain::Receipt::DataNull:
                        qWarning() << "Packet with receipt has NULL data";
                    break;
                    case Chain::Receipt::DataSizeWrong:
                    qWarning() << "Packet with receipt has wrong data size "<< a_pkt->hdr()->size;
                    break;
                }
            }

        } break;
        case SIGN_RESPONSE:{
            qWarning() << "We don't serve any service so nothing todo with SIG_RESPONSE. TODO: add service provide for this realization as well";
        } break;
        case RESPONSE_SUCCESS:{
            if( a_pkt->hdr()->size < sizeof(dap_stream_ch_chain_net_srv_pkt_success_hdr_t) ){
                qWarning() << "Wrong error packet data size, expected to be at least " << sizeof(dap_stream_ch_chain_net_srv_pkt_success_hdr_t);
                break;
            }
            const dap_stream_ch_chain_net_srv_pkt_success_t * l_success =
                    reinterpret_cast<const dap_stream_ch_chain_net_srv_pkt_success_t* >(a_pkt->data());
            emit sigProvideSuccess( l_success->hdr.net_id, l_success->hdr.srv_uid, l_success->hdr.usage_id );
        } break;
        case RESPONSE_ERROR:{
            const dap_stream_ch_chain_net_srv_pkt_error_t *l_err;
            if( a_pkt->hdr()->size != sizeof(*l_err) ){
                qWarning() << "Wrong error packet data size, expected to be "<<sizeof (*l_err);
                break;
            }
            l_err =reinterpret_cast<const dap_stream_ch_chain_net_srv_pkt_error_t*>(a_pkt->data());
            emit sigProvideError(l_err->net_id, l_err->srv_uid, l_err->usage_id,  l_err->code );
        } break;
        case NOTIFY_STOPPED: {
            /// TODO add usage id, net id and service id to identify what exactly was stopped
            emit sigNotifyStopped();
        } break;
        default: qWarning() << "Unknown packet type " << a_pkt->hdr()->type;
    }
}

void ChChainNetSrv::sendRequest(Chain::NetId a_netId,// Network id wheither to request
    Crypto::HashFast a_txCond, // Conditioned transaction with paymemt for
    Chain::NetSrv::Uid a_srvUid, const QString& a_token ) // Service ID
{
    dap_stream_ch_chain_net_srv_pkt_request_t * l_request =static_cast<dap_stream_ch_chain_net_srv_pkt_request_t *>(
                calloc(1,sizeof(dap_stream_ch_chain_net_srv_pkt_request_t) ) );
    l_request->hdr.net_id = a_netId.value();
    l_request->hdr.tx_cond = a_txCond.value();
    qDebug() << "2791: Service req: net_id = " << a_netId.value().uint64 << "tx_cond = " << a_txCond.value().raw;
    l_request->hdr.srv_uid = a_srvUid;
    strncpy(l_request->hdr.token, a_token.toLatin1().constData(),sizeof (l_request->hdr.token)-1);
    sendPacket( get_id(),ChChainNetSrvPktType::REQUEST,l_request,sizeof(*l_request));
    qInfo() << "Sent request for service "<<a_srvUid.toString();
}
