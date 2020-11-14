#ifndef DAPERRORS_H
#define DAPERRORS_H

#include <QString>
#include <QMap>

class DapErrors
{
public:

    enum Error
    {
        UNKNOWN_ERROR,
        NOT_ENOUGH_FOUNDS_FOR_TRANSFER,
    };
    DapErrors(){}

    static const QString *getErrorText(Error a_error);
private:
    static QMap<Error,QString> m_listErrors;
};

#endif // DAPERRORS_H
