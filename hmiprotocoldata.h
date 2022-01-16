#ifndef HMIPROTOCOLDATA_H
#define HMIPROTOCOLDATA_H

#include <QObject>

namespace hmiprotocoldata
{
    enum Payload : uint8_t
    {
        PAYLOAD_ERROR = 0x00,
        PAYLOAD_OK = 0xFF
    };

    enum LoginRequest : uint8_t
    {
        LOGIN_ERROR = 0x00,
        LOGIN_BUSY = 0xAA,
        LOGIN_PASS = 0xCC,
        LOGIN_OK = 0xFF
    };

    enum Command : uint8_t
    {
        ALIVE = 0xA0,
        LOGIN = 0xA1,
        FORCE_LOGIN = 0xA2,
        LOGIN_REQUEST = 0xA3
    };
}

#endif // HMIPROTOCOLDATA_H
