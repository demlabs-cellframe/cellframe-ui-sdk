#ifndef DAPERRORS_H
#define DAPERRORS_H

#include <QString>
#include <QMap>
#include <QObject>
#include <QJsonObject>
#include <QDebug>

class DapErrors
{
public:
    static const QString ERROR_TEXT;
    static const QString ERROR_NUMBER;
    static const QString ERROR_PARAMETER;
    static const QString ERROR_NUMBER_SECOND_ROW;
    static const QString ERROR_PARAMETER_SECOND_ROW;

    enum Error
    {
        UNKNOWN_ERROR,
        //Errors associated with the transfer of tokens
        DESTINATION_ADDRESS_INVALID,
        NOT_ENOUGH_FOUNDS_FOR_TRANSFER,
        SOURCE_ADDRESS_IS_INVALID,
        FEE_ADDRESS_IS_INVALID,
        WALLET_ADDRESS_NOT_RECOGNIZED,
        NOT_FOUND_NET_BY_NAME_XXX,
        WALLET_XXX_DOES_NOT_EXIST,
        NOT_FOUND_CHEIN_NAME_XXX_TRY_USE_PARAMETR_CHEIN,
        SOCKET_CONNECTION_ERR_XXX,
        CANT_CONNECT_TO_DAPCASHNODE

    };
    DapErrors(){}

    static void inicialErrorList();
    static QJsonObject getErrorNumber(const QString& a_text);
    static const QString &getErrorText(Error a_error);
private:
    static QMap<Error,QPair<QString,QString>> m_listErrors;
};

#endif // DAPERRORS_H
