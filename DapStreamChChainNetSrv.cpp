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

#define DAP_STREAM_CH_CHAIN_NET_SRV_PKT_TYPE_REQUEST                       0x01
#define DAP_STREAM_CH_CHAIN_NET_SRV_PKT_TYPE_SIGN_REQUEST                  0x10
#define DAP_STREAM_CH_CHAIN_NET_SRV_PKT_TYPE_SIGN_RESPONSE                 0x11
#define DAP_STREAM_CH_CHAIN_NET_SRV_PKT_TYPE_RECEIPE                       0x20
#define DAP_STREAM_CH_CHAIN_NET_SRV_PKT_TYPE_RESPONSE_SUCCESS              0xf0
#define DAP_STREAM_CH_CHAIN_NET_SRV_PKT_TYPE_RESPONSE_ERROR                0xff

/**
 * @brief DapStreamChChainNetSrv::DapStreamChChainNetSrv
 * @param a_streamer
 * @param a_mainDapSession
 */
DapStreamChChainNetSrv::DapStreamChChainNetSrv(DapStreamer * a_streamer, DapSession * a_mainDapSession)
                : DapChBase(nullptr, 'R'), m_streamer(a_streamer), m_mainDapSession(a_mainDapSession)
{

}

/**
 * @brief DapStreamChChainNetSrv::onPktIn
 * @param a_pkt
 */
void DapStreamChChainNetSrv::onPktIn(DapChannelPacket* a_pkt)
{
    switch ( a_pkt->hdr()->type ) {
        case DAP_STREAM_CH_CHAIN_NET_SRV_PKT_TYPE_REQUEST:{

        } break;
        case DAP_STREAM_CH_CHAIN_NET_SRV_PKT_TYPE_SIGN_REQUEST:{

        } break;
        case DAP_STREAM_CH_CHAIN_NET_SRV_PKT_TYPE_SIGN_RESPONSE:{

        } break;
        case DAP_STREAM_CH_CHAIN_NET_SRV_PKT_TYPE_RECEIPE:{

        } break;
        case DAP_STREAM_CH_CHAIN_NET_SRV_PKT_TYPE_RESPONSE_SUCCESS:{

        } break;
        case DAP_STREAM_CH_CHAIN_NET_SRV_PKT_TYPE_RESPONSE_ERROR:{

        } break;
        default: qWarning() << "Unknown packet type " << a_pkt->hdr()->type;
    }
}

