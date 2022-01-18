/*************************************************************/
/* AUTOR: GabiAndi                                           */
/* FECHA: 18/01/2022                                         */
/*                                                           */
/* DESCRIPCION:                                              */
/* Valores de comandos, respuestas, etc.                     */
/*************************************************************/

#ifndef HMIPROTOCOLDATA_H
#define HMIPROTOCOLDATA_H

#include <QObject>

namespace hmiprotocoldata
{
    enum Command : uint8_t
    {
        KEEP_ALIVE = 0xA0,
        LOGIN = 0xA1,
        FORCE_LOGIN = 0xA2,
        LOGIN_REQUEST = 0xA3,
        DISCONNECT_CODE = 0xA4,
    };

    enum KeepAliveMode : uint8_t
    {
        REPLY = 0x00,
        REQUEST = 0xFF
    };

    enum LoginRequest : uint8_t
    {
        LOGIN_ERROR = 0x00,
        LOGIN_FORCE_REQUIRED = 0xAA,
        LOGIN_CORRECT = 0xFF
    };

    enum ForceLogin : uint8_t
    {
        NO_FORCE_CONNECT = 0x00,
        FORCE_CONNECT = 0xFF,
    };

    enum DisconnectCode : uint8_t
    {
        LOGIN_TIMEOUT = 0x00,
        OTHER_USER_LOGIN = 0xFF,
    };
}

#endif // HMIPROTOCOLDATA_H
