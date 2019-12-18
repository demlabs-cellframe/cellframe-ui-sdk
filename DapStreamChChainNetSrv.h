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
#include "dap_chain_datum_tx_receipt.h"
#include "DapChBase.h"
#include "DapCrypto.h"



class DapStreamer;
class DapSession;
namespace Dap {

    // TODO move to its own module
    namespace Chain {

        class NetId
        {
        private:
            dap_chain_net_id_t m_value;
        public:
            const dap_chain_net_id_t& value () const { return  m_value;}
            NetId(){ m_value.uint64 = 0ull; }
            NetId( const dap_chain_net_id_t& a_value){ m_value.uint64 = a_value.uint64; }
            NetId( const NetId& a_netId){ m_value.uint64 = a_netId.m_value.uint64; }
            NetId( const QString& a_str){
                m_value.uint64 = a_str.isNull() ? 0 : dap_chain_net_id_from_str(a_str.toLatin1().constData()).uint64;
            }
            QString toString(){ return QString().sprintf("0x%016lX",m_value.uint64); }
            operator dap_chain_net_id_t& (){ return  m_value; }
            dap_chain_net_id_t& operator=(const NetId& a_netId) {  m_value.uint64 = a_netId.m_value.uint64; return m_value; }
            bool operator==(const NetId& a_netId){ return a_netId.m_value.uint64 == m_value.uint64; }
        };


        namespace NetSrv {
            class Uid
            {
            private:
                dap_chain_net_srv_uid_t m_value;
            public:
                Uid(quint64 a_value) { m_value.uint64 = a_value ;}
                Uid(){ m_value.uint64 = 0ull; }
                Uid( const dap_chain_net_srv_uid_t& a_value){ m_value.uint64 = a_value.uint64; }
                Uid( const Uid& a_netSrvUid){ m_value.uint64 = a_netSrvUid.m_value.uint64; }
                Uid( const QString& a_str){
                    m_value.uint64 = dap_chain_net_srv_uid_from_str(a_str.toLatin1().constData()).uint64;
                }
                operator dap_chain_net_srv_uid_t& (){ return  m_value; }

                QString toString(){ return QString().sprintf("0x%016lX",m_value.uint64); }

                dap_chain_net_srv_uid_t& operator=(const Uid& a_netSrvUid) {
                    m_value.uint64 = a_netSrvUid.m_value.uint64;
                    return m_value;
                }
                dap_chain_net_srv_uid_t& operator=(quint64 a_value) {
                    m_value.uint64 = a_value;
                    return m_value;
                }

                bool operator==(const Uid& a_netSrvUid){ return a_netSrvUid.m_value.uint64 == m_value.uint64; }
            };
            static const Uid UidNull=Uid();
            enum UnitType{
                UNIT_TYPE_UNDEFINED = 0 ,
                UNIT_TYPE_MB = 0x00000001, // megabytes
                UNIT_TYPE_SEC = 0x00000002, // seconds
                UNIT_TYPE_DAY = 0x00000003,  // days
                UNIT_TYPE_KB = 0x00000010,  // kilobytes
                UNIT_TYPE_B = 0x00000011,   // bytes
            };


        }
        class Receipt {
        private:
            dap_chain_datum_tx_receipt_t * m_value;
        public:
            enum ThrowClass{DataNull, DataSizeWrong};
            Receipt() { m_value = nullptr; }
            Receipt(const Receipt& a_receipt){ m_value = a_receipt.m_value; }
            Receipt(const Receipt* a_receipt){ m_value = a_receipt->m_value; }
            Receipt(const void * a_data, size_t a_dataSize){
                if( a_data == nullptr)
                    throw DataNull;
                if( a_dataSize < ( 1 +sizeof (m_value->receipt_info)+sizeof (m_value->size)))
                    throw DataSizeWrong;
                m_value = DAP_NEW_Z_SIZE(dap_chain_datum_tx_receipt_t, a_dataSize);
                ::memcpy(m_value,a_data,a_dataSize);
            }
            ~Receipt(){
                if (m_value)
                    DAP_DELETE(m_value);
            }

            void release(){ m_value = nullptr; } // Release wrapper from m_value to prevent doulbe free
            operator dap_chain_datum_tx_receipt_t& () { return  *m_value;}
            operator dap_chain_datum_tx_receipt_t* () { return  m_value;}
            operator const void* () { return  m_value;}
            operator void* () { return  m_value;}
            quint16 size() { return m_value?m_value->size : 0; }

