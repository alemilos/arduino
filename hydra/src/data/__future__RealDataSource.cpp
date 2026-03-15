// #include "RealDataSource.h"

// RealDataSource::RealDataSource(HardwareSerial& serial)
//     : _serial(serial), _rxIdx(0), _syncFound(false), _lastValidFrameMs(0)
// {
//     _data.reset();
// }

// void RealDataSource::update(uint32_t nowMs) {
//     // Leggi tutti i byte disponibili — NON aspettare. Non-bloccante.
//     while (_serial.available()) {
//         uint8_t b = (uint8_t)_serial.read();

//         if (!_syncFound) {
//             // Cerca inizio frame
//             if (b == FRAME_SOF1) {
//                 _rxBuf[0] = b;
//                 _rxIdx    = 1;
//             } else if (_rxIdx == 1 && b == FRAME_SOF2) {
//                 _rxBuf[1] = b;
//                 _rxIdx    = 2;
//                 _syncFound = true;
//             } else {
//                 _rxIdx = 0; // reset se sequenza SOF interrotta
//             }
//         } else {
//             // Accumula payload
//             if (_rxIdx < FRAME_TOTAL) {
//                 _rxBuf[_rxIdx++] = b;
//             }

//             if (_rxIdx == FRAME_TOTAL) {
//                 if (_parseFrame()) {
//                     _lastValidFrameMs = nowMs;
//                     _data.dataValid   = true;
//                     _data.lastUpdateMs = nowMs;
//                 }
//                 _rxIdx     = 0;
//                 _syncFound = false;
//             }
//         }
//     }

//     // Timeout: se non riceviamo frame da troppo, segnala dato non valido
//     if (_lastValidFrameMs > 0 && (nowMs - _lastValidFrameMs) > DATA_TIMEOUT_MS) {
//         _data.dataValid = false;
//     }
// }

// bool RealDataSource::_parseFrame() {
//     // buf: [AA][BB][SPD][RPM_H][RPM_L][VOLT_RAW][CUR_RAW][CRC]
//     uint8_t crcCalc  = _crc8(&_rxBuf[2], FRAME_PAYLOAD);
//     uint8_t crcRecv  = _rxBuf[FRAME_TOTAL - 1];

//     if (crcCalc != crcRecv) return false;

//     _data.speedKmh       = _rxBuf[2];
//     _data.rpmEngine      = ((uint16_t)_rxBuf[3] << 8) | _rxBuf[4];
//     _data.batteryVoltage = _rxBuf[5] * 0.1f;     // es. 126 → 12.6V
//     _data.currentAmps    = _rxBuf[6] * 0.1f;     // es. 25 → 2.5A
//     _data.engineRunning  = (_data.rpmEngine > 500);

//     return true;
// }

// uint8_t RealDataSource::_crc8(const uint8_t* buf, uint8_t len) const {
//     uint8_t crc = 0;
//     for (uint8_t i = 0; i < len; i++) crc ^= buf[i];
//     return crc;
// }

// const VehicleData& RealDataSource::getData() const {
//     return _data;
// }