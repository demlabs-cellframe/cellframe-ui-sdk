#include "DapErrors.h"

QMap<DapErrors::Error,QPair<QString,QString>> DapErrors::m_listErrors;
const QString DapErrors::ERROR_TEXT = "errorText";
const QString DapErrors::ERROR_NUMBER = "errorNumber";
const QString DapErrors::ERROR_PARAMETER = "errorParameter";
const QString DapErrors::ERROR_NUMBER_SECOND_ROW = "errorNumberSecondRow";
const QString DapErrors::ERROR_PARAMETER_SECOND_ROW = "errorParameterSecondRow";

void DapErrors::inicialErrorList()
{
    //Errors associated with the transfer of tokens
    m_listErrors.insert(Error::DESTINATION_ADDRESS_INVALID,                     {QString("destination address is invalid")                                  ,QObject::tr("destination address is invalid")});
    m_listErrors.insert(Error::NOT_ENOUGH_FOUNDS_FOR_TRANSFER,                  {QString("not enough funds for transfer")                                   ,QObject::tr("not enough funds for transfer")});
    m_listErrors.insert(Error::SOURCE_ADDRESS_IS_INVALID,                       {QString("source address is invalid")                                       ,QObject::tr("source address is invalid")});
    m_listErrors.insert(Error::FEE_ADDRESS_IS_INVALID,                          {QString("fee address is invalid")                                          ,QObject::tr("fee address is invalid")});
    m_listErrors.insert(Error::WALLET_ADDRESS_NOT_RECOGNIZED,                   {QString("wallet address not recognized")                                   ,QObject::tr("wallet address not recognized")});
    m_listErrors.insert(Error::NOT_FOUND_NET_BY_NAME_XXX,                       {QString("not found net by name (\\w+)")                                    ,QObject::tr("not found net by name %1")});
    m_listErrors.insert(Error::WALLET_XXX_DOES_NOT_EXIST,                       {QString("wallet (\\w+) does not exist")                                    ,QObject::tr("wallet %1 does not exist")});
    m_listErrors.insert(Error::NOT_FOUND_CHEIN_NAME_XXX_TRY_USE_PARAMETR_CHEIN, {QString("not found chain name (\\w+), try use parameter '-chain'")         ,QObject::tr("not found chain name %1, try use parameter '-chain'")});
    m_listErrors.insert(Error::SOCKET_CONNECTION_ERR_XXX,                       {QString("Socket connection err: (\\w+)")                                   ,QObject::tr("Socket connection err: %1")});
    m_listErrors.insert(Error::CANT_CONNECT_TO_DAPCASHNODE,                     {QString("Can't connect to dapcash-node")                                   ,QObject::tr("Can't connect to dapcash-node")});
}

const QString &DapErrors::getErrorText(Error a_error)
{
    if(m_listErrors.isEmpty())
        inicialErrorList();

    static const QString resultStr = m_listErrors.value(a_error).second;
    return resultStr;
}

QJsonObject DapErrors::getErrorNumber(const QString& a_text)
{
    if(m_listErrors.isEmpty())
        inicialErrorList();

    QJsonObject resultObj;
    QStringList stringList = a_text.split("\n");
    for( auto string:stringList)
    {
        if(!string.isEmpty())
            for(int numKey = 0; numKey < m_listErrors.count();numKey++)
            {
                Error numIter = static_cast<Error>(numKey);

                if(m_listErrors[numIter].first.contains("(\\w+)"))
                {
                    QRegExp re(m_listErrors[numIter].first);

                    re.indexIn(string, 0);
                    if(!re.cap(0).isEmpty())
                    {
                        if(resultObj.isEmpty())
                        {
                            resultObj.insert(ERROR_NUMBER,numIter);
                            if(!re.cap(1).isEmpty())
                                resultObj.insert(ERROR_PARAMETER,re.cap(1));
                        }
                        else {
                            resultObj.insert(ERROR_NUMBER_SECOND_ROW,numIter);
                            if(!re.cap(1).isEmpty())
                                resultObj.insert(ERROR_PARAMETER_SECOND_ROW,re.cap(1));
                        }
                        continue;
                    }
                }
                else
                {
                    QRegExp re(m_listErrors[numIter].first);
                    re.indexIn(string, 0);
                    if(!re.cap(0).isEmpty())
                    {
                        if(resultObj.isEmpty())
                            resultObj.insert(ERROR_NUMBER,numIter);
                        else
                            resultObj.insert(ERROR_NUMBER_SECOND_ROW,numIter);
                        continue;
                    }
                }
            }
    }

    if(resultObj.isEmpty())
        resultObj.insert(ERROR_NUMBER,Error::UNKNOWN_ERROR);

    return resultObj;
}
