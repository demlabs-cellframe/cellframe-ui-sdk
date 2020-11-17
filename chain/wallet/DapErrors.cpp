#include "DapErrors.h"

const QString DapErrors::getErrorText(Error a_error)
{
    switch (a_error) {
        case Error::NOT_ENOUGH_FUNDS_FOR_TRANSFER: return "not enough funds for transfer";
        case Error::UNKNOWN_ERROR: return "Unknown error";
        default: return "";
    }
}

