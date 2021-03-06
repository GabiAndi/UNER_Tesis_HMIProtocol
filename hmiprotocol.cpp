#include "hmiprotocol.h"

HMIProtocol::HMIProtocol(QObject *parent) :
    QObject{parent}
{
    // Estado del analisis
    state = new state_t;

    state->dataMaxLength = 1;
    state->timeOutMs = 100;
    state->data.clear();
    state->readIndex = 0;
    state->readState = ReadState::STATE_HEADER_BYTE1;
    state->payloadLength = 0;

    // Paquete de datos
    package = new package_t;

    package->cmd = 0x00;
    package->payload.clear();

    // Timer
    timer = new QTimer(this);

    timer->setSingleShot(true);

    connect(timer, &QTimer::timeout, this, &HMIProtocol::reset);
}

HMIProtocol::~HMIProtocol()
{
    // Eliminamos la memoria
    delete state;
    delete package;
    delete timer;
}

void HMIProtocol::read(const QByteArray data)
{
    /*
     * Se añaden los datos nuevos a los anteriores, en el caso de que el paquete venga por partes.
     * Solo si el tamaño no supera al maximo permitido.
     */
    if ((state->data.length() + data.length()) <= (state->dataMaxLength * 1024))
    {
        state->data.append(data);
    }

    // Hasta que no se terminen de analizar todos los datos en cola
    while (state->readIndex < state->data.length())
    {
        // Se lee el proximo byte del buffer si esta disponible y se aumenta el indice de lectura
        uint8_t readByte = state->data.at(state->readIndex++);

        // Maquina de estados
        switch (state->readState)
        {
            // Primer byte de cabecera
            case ReadState::STATE_HEADER_BYTE1:
                if (readByte == PROTOCOL_HEADER.at(STATE_HEADER_BYTE1))
                {
                    // Disparo del timer de time out
                    timer->start(state->timeOutMs);

                    state->readState = ReadState::STATE_HEADER_BYTE2;
                }

                else
                {
                    reset();
                }

                break;

            // Segundo byte de cabecera
            case ReadState::STATE_HEADER_BYTE2:
                if (readByte == PROTOCOL_HEADER.at(STATE_HEADER_BYTE2))
                {
                    state->readState = ReadState::STATE_HEADER_BYTE3;
                }

                else
                {
                    reset();
                }

                break;

            // Tercer byte de cabecera
            case ReadState::STATE_HEADER_BYTE3:
                if (readByte == PROTOCOL_HEADER.at(STATE_HEADER_BYTE3))
                {
                    state->readState = ReadState::STATE_HEADER_BYTE4;
                }

                else
                {
                    reset();
                }

                break;

            // Cuarto byte de cabecera
            case ReadState::STATE_HEADER_BYTE4:
                if (readByte == PROTOCOL_HEADER.at(STATE_HEADER_BYTE4))
                {
                    state->readState = ReadState::STATE_HEADER_TOKEN;
                }

                else
                {
                    reset();
                }

                break;

            // Byte de token
            case ReadState::STATE_HEADER_TOKEN:
                if (readByte == PROTOCOL_HEADER.at(STATE_HEADER_TOKEN))
                {
                    state->readState = ReadState::STATE_PAYLOAD_LENGTH_BYTE1;
                }

                else
                {
                    reset();
                }

                break;

            // Byte 1 de tamaño
            case ReadState::STATE_PAYLOAD_LENGTH_BYTE1:
                state->payloadLength = (uint16_t)(readByte);

                state->readState = ReadState::STATE_PAYLOAD_LENGTH_BYTE2;

                break;

            // Byte 2 de tamaño
            case ReadState::STATE_PAYLOAD_LENGTH_BYTE2:
                state->payloadLength |= ((uint16_t)(readByte) << 8);

                state->readState = ReadState::STATE_CMD;

                break;

            // Comando
            case ReadState::STATE_CMD:
                package->cmd = readByte;

                state->readState = ReadState::STATE_PAYLOAD;

                break;

            // Payload
            case ReadState::STATE_PAYLOAD:
                // Si quedan datos del payload por leer
                if (state->payloadLength > 0)
                {
                    package->payload.append(readByte);

                    state->payloadLength--;
                }

                // Si se recibio todo el paquete
                if (state->payloadLength == 0)
                {
                    // Se envia el paquete
                    emit readyRead(package->cmd, package->payload);

                    reset();
                }

                break;

            // Caso por defecto
            default:
                reset();

                break;
        }
    }
}

void HMIProtocol::write(const uint8_t cmd, const QByteArray payload)
{
    // Preparamos el comando y el payload en un paquete entero
    QByteArray data;

    uint16_t payloadLength = payload.length();

    data.append(PROTOCOL_HEADER);
    data.append((uint8_t)(payloadLength));
    data.append((uint8_t)((payloadLength >> 8)));
    data.append(cmd);
    data.append(payload);

    emit readyWrite(data);
}

void HMIProtocol::reset()
{
    // Detenemos el timer
    timer->stop();

    // Estado
    state->data.remove(0, state->readIndex);
    state->readIndex = 0;
    state->readState = ReadState::STATE_HEADER_BYTE1;
    state->payloadLength = 0;

    // Paquete
    package->cmd = 0x00;
    package->payload.clear();
}
