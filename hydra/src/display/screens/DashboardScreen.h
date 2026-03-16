
#pragma once
#include "./IScreen.h"
#include "../../config/Config.h"
#include "../../data/VehicleData.h"


#include <Adafruit_ILI9341.h>

class DashboardScreen : public IScreen {
public:
    explicit DashboardScreen(Adafruit_ILI9341& tft);

    void drawFull(const VehicleData& data) override;
    void update  (const VehicleData& data) override;
    void onEnter ()                        override;
    void onExit  ()                        override;

    const char* getName() const override { return "DASHBOARD"; }

private:
    Adafruit_ILI9341& _tft;

    // Shadow values 
    uint8_t  _prevSpeed;
    float    _prevFuelCellVoltage;
    float    _prevFuelCellTemperature;
    float    _prevMotorCurrent;
    float    _prevHydrogenConsumption;
    float    _prevCabinTemperature;

    bool     _prevDataValid;
    bool     _prevEngineRunning;

    void _drawFrame                  ();
    void _drawSpeed                  (uint8_t speed,           bool force);
    void _drawFuelCellVoltage        (float v,                 bool force);
    void _drawFuelCellTemperature    (float c,                 bool force);
    void _drawMotorCurrent           (float a,                 bool force);
    void _drawHydrogenConsumption    (float x,                 bool force);
    void _drawCabinTemperature       (float c,                 bool force);

    void _clearRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    void _ftoa(float val, uint8_t decimals, char* buf, uint8_t bufLen) const;
};