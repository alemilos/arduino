
#pragma once
#include "./IScreen.h"
#include "../../config/Config.h"
#include "../../data/VehicleData.h"


#include <TFT_eSPI.h> // esp32

class DashboardScreen : public IScreen {
public:
    explicit DashboardScreen(TFT_eSPI& tft);

    void drawFull(const VehicleData& data) override;
    void update  (const VehicleData& data) override;
    void onEnter ()                        override;
    void onExit  ()                        override;

    const char* getName() const override { return "DASHBOARD"; }

private:
    TFT_eSPI& _tft;

    // Shadow values — dirty check lives here, not in DisplayManager
    uint8_t  _prevSpeed;
    uint16_t _prevRpm;
    float    _prevVoltage;
    float    _prevCurrent;
    float    _prevEfficiency;
    bool     _prevDataValid;
    bool     _prevEngineRunning;

    void _drawFrame      ();
    void _drawSpeed      (uint8_t speed,          bool force);
    void _drawRpm        (uint16_t rpm,            bool force);
    void _drawRpmBar     (uint16_t rpm,            bool force);
    void _drawVoltage    (float v,                 bool force);
    void _drawCurrent    (float a,                 bool force);
    void _drawEfficiency (float eff,               bool force);
    void _drawStatusBar  (const VehicleData& data, bool force);

    void _clearRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    void _ftoa(float val, uint8_t decimals, char* buf, uint8_t bufLen) const;
};