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
#include "DapStreamChChainNetSrv.h"

// TYPE_REQUEST
typedef struct dap_stream_ch_chain_net_srv_pkt_request_hdr{
    dap_chain_net_id_t net_id;// Network id wheither to request
    dap_chain_hash_fast_t tx_cond; // Conditioned transaction with paymemt for
    dap_chain_net_srv_uid_t srv_uid;
} DAP_ALIGN_PACKED dap_stream_ch_chain_net_srv_pkt_request_hdr_t;

typedef struct dap_stream_ch_chain_net_srv_pkt_request{
    dap_stream_ch_chain_net_srv_pkt_request_hdr_t hdr;
    uint8_t data[];
} DAP_ALIGN_PACKED dap_stream_ch_chain_net_srv_pkt_request_t;

typedef struct dap_stream_ch_chain_net_srv_pkt_success_hdr{
    uint32_t usage_id;
} DAP_ALIGN_PACKED dap_stream_ch_chain_net_srv_pkt_success_hdr_t;

typedef struct dap_stream_ch_chain_net_srv_pkt_success{
    dap_stream_ch_chain_net_srv_pkt_success_hdr_t hdr;
    uint8_t custom_data[];
} DAP_ALIGN_PACKED dap_stream_ch_chain_net_srv_pkt_success_t;

// TYPE_RESPONSE_ERROR
typedef struct dap_stream_ch_chain_net_srv_pkt_error{
    uint32_t code; // error code
} DAP_ALIGN_PACKED dap_stream_ch_chain_net_srv_pkt_error_t;

using namespace Dap;
using namespace Dap::Stream;

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
 * @brief ChChainNetSrv::onPktIn
 * @param a_pkt
 */
void ChChainNetSrv::onPktIn(DapChannelPacket* a_pkt)
{
    switch (static_cast<ChChainNetSrvPktType>(a_pkt->hdr()->type) ) {
        case REQUEST:{

        } break;
        case SIGN_REQUEST:{

        } break;
        case SIGN_RESPONSE:{

        } break;
        case RESPONSE_SUCCESS:{

        } break;
        case RESPONSE_ERROR:{

        } break;
        default: qWarning() << "Unknown packet type " << a_pkt->hdr()->type;
    }
}

