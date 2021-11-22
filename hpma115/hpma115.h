/*
 * Copyright (c) 2021, Koncepto.io
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef CATIE_SIXTRON_HPMA115_H_
#define CATIE_SIXTRON_HPMA115_H_

#include <cstdint>

namespace sixtron {

typedef struct {
    uint16_t pm2_5;
    uint16_t pm10;
    uint16_t pm1_0;
    uint16_t pm4_0;
} hpma115_data_t;

class HPMA115 {
public:
    enum class ErrorType : uint8_t {
        Ok = 0,
        SerialError,
        InvalidValue,
    };

    enum class Header : uint8_t {
        Send = 0x68,
        Resp = 0x40,
        Ack = 0xA5,
        Nack = 0x96,
        AutoData1 = 0x42,
        AutoData2 = 0x4d,
    };

    enum class Command : uint8_t {
        ReadMeas = 0x04,
        StartMeas = 0x01,
        StopMeas = 0x02,
        SetCoef = 0x08,
        ReadCoef = 0x10,
        EnableAutoSend = 0x40,
        StopAutoSend = 0x20,
    };

    HPMA115(mbed::BufferedSerial *serial);
    ~HPMA115();
    ErrorType read_measurement(hpma115_data_t *data);
    ErrorType start_measurement();
    ErrorType stop_measurement();
    ErrorType set_adjust_coef(uint8_t coef);
    ErrorType read_adjust_coef(uint8_t *coef);
    ErrorType enable_auto_send();
    ErrorType stop_auto_send();

private:
    mbed::BufferedSerial &serial;
    ErrorType send_command(Command cmd);
    ErrorType compute_checksum(uint8_t *frame);
    bool compact_nstd;
};

} // namespace sixtron

#endif // CATIE_SIXTRON_HPMA115_H_
