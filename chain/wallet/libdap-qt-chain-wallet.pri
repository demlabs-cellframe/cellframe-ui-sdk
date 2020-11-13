QT += core

INCLUDEPATH += $$PWD $$PWD/../ \
    $$PWD/models


include (dapRPCProtocol/DapRPCProtocol.pri)

win32{
    QMAKE_CXXFLAGS +=  -mno-ms-bitfields
}

DISTFILES +=

HEADERS += \
    $$PWD/CellframeNodeConfig.h \
    $$PWD/DapChainConvertor.h \
    $$PWD/DapHistoryType.h \
    $$PWD/DapLogMessage.h \
    $$PWD/DapNetwork.h \
    $$PWD/DapNodeType.h \
    $$PWD/DapToken.h \
    $$PWD/DapTokenValue.h \
    $$PWD/DapVpnOrder.h \
    $$PWD/DapWallet.h \
    $$PWD/DapWalletHistoryEvent.h \
    $$PWD/DapWalletToken.h \
    $$PWD/handlers/CertificateManager/DapCertificateCommands.h \
    $$PWD/handlers/CertificateManager/DapCertificateOperation.h \
    $$PWD/handlers/CertificateManager/DapCertificateType.h \
    $$PWD/handlers/DapAbstractCommand.h \
    $$PWD/handlers/DapActivateClientCommand.h \
    $$PWD/handlers/DapAddWalletCommand.h \
    $$PWD/handlers/DapCertificateManagerCommands.h \
    $$PWD/handlers/DapCreateTransactionCommand.h \
    $$PWD/handlers/DapExportLogCommand.h \
    $$PWD/handlers/DapGetHistoryExecutedCmdCommand.h \
    $$PWD/handlers/DapGetListNetworksCommand.h \
    $$PWD/handlers/DapGetListWalletsCommand.h \
    $$PWD/handlers/DapGetNetworkStatusCommand.h \
    $$PWD/handlers/DapGetWalletsInfoCommand.h \
    $$PWD/handlers/DapGetWalletAddressesCommand.h \
    $$PWD/handlers/DapGetWalletHistoryCommand.h \
    $$PWD/handlers/DapGetWalletInfoCommand.h \
    $$PWD/handlers/DapGetWalletTokenInfoCommand.h \
    $$PWD/handlers/DapMempoolProcessCommand.h \
    $$PWD/handlers/DapNetworkGoToCommand.h \
    $$PWD/handlers/DapQuitApplicationCommand.h \
    $$PWD/handlers/DapRunCmdCommand.h \
    $$PWD/handlers/DapSaveHistoryExecutedCmdCommand.h \
    $$PWD/handlers/DapUpdateLogsCommand.h \
    $$PWD/models/DapBalanceModel.h \
    $$PWD/models/DapNetworksList.h \
    $$PWD/models/DapTransactionsProxyModel.h \
    $$PWD/models/DapVpnOrdersModel.h \
    $$PWD/models/DapWalletBalanceModel.h \
    $$PWD/models/DapWalletModel.h \
    $$PWD/serviceClient/DapServiceClient.h \
    $$PWD/serviceClient/DapServiceClientNativeAbstract.h \
    $$PWD/serviceClient/DapServiceClientNativeLinux.h \
    $$PWD/serviceClient/DapServiceClientNativeMacOS.h \
    $$PWD/serviceClient/DapServiceClientNativeWin.h

SOURCES += \
    $$PWD/CellframeNodeConfig.cpp \
    $$PWD/DapChainConvertor.cpp \
    $$PWD/DapHistoryType.cpp \
    $$PWD/DapLogMessage.cpp \
    $$PWD/DapNetwork.cpp \
    $$PWD/DapToken.cpp \
    $$PWD/DapTokenValue.cpp \
    $$PWD/DapVpnOrder.cpp \
    $$PWD/DapWallet.cpp \
    $$PWD/DapWalletHistoryEvent.cpp \
    $$PWD/DapWalletToken.cpp \
    $$PWD/handlers/CertificateManager/DapCertificateCommands.cpp \
    $$PWD/handlers/CertificateManager/DapCertificateOperation.cpp \
    $$PWD/handlers/DapAbstractCommand.cpp \
    $$PWD/handlers/DapActivateClientCommand.cpp \
    $$PWD/handlers/DapAddWalletCommand.cpp \
    $$PWD/handlers/DapCertificateManagerCommands.cpp \
    $$PWD/handlers/DapCreateTransactionCommand.cpp \
    $$PWD/handlers/DapExportLogCommand.cpp \
    $$PWD/handlers/DapGetHistoryExecutedCmdCommand.cpp \
    $$PWD/handlers/DapGetListNetworksCommand.cpp \
    $$PWD/handlers/DapGetListWalletsCommand.cpp \
    $$PWD/handlers/DapGetNetworkStatusCommand.cpp \
    $$PWD/handlers/DapGetWalletsInfoCommand.cpp \
    $$PWD/handlers/DapGetWalletAddressesCommand.cpp \
    $$PWD/handlers/DapGetWalletHistoryCommand.cpp \
    $$PWD/handlers/DapGetWalletInfoCommand.cpp \
    $$PWD/handlers/DapGetWalletTokenInfoCommand.cpp \
    $$PWD/handlers/DapMempoolProcessCommand.cpp \
    $$PWD/handlers/DapNetworkGoToCommand.cpp \
    $$PWD/handlers/DapQuitApplicationCommand.cpp \
    $$PWD/handlers/DapRunCmdCommand.cpp \
    $$PWD/handlers/DapSaveHistoryExecutedCmdCommand.cpp \
    $$PWD/handlers/DapUpdateLogsCommand.cpp \
    $$PWD/models/DapBalanceModel.cpp \
    $$PWD/models/DapNetworksList.cpp \
    $$PWD/models/DapTransactionsProxyModel.cpp \
    $$PWD/models/DapVpnOrdersModel.cpp \
    $$PWD/models/DapWalletBalanceModel.cpp \
    $$PWD/models/DapWalletModel.cpp \
    $$PWD/serviceClient/DapServiceClient.cpp \
    $$PWD/serviceClient/DapServiceClientNativeAbstract.cpp \
    $$PWD/serviceClient/DapServiceClientNativeLinux.cpp \
    $$PWD/serviceClient/DapServiceClientNativeMacOS.cpp \
    $$PWD/serviceClient/DapServiceClientNativeWin.cpp