            dap_chain_datum_tx_receipt_t * value() { return m_value; }
            NetSrv::Uid getNetSrvUid() { return m_value ? m_value->receipt_info.srv_uid : NetSrv::UidNull; }
            NetSrv::UnitType getUnitType() { return m_value ?static_cast<NetSrv::UnitType>(m_value->receipt_info.units_type.uint32):
                                                             NetSrv::UNIT_TYPE_UNDEFINED ; }
            quint64 getUnits() { return  m_value? m_value->receipt_info.units : 0; }
            quint64 getValueDatoshi() { return  m_value ? m_value->receipt_info.value_datoshi: 0; }

            void signAdd(Crypto::Key& a_key){
                dap_chain_datum_tx_receipt_sign_add( m_value, m_value->size, a_key );
            }
            void signAdd(Crypto::Cert& a_cert){
                dap_chain_datum_tx_receipt_sign_add( m_value, m_value->size, a_cert.key() );
            }

            Receipt* deepCopy(){
                Receipt* ret = new Receipt;
                ret->m_value = DAP_NEW_Z_SIZE(dap_chain_datum_tx_receipt_t, m_value->size);
                ::memcpy(ret->m_value, m_value, m_value->size);
                return  ret;
            }
        };

    }
    namespace Stream{
        enum ChChainNetSrvPktType {
            REQUEST             = 0x01,
            SIGN_REQUEST        = 0x10,
            SIGN_RESPONSE       = 0x11,
            NOTIFY_STOPPED      = 0x20,
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
            TX_COND_WRONG_SIZE        = 0x00000405,
            RECEIPT_CANT_FIND         = 0x00000500,
            RECEIPT_NO_SIGN           = 0x00000501,
            PRICE_NOT_FOUND           = 0x00000600,
            RECEIPT_WRONG_PKEY_HASH   = 0x00000502,
            UNKNOWN                   = 0xffffffff
        };
        static inline const QString chChainNetSrvPktResponseErrorCodeToString(quint32 a){
            switch (static_cast<ChChainNetSrvPktResponseErrorCode>(a)) {
                case UNDEFINED: return "UNDEFINED";
                case SERVICE_NOT_FOUND: return "SERVICE_NOT_FOUND";
                case NETWORK_NOT_FOUND: return "NETWORK_NOT_FOUND";
                case NETWORK_NO_LEDGER: return "NETWORK_NO_LEDGER";
                case USAGE_CANT_ADD: return "USAGE_CANT_ADD";
                case TX_COND_NOT_FOUND: return "TX_COND_NOT_FOUND";
                case TX_COND_NO_COND_OUT: return "TX_COND_NO_COND_OUT";
                case TX_COND_NOT_ENOUGH: return "TX_COND_NOT_ENOUGH";
                case TX_COND_NOT_ACCEPT_TOKEN: return "TX_COND_NOT_ACCEPT_TOKEN";
                case TX_COND_WRONG_SRV_UID: return "TX_COND_WRONG_SRV_UID";
                case TX_COND_WRONG_SIZE: return "TX_COND_WRONG_SIZE";
                case RECEIPT_CANT_FIND: return "RECEIPT_CANT_FIND";
                case RECEIPT_NO_SIGN: return "RECEIPT_NO_SIGN";
                case PRICE_NOT_FOUND: return "PRICE_NOT_FOUND";
                case RECEIPT_WRONG_PKEY_HASH: return "RECEIPT_WRONG_PKEY_HASH";
                case UNKNOWN: return "UNKNOWN";
            }
        };

        class ChChainNetSrv : public DapChBase
        {
            Q_OBJECT
        private:
            DapStreamer * m_streamer;
            DapSession * m_mainDapSession;
        public:
            ChChainNetSrv(DapStreamer * a_streamer, DapSession * a_mainDapSession);
        signals:
            void sigReceiptToSign(Chain::Receipt * receipt );
            void sigProvideSuccess (Chain::NetId a_netId, Chain::NetSrv::Uid a_srvUid, quint32 a_usageId );
            void sigProvideError(Chain::NetId a_netId, Chain::NetSrv::Uid a_srvUid, quint32 a_usageId,quint32 a_errorCode);
            void sigNotifyStopped(); // Service stopped
        public slots:
            void onPktIn(DapChannelPacket* a_pkt) override;

            void sendReceipt(Chain::Receipt * receipt );
            void sendRequest(Chain::NetId a_netId,// Network id wheither to request
                Crypto::HashFast a_txCond, // Conditioned transaction with paymemt for
                Chain::NetSrv::Uid a_srvUid ,// Service ID
                const QString& a_token        // Token to pay
            );
        };
    }
}
