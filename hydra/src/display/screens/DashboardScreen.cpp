#include "../screens/DashboardScreen.h"
#include <Arduino.h>

DashboardScreen::DashboardScreen(Adafruit_ILI9341& tft)
    : _tft(tft),
      _prevSpeed(0xFF),
      _prevFuelCellVoltage(-1.0f),
      _prevFuelCellTemperature(-1.0f),
      _prevMotorCurrent(-1.0f),
      _prevHydrogenConsumption(-1.0f),
      _prevCabinTemperature(-1.0f),

      _prevDataValid(false),
      _prevEngineRunning(false)
{}

// ── Lifecycle ────────────────────────────────────────────
void DashboardScreen::onEnter() {
    // Invalidate shadow to force full redraw on first update()
    _prevSpeed               = 0xFF;
    _prevFuelCellVoltage     =  -1.0f;
    _prevFuelCellTemperature =  -1.0f;
    _prevMotorCurrent        = -1.0f;
    _prevHydrogenConsumption = -1.0f;
    _prevCabinTemperature    = -1.0f;

    _prevDataValid     = false;
    _prevEngineRunning = false;
}

void DashboardScreen::onExit() { /* Next screen is responsible for clearing the display */ }

// ── drawFull — called once on mount ─────────────────────
void DashboardScreen::drawFull(const VehicleData& data) {
    _tft.fillScreen(COLOR_BG);
    _tft.setTextColor(COLOR_LABEL);
    _tft.setTextSize(2);

    _drawFrame();
    _drawSpeed     (data.speedKmh,        true);
    _drawFuelCellVoltage(data.fuelCellVoltage, true);
    _drawMotorCurrent   (data.currentAmps,     true);
    // _drawStatusBar (data,                 true);

    _prevSpeed           = data.speedKmh;
    _prevFuelCellVoltage = data.fuelCellVoltage;
    _prevMotorCurrent    = data.currentAmps;
    _prevDataValid       = data.dataValid;
    _prevEngineRunning   = data.engineRunning;
}

// ── update — dirty values only ───────────────────────────
void DashboardScreen::update(const VehicleData& data) {
    _drawSpeed     (data.speedKmh,        data.speedKmh        != _prevSpeed);
    _drawFuelCellVoltage(data.fuelCellVoltage,  data.fuelCellVoltage  != _prevFuelCellVoltage);
    _drawMotorCurrent   (data.currentAmps,     data.currentAmps     != _prevMotorCurrent);
    // _drawStatusBar (data, data.dataValid      != _prevDataValid ||
    //                       data.engineRunning  != _prevEngineRunning);

    _prevSpeed           = data.speedKmh;
    _prevFuelCellVoltage = data.fuelCellVoltage;
    _prevMotorCurrent = data.currentAmps;
    _prevDataValid       = data.dataValid;
    _prevEngineRunning   = data.engineRunning;
}

// ── Static frame ─────────────────────────────────────────
void DashboardScreen::_drawFrame() {
    _tft.drawFastHLine(0, ZONE_MID_Y, LCD_WIDTH, COLOR_ACCENT);
    _tft.drawFastHLine(0, ZONE_STATUS_Y, LCD_WIDTH, COLOR_ACCENT);
    _tft.drawFastVLine(160, ZONE_MID_Y, ZONE_MID_H, COLOR_LABEL);
    _tft.drawFastVLine(320, ZONE_MID_Y, ZONE_MID_H, COLOR_LABEL);

    // Labels
    _tft.setTextColor(COLOR_LABEL);
    _tft.setTextSize(1);
    _tft.setCursor(SPD_X, SPD_Y);
    _tft.print("SPEED");
    _tft.setCursor(VOLT_VAL_X, ZONE_MID_Y + 10);
    _tft.print("VOLTAGE");
    _tft.setCursor(CURR_VAL_X, ZONE_MID_Y + 10);
    _tft.print("CURRENT");
}

// ── Speed ─────────────────────────────────────────────────
void DashboardScreen::_drawSpeed(uint8_t speed, bool force) {
    if (!force) return;
    _clearRect(SPD_VAL_X, SPD_VAL_Y, SPD_CLEAR_W, SPD_CLEAR_H);
    _tft.setTextColor(COLOR_TEXT);
    _tft.setTextSize(6);
    _tft.setCursor(SPD_VAL_X, SPD_VAL_Y);
    char buf[4];
    snprintf(buf, sizeof(buf), "%3d", speed);
    _tft.println(buf);
}


// ── Voltage ───────────────────────────────────────────────
void DashboardScreen::_drawFuelCellVoltage(float v, bool force) {
    if (!force) return;
    _clearRect(VOLT_VAL_X, VOLT_VAL_Y, MID_CLEAR_W, MID_CLEAR_H);
    uint16_t color = (v < VOLTAGE_MIN) ? COLOR_WARN : COLOR_TEXT;
    _tft.setTextColor(color);
    _tft.setTextSize(3);
    _tft.setCursor(VOLT_VAL_X, VOLT_VAL_Y);
    char buf[8];
    _ftoa(v, 1, buf, sizeof(buf));
    _tft.println(buf);
}

// ── Current ───────────────────────────────────────────────
void DashboardScreen::_drawMotorCurrent(float a, bool force) {
    if (!force) return;
    _clearRect(CURR_VAL_X, CURR_VAL_Y, MID_CLEAR_W, MID_CLEAR_H);
    _tft.setTextColor(COLOR_TEXT);
    _tft.setTextSize(3);
    _tft.setCursor(CURR_VAL_X, CURR_VAL_Y);
    char buf[8];
    _ftoa(a, 1, buf, sizeof(buf));
    _tft.println(buf);
}


// ── Status bar ────────────────────────────────────────────
// void DashboardScreen::_drawStatusBar(const VehicleData& data, bool force) {
    // if (!force) return;
    // _clearRect(0, ZONE_STATUS_Y + 1, LCD_WIDTH, ZONE_STATUS_H - 1);
    // print "SRC:" label at (10, ZONE_STATUS_Y+10), COLOR_LABEL
    // fillCircle(20, ZONE_STATUS_Y+40, 8, data.dataValid ? COLOR_OK : COLOR_WARN)
    // print data.dataValid ? "DATA OK" : "NO DATA" at (35, ZONE_STATUS_Y+34)
    // print data.engineRunning ? "ENGINE ON" : "ENGINE OFF" at (200, ZONE_STATUS_Y+34)
    // print uptime mm:ss at (360, ZONE_STATUS_Y+34), COLOR_LABEL
// }

// ── Helpers ───────────────────────────────────────────────
void DashboardScreen::_clearRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    _tft.fillRect(x, y, w, h, COLOR_BG);
}

void DashboardScreen::_ftoa(float val, uint8_t decimals, char* buf, uint8_t bufLen) const {
    dtostrf(val, 4, decimals, buf);
}