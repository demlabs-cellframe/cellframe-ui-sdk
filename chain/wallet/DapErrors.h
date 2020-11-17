#ifndef DAPERRORS_H
#define DAPERRORS_H

#include <QString>
#include <QMap>

class DapErrors
{
    DapErrors() {};
public:

    enum Error
    {
        UNKNOWN_ERROR,
        NOT_ENOUGH_FUNDS_FOR_TRANSFER,
    };

    static const QString getErrorText(Error a_error);
};

#endif // DAPERRORS_H
