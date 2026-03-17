#include "SimulatedDataSource.h"
#include <cmath>

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

    // Pseudo-random number generator (deterministic based on counter)
    auto pseudoRandom = [](uint32_t seed) -> float {
        uint32_t x = seed ^ (seed << 13);
        x = x ^ (x >> 17);
        x = x ^ (x << 5);
        return (float)(x % 100) / 100.0f;
    };

    // Fase 0: accelerazione con variazioni (primi 10 secondi)
    if (_simPhase == 0) {
        // Variable acceleration: base 0.8-1.2 km/h per cycle
        float accelVariation = 0.8f + pseudoRandom(_phaseCounter) * 0.4f;
        _data.speedKmh = (uint8_t)(_data.speedKmh + accelVariation > 50 ? 50 : _data.speedKmh + accelVariation);
        if (_phaseCounter >= 6000) { _simPhase = 1; _phaseCounter = 0; }
    }
    // Fase 1: crociera con variazioni di velocità (20 secondi)
    else if (_simPhase == 1) {
        // Simulate realistic cruise: speed varies around 35-45 km/h with a wave pattern
        float wavePhase = (_phaseCounter / 20000.0f) * 6.28f; // 0 to 2π
        float waveDelta = sin(wavePhase) * 5.0f; // ±5 km/h variation
        float baseSpeed = 40.0f;
        _data.speedKmh = (uint8_t)(baseSpeed + waveDelta + pseudoRandom(_phaseCounter) * 2.0f);

        if (_phaseCounter >= 15000) { _simPhase = 2; _phaseCounter = 0; }
    }
    // Fase 2: decelerazione (8 secondi)
    else {
        _data.speedKmh = (uint8_t)(_data.speedKmh > 0 ? _data.speedKmh - 1 : 0);
        if (_phaseCounter >= 8000) { _simPhase = 0; _phaseCounter = 0; }
    }

    // Aggiorna dati derivati
    _data.fuelCellVoltage = 12.6f - (_data.consumedMah / 10000.0f);
    _data.currentAmps    = _data.engineRunning ? 2.5f + _data.speedKmh * 0.05f : 0.1f;

    // Simulate fuel cell temperature (heats up with current, cools down slowly)
    float targetTemp = 35.0f + (_data.currentAmps * 8.0f);  // hotter with more current
    _data.fuelCellTemperature += (targetTemp - _data.fuelCellTemperature) * 0.05f;

    // Simulate cabin temperature (baseline 22°C, increases with activity)
    float cabinHeatGeneration = _data.speedKmh * 0.15f;
    _data.cabinTemperatureC += (22.0f + cabinHeatGeneration - _data.cabinTemperatureC) * 0.02f;

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