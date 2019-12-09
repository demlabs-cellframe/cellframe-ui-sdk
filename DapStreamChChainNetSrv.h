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

#include "dap_common.h"
#include "dap_chain_common.h"
#include "DapChBase.h"

class DapStreamer;
class DapSession;
namespace Dap {
    namespace Stream{
        enum ChChainNetSrvPktType {
            REQUEST             = 0x01,
            SIGN_REQUEST        = 0x10,
            SIGN_RESPONSE       = 0x11,
            RESPONSE_SUCCESS    = 0xf0,
            RESPONSE_ERROR      = 0xff
        };
        enum ChChainNetSrvPktResponseErrorCode{
            UNDEFINED                 = 0x00000000,
            SERVICE_NOT_FOUND         = 0x00000100,
            NETWORK_NOT_FOUND         = 0x00000200,
            NETWORK_NO_LEDGER         = 0x00000201,
            USAGE_CANT_ADD            = 0x00000300,
            TX_COND_NOT_FOUND         = 0x00000400,
            TX_COND_NO_COND_OUT       = 0x00000401,
            TX_COND_NOT_ENOUGH        = 0x00000402,
            TX_COND_NOT_ACCEPT_TOKEN  = 0x00000403,
            TX_COND_WRONG_SRV_UID     = 0x00000404,
            TX_COND_WRONG_SIZE        = 0x00000404,
            RECEIPT_CANT_FIND         = 0x00000500,
            RECEIPT_NO_SIGN           = 0x00000501,
            PRICE_NOT_FOUND           = 0x00000600,
            RECEIPT_WRONG_PKEY_HASH   = 0x00000502,
            UNKNOWN                   = 0xffffffff
        };

        class ChChainNetSrv : public DapChBase
        {
            Q_OBJECT
        private:
            DapStreamer * m_streamer;
            DapSession * m_mainDapSession;
        public:
            ChChainNetSrv(DapStreamer * a_streamer, DapSession * a_mainDapSession);
        public slots:
            void onPktIn(DapChannelPacket* a_pkt) override;
        };
    }
}
