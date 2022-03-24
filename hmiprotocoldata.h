/*************************************************************/
/* AUTOR: GabiAndi                                           */
/* FECHA: 18/01/2022                                         */
/*                                                           */
/* DESCRIPCION:                                              */
/* Valores de comandos, respuestas, etc.                     */
/*************************************************************/

#ifndef HMIPROTOCOLDATA_H
#define HMIPROTOCOLDATA_H

#include <inttypes.h>

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
        GET_SENSOR = 0x00,
        REQUEST_GET_SENSOR,
        SET_SENSOR = 0x10,
        REQUEST_SET_SENSOR,
        GET_SYSTEM_STATE = 0x20,
        REQUEST_GET_SYSTEM_STATE,
        SET_SYSTEM_STATE = 0x30,
        REQUEST_SET_SYSTEM_STATE,
        KEEP_ALIVE = 0xA0,
        LOGIN = 0xA1,
        FORCE_LOGIN = 0xA2,
        LOGIN_REQUEST = 0xA3,
        DISCONNECT_CODE = 0xA4,
    };

    enum Sensor : uint8_t
    {
        SENSOR_LV_FOSO = 0x00,
        SENSOR_LV_LODO,
        SENSOR_TEMP,
        SENSOR_OD,
        SENSOR_PH_ANOX,
        SENSOR_PH_AIREACION,
        SENSOR_MOTOR_CURRENT = 0x10,
        SENSOR_MOTOR_VOLTAJE,
        SENSOR_MOTOR_TEMP,
        SENSOR_MOTOR_VELOCITY,
    };

    enum SystemState :uint8_t
    {
        CONTROL_SYSTEM = 0x00,
        SETPOINT_OD,
        PID_ERROR,
        PID_KP,
        PID_RPM_KP,
        PID_KD,
        PID_RPM_KD,
        PID_KI,
        PID_RPM_KI,
    };

    enum KeepAliveMode : uint8_t
    {
        REPLY = 0x00,
        REQUEST = 0xFF
    };

    enum Request : uint8_t
    {
        REQUEST_ERROR = 0x00,
        REQUEST_OK = 0xFF
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
