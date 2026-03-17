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
    _prevFuelCellVoltage     = -1.0f;
    _prevFuelCellTemperature = -1.0f;
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

    _drawFrame();
    _drawLogo(true);
    _drawFuelCellInfo(data.fuelCellVoltage, data.fuelCellTemperature, true);
    _drawCabinTemperature(data.cabinTemperatureC, true);
    _drawSpeed(data.speedKmh, true);
    _drawHydrogenConsumption(data.consumedMah, true);
    _drawCustomArea(true);
    _drawMotorCurrent(data.currentAmps, true);

    _prevSpeed               = data.speedKmh;
    _prevFuelCellVoltage     = data.fuelCellVoltage;
    _prevFuelCellTemperature = data.fuelCellTemperature;
    _prevMotorCurrent        = data.currentAmps;
    _prevHydrogenConsumption = data.consumedMah;
    _prevCabinTemperature    = data.cabinTemperatureC;
    _prevDataValid           = data.dataValid;
    _prevEngineRunning       = data.engineRunning;
}

// ── update — dirty values only ───────────────────────────
void DashboardScreen::update(const VehicleData& data) {
    _drawSpeed(data.speedKmh, data.speedKmh != _prevSpeed);
    _drawFuelCellInfo(data.fuelCellVoltage, data.fuelCellTemperature,
                      data.fuelCellVoltage != _prevFuelCellVoltage ||
                      data.fuelCellTemperature != _prevFuelCellTemperature);
    _drawCabinTemperature(data.cabinTemperatureC, data.cabinTemperatureC != _prevCabinTemperature);
    _drawHydrogenConsumption(data.consumedMah, data.consumedMah != _prevHydrogenConsumption);
    _drawMotorCurrent(data.currentAmps, data.currentAmps != _prevMotorCurrent);

    _prevSpeed               = data.speedKmh;
    _prevFuelCellVoltage     = data.fuelCellVoltage;
    _prevFuelCellTemperature = data.fuelCellTemperature;
    _prevMotorCurrent        = data.currentAmps;
    _prevHydrogenConsumption = data.consumedMah;
    _prevCabinTemperature    = data.cabinTemperatureC;
    _prevDataValid           = data.dataValid;
    _prevEngineRunning       = data.engineRunning;
}

// ── Static frame ─────────────────────────────────────────
void DashboardScreen::_drawFrame() {
    _tft.setTextColor(COLOR_LABEL);
    _tft.setTextSize(1);

    // Horizontal dividers
    _tft.drawFastHLine(0, ZONE_TOP_H, LCD_WIDTH, COLOR_ACCENT);
    _tft.drawFastHLine(0, ZONE_BOTTOM_Y, LCD_WIDTH, COLOR_ACCENT);

    // Vertical dividers (thirds for bottom row)
    _tft.drawFastVLine(160, ZONE_BOTTOM_Y, ZONE_BOTTOM_H, COLOR_ACCENT);
    _tft.drawFastVLine(320, ZONE_BOTTOM_Y, ZONE_BOTTOM_H, COLOR_ACCENT);

    // Top row vertical dividers (for logo, fuel cell, cabin)
    _tft.drawFastVLine(85, ZONE_TOP_Y, ZONE_TOP_H, COLOR_ACCENT);
    _tft.drawFastVLine(280, ZONE_TOP_Y, ZONE_TOP_H, COLOR_ACCENT);

    // Labels for bottom row
    _tft.setCursor(20, H2_LABEL_Y);
    _tft.print("H2");
    _tft.setCursor(175, CURR_LABEL_Y);
    _tft.print("CUSTOM");
    _tft.setCursor(330, CURR_LABEL_Y);
    _tft.print("MOTOR");
}

// ── Logo (placeholder) ───────────────────────────────────
void DashboardScreen::_drawLogo(bool force) {
    if (!force) return;
    _clearRect(LOGO_X, LOGO_Y, LOGO_W, LOGO_H);
    _tft.setTextColor(COLOR_TEXT);
    _tft.setTextSize(1);
    _tft.setCursor(LOGO_X + 5, LOGO_Y + 25);
    _tft.print("H2");
}

