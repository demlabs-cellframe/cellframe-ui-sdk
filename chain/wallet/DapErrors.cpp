#include "DapErrors.h"

QMap<DapErrors::Error,QString> DapErrors::m_listErrors{
    {Error::NOT_ENOUGH_FOUNDS_FOR_TRANSFER,                     "not enough funds for transfer"}
    ,{Error::UNKNOWN_ERROR,                                     "Unknown error"}
};

const QString *DapErrors::getErrorText(Error a_error)
{
    static QString* resultStr = new QString(m_listErrors.value(a_error));
    return resultStr;
}

