// #pragma once
// #include <Arduino.h>
// #include "IDataSource.h"

// // Parser del protocollo seriale dalla ECU.
// // Frame formato: [0xAA][0xBB][SPD][RPM_H][RPM_L][VOLT_RAW][CUR_RAW][CRC8]
// // CRC8 = XOR di tutti i byte da [SPD] a [CUR_RAW]
// // Non bloccante: legge solo i byte disponibili in questo tick.

// static constexpr uint8_t FRAME_SOF1     = 0xAA;
// static constexpr uint8_t FRAME_SOF2     = 0xBB;
// static constexpr uint8_t FRAME_PAYLOAD  = 5;    // byte dopo i due SOF
// static constexpr uint8_t FRAME_TOTAL    = 8;
// static constexpr uint32_t DATA_TIMEOUT_MS = 2000; // oltre 2s → dataValid = false

// class RealDataSource : public IDataSource {
// public:
//     explicit RealDataSource(HardwareSerial& serial);

//     void               update(uint32_t nowMs)       override;
//     const VehicleData& getData()             const  override;
//     const char*        getSourceName()       const  override { return "ECU_SERIAL"; }

// private:
//     HardwareSerial& _serial;
//     VehicleData     _data;

//     uint8_t  _rxBuf[FRAME_TOTAL];
//     uint8_t  _rxIdx;
//     bool     _syncFound;
//     uint32_t _lastValidFrameMs;

//     bool _parseFrame();
//     uint8_t _crc8(const uint8_t* buf, uint8_t len) const;
// };