// ── Fuel Cell Info (Voltage + Temperature) ───────────────
void DashboardScreen::_drawFuelCellInfo(float voltage, float temperature, bool force) {
    if (!force) return;

    // Clear area
    _clearRect(FUELCELL_X, FUELCELL_Y, 180, ZONE_TOP_H - 10);

    // Label
    _tft.setTextColor(COLOR_LABEL);
    _tft.setTextSize(1);
    _tft.setCursor(FUELCELL_X, FUELCELL_LABEL_Y);
    _tft.print("FUEL CELL");

    // Voltage value
    uint16_t voltColor = (voltage < VOLTAGE_MIN) ? COLOR_WARN : COLOR_TEXT;
    _tft.setTextColor(voltColor);
    _tft.setTextSize(2);
    _tft.setCursor(FUELCELL_X, FUELCELL_VAL_Y);
    char voltBuf[8];
    _ftoa(voltage, 1, voltBuf, sizeof(voltBuf));
    _tft.print(voltBuf);
    _tft.print("V");

    // Temperature value
    _tft.setTextColor(COLOR_TEXT);
    _tft.setCursor(FUELCELL_X + 100, FUELCELL_VAL_Y);
    char tempBuf[6];
    _ftoa(temperature, 0, tempBuf, sizeof(tempBuf));
    _tft.print(tempBuf);
    _tft.print("C");
}

// ── Cabin Temperature ────────────────────────────────────
void DashboardScreen::_drawCabinTemperature(float temp, bool force) {
    if (!force) return;

    _clearRect(CABIN_X, CABIN_Y, 160, ZONE_TOP_H - 10);

    _tft.setTextColor(COLOR_LABEL);
    _tft.setTextSize(1);
    _tft.setCursor(CABIN_X, CABIN_LABEL_Y);
    _tft.print("CABIN");

    _tft.setTextColor(COLOR_TEXT);
    _tft.setTextSize(2);
    _tft.setCursor(CABIN_X, CABIN_VAL_Y);
    char buf[6];
    _ftoa(temp, 0, buf, sizeof(buf));
    _tft.print(buf);
    _tft.print("C");
}

// ── Speed (Center, Large) ────────────────────────────────
void DashboardScreen::_drawSpeed(uint8_t speed, bool force) {
    if (!force) return;
    _clearRect(SPD_VAL_X - 30, SPD_VAL_Y - 20, SPD_CLEAR_W + 60, SPD_CLEAR_H);

    _tft.setTextColor(COLOR_TEXT);
    _tft.setTextSize(6);
    _tft.setCursor(SPD_VAL_X, SPD_VAL_Y);
    char buf[4];
    snprintf(buf, sizeof(buf), "%3d", speed);
    _tft.print(buf);

    _tft.setTextColor(COLOR_LABEL);
    _tft.setTextSize(2);
    _tft.setCursor(SPD_VAL_X + 200, SPD_VAL_Y + 30);
    _tft.print("km/h");
}

// ── Hydrogen Consumption ─────────────────────────────────
void DashboardScreen::_drawHydrogenConsumption(float h2, bool force) {
    if (!force) return;
    _clearRect(H2_X, H2_VAL_Y - 10, H2_CLEAR_W, H2_CLEAR_H);

    _tft.setTextColor(COLOR_TEXT);
    _tft.setTextSize(2);
    _tft.setCursor(H2_X, H2_VAL_Y);
    char buf[8];
    _ftoa(h2, 0, buf, sizeof(buf));
    _tft.print(buf);

    _tft.setTextColor(COLOR_LABEL);
    _tft.setTextSize(1);
    _tft.setCursor(H2_X, H2_VAL_Y + 25);
    _tft.print("mAh");
}

// ── Custom Area (Placeholder) ────────────────────────────
void DashboardScreen::_drawCustomArea(bool force) {
    if (!force) return;
    _clearRect(CUSTOM_X, CUSTOM_Y, CUSTOM_W, CUSTOM_H);

    _tft.setTextColor(COLOR_LABEL);
    _tft.setTextSize(1);
    _tft.setCursor(CUSTOM_X + 30, CUSTOM_Y + 30);
    _tft.print("CUSTOM");
}

// ── Motor Current ────────────────────────────────────────
void DashboardScreen::_drawMotorCurrent(float current, bool force) {
    if (!force) return;
    _clearRect(CURR_X, CURR_VAL_Y - 10, CURR_CLEAR_W, CURR_CLEAR_H);

    _tft.setTextColor(COLOR_TEXT);
    _tft.setTextSize(2);
    _tft.setCursor(CURR_X, CURR_VAL_Y);
    char buf[8];
    _ftoa(current, 1, buf, sizeof(buf));
    _tft.print(buf);

    _tft.setTextColor(COLOR_LABEL);
    _tft.setTextSize(1);
    _tft.setCursor(CURR_X, CURR_VAL_Y + 25);
    _tft.print("A");
}

// ── Helpers ───────────────────────────────────────────────
void DashboardScreen::_clearRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    _tft.fillRect(x, y, w, h, COLOR_BG);
}

void DashboardScreen::_ftoa(float val, uint8_t decimals, char* buf, uint8_t bufLen) const {
    dtostrf(val, 4, decimals, buf);
}