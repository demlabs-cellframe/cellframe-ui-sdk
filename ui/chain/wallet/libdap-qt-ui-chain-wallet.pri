QT += core qml

INCLUDEPATH += $$PWD $$PWD/../

win32{
    QMAKE_CXXFLAGS +=  -mno-ms-bitfields
}

DISTFILES +=

HEADERS += \
    $$PWD/DapHelper.h \
    $$PWD/DapSettings.h \
    $$PWD/DapSystemTrayIcon.h 

SOURCES += \
    $$PWD/DapHelper.cpp \
    $$PWD/DapSettings.cpp \
    $$PWD/DapSystemTrayIcon.cpp \

RESOURCES += \
    $$PWD/libdap-qt-ui-chain-wallet.qrc



