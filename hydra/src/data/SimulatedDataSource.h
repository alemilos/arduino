#pragma once
#include "IDataSource.h"

// Simulate a vehicle that accelerates, keeps a constant speed, decelerates.

class SimulatedDataSource : public IDataSource {
public:
    SimulatedDataSource();

    void              update(uint32_t nowMs)       override;
    const VehicleData& getData()             const override;
    const char*        getSourceName()       const override { return "SIMULATED"; }

private:
    VehicleData _data;
    uint32_t    _lastUpdateMs;
    uint8_t     _simPhase;      // 0=accel, 1=cruise, 2=decel
    uint16_t    _phaseCounter;

    void _advanceSimulation(uint32_t dtMs);
    float _computeEfficiency() const;
};