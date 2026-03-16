#pragma once
#include <stdint.h>

// Pod (Plain Old Data) Structure — no logic, no constructor.
// All modules read from here, only DataSource writes.
// For portability, use only fixed size types.

struct VehicleData {
    uint8_t  speedKmh;         // 0–50 kmh
    // uint16_t rpmEngine;        // 0–65535 rpm
    uint32_t odometryM;        // odometria in metri (non cm: overflow più tardi)

    float    fuelCellVoltage;   // es. 12.4V
    float    currentAmps;      // corrente istantanea
    float    consumedMah;      // energia consumata sessione

    float    efficiencyKmKwh;  // km/kWh calcolato

    // System state
    bool     engineRunning;
    bool     dataValid;        // false if source doesn't respond 
    uint32_t lastUpdateMs;     // timestamp last write 

    void reset() {
        speedKmh        = 0;
        // rpmEngine       = 0;
        odometryM       = 0;
        fuelCellVoltage  = 0.0f;
        currentAmps     = 0.0f;
        consumedMah     = 0.0f;
        efficiencyKmKwh = 0.0f;
        engineRunning   = false;
        dataValid       = false;
        lastUpdateMs    = 0;
    }
};