#include "DapCertificateCommands.h"
#include <QMetaEnum>


DapCertificateCommands *DapCertificateCommands::instance()
{
    static DapCertificateCommands s_instance;
    return &s_instance;
}


QString DapCertificateCommands::commandToString(DapCertificateCommands::Commands command)
{
    static QMetaEnum CertificateCommands_MetaEnum = QMetaEnum::fromType<Commands>();
    return CertificateCommands_MetaEnum.valueToKey(int(command));
}
