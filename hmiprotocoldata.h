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
    union DataConverter
    {
        uint8_t u8[8];
        uint16_t u16[4];
        uint32_t u32[2];
        uint64_t u64;

        float f[2];
        double d;
    };

    enum Command : uint8_t
    {
        GET_PARAM = 0x00,
        REQUEST_GET_PARAM = GET_PARAM,
        SET_PARAM = 0x50,
        REQUEST_SET_PARAM = SET_PARAM,
        KEEP_ALIVE = 0xA0,
        LOGIN = 0xA1,
        FORCE_LOGIN = 0xA2,
        LOGIN_REQUEST = 0xA3,
        DISCONNECT_CODE = 0xA4,
    };

    enum Sensor : uint8_t
    {
        SENSOR_LV_FOSO = 0x00,
        SENSOR_LV_LODO = 0x01,
        SENSOR_TEMP = 0x02,
        SENSOR_OD = 0x03,
        SENSOR_PH_ANOX = 0x04,
        SENSOR_PH_AIREACION = 0x05,
        SENSOR_MOTOR_CURRENT = 0x10,
        SENSOR_MOTOR_VOLTAJE = 0x11,
        SENSOR_MOTOR_TEMP = 0x12,
        SENSOR_MOTOR_VELOCITY = 0x13,
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
