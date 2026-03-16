#include "SimulatedDataSource.h"

SimulatedDataSource::SimulatedDataSource()
    : _lastUpdateMs(0), _simPhase(0), _phaseCounter(0)
{
    _data.reset();
    _data.dataValid = true;
}

void SimulatedDataSource::update(uint32_t nowMs) {
    if (_lastUpdateMs == 0) {
        _lastUpdateMs = nowMs;
        return;
    }

    uint32_t dt = nowMs - _lastUpdateMs;
    _lastUpdateMs = nowMs;

    _advanceSimulation(dt);
    _data.lastUpdateMs = nowMs;
}

void SimulatedDataSource::_advanceSimulation(uint32_t dtMs) {
    _phaseCounter += dtMs;

    // Fase 0: accelerazione (primi 5 secondi)
    if (_simPhase == 0) {
        _data.speedKmh  = (uint8_t)(_data.speedKmh + 1 > 30 ? 30 : _data.speedKmh + 1);
        if (_phaseCounter >= 5000) { _simPhase = 1; _phaseCounter = 0; }
    }
    // Fase 1: crociera (10 secondi)
    else if (_simPhase == 1) {
        _data.speedKmh  = 30;
        if (_phaseCounter >= 10000) { _simPhase = 2; _phaseCounter = 0; }
    }
    // Fase 2: decelerazione (3 secondi)
    else {
        _data.speedKmh  = (uint8_t)(_data.speedKmh > 0 ? _data.speedKmh - 1 : 0);
        if (_phaseCounter >= 3000) { _simPhase = 0; _phaseCounter = 0; }
    }

    // Aggiorna dati derivati
    _data.fuelCellVoltage = 12.6f - (_data.consumedMah / 10000.0f);
    _data.currentAmps    = _data.engineRunning ? 2.5f + _data.speedKmh * 0.05f : 0.1f;

    float dtH = dtMs / 3600000.0f;
    _data.consumedMah   += _data.currentAmps * 1000.0f * dtH;
    _data.odometryM     += (uint32_t)(_data.speedKmh * dtMs / 3600);
    _data.efficiencyKmKwh = _computeEfficiency();
}

float SimulatedDataSource::_computeEfficiency() const {
    if (_data.consumedMah < 1.0f) return 0.0f;
    float consumedKwh = (_data.consumedMah * _data.fuelCellVoltage) / 1000000.0f;
    if (consumedKwh < 1e-6f) return 0.0f;
    return (_data.odometryM / 1000.0f) / consumedKwh;
}

const VehicleData& SimulatedDataSource::getData() const {
    return _data;
}