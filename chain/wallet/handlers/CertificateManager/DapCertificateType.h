#ifndef DAPCERTIFICATETYPE_H
#define DAPCERTIFICATETYPE_H


#include <QObject>


class DapCertificateType
{
    Q_GADGET
public:
    //certificate type access
    enum AccessKeyType{
        Public = 0,
        Private,
        Both
    };
    Q_ENUM(AccessKeyType);

    //certificate location dir
    enum DirType{
        DefaultDir = 0,
        ShareDir
    };
    Q_ENUM(DirType);


protected:
    explicit DapCertificateType() {  }
};



#endif // DAPCERTIFICATETYPE_H
