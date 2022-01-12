/*************************************************************/
/* AUTOR: GabiAndi                                           */
/* FECHA: 11/10/2021                                         */
/*                                                           */
/* DESCRIPCION:                                              */
/* Gestiona el protocolo de comunicacion desarrollado para   */
/* el sistema.                                               */
/*************************************************************/

#ifndef HMIPROTOCOL_H
#define HMIPROTOCOL_H

#include "HMIProtocol_global.h"

#include <QObject>

#include <QTimer>

class HMIPROTOCOL_EXPORT HMIProtocol : public QObject
{
        Q_OBJECT

    public:
        explicit HMIProtocol(QObject *parent = nullptr);
        ~HMIProtocol();

        enum Command : uint8_t
        {
            CMD_NONE = 0x00,
            CMD_ALIVE = 0xA0,
            CMD_LOGIN = 0xA1
        };

    signals:
        void readyRead(const HMIProtocol::Command cmd, const QByteArray payload);
        void readyWrite(const QByteArray data);

    public slots:
        void init();

        void read(const QByteArray data);
        void write(const HMIProtocol::Command cmd, const QByteArray payload);

    private:
        // Paquete de datos
        const QByteArray PROTOCOL_HEADER = "SCPA:";

        enum ReadState : uint8_t
        {
            STATE_HEADER_BYTE1,
            STATE_HEADER_BYTE2,
            STATE_HEADER_BYTE3,
            STATE_HEADER_BYTE4,
            STATE_HEADER_TOKEN,
            STATE_PAYLOAD_LENGTH_BYTE1,
            STATE_PAYLOAD_LENGTH_BYTE2,
            STATE_CMD,
            STATE_PAYLOAD
        };

        typedef struct
        {
            uint16_t dataMaxLength;
            int timeOutMs;

            QByteArray data;

            uint16_t readIndex;
            HMIProtocol::ReadState readState;

            uint16_t payloadLength;
        }state_t;

        typedef struct
        {
            HMIProtocol::Command cmd;
            QByteArray payload;
        }package_t;

        state_t *state = nullptr;

        package_t *package = nullptr;

    private slots:
        void reset();
};

#endif // HMIPROTOCOL_H
