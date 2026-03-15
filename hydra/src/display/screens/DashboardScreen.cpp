#include "../screens/DashboardScreen.h"
#include <Arduino.h>

DashboardScreen::DashboardScreen(TFT_eSPI& tft)
    : _tft(tft),
      _prevSpeed(0xFF),
      _prevRpm(0xFFFF),
      _prevVoltage(-1.0f),
      _prevCurrent(-1.0f),
      _prevEfficiency(-1.0f),
      _prevDataValid(false),
      _prevEngineRunning(false)
{}

// ── Lifecycle ────────────────────────────────────────────
void DashboardScreen::onEnter() {
    // Invalidate shadow to force full redraw on first update()
    _prevSpeed         = 0xFF;
    _prevRpm           = 0xFFFF;
    _prevVoltage       = -1.0f;
    _prevCurrent       = -1.0f;
    _prevEfficiency    = -1.0f;
    _prevDataValid     = false;
    _prevEngineRunning = false;
}

void DashboardScreen::onExit() {
    // Next screen is responsible for clearing the display
}

// ── drawFull — called once on mount ─────────────────────
void DashboardScreen::drawFull(const VehicleData& data) {
    // fillScreen(COLOR_BG)
    _drawFrame();
    _drawSpeed     (data.speedKmh,        true);
    _drawRpm       (data.rpmEngine,       true);
    _drawRpmBar    (data.rpmEngine,       true);
    _drawVoltage   (data.batteryVoltage,  true);
    _drawCurrent   (data.currentAmps,     true);
    _drawEfficiency(data.efficiencyKmKwh, true);
    _drawStatusBar (data,                 true);

    _prevSpeed         = data.speedKmh;
    _prevRpm           = data.rpmEngine;
    _prevVoltage       = data.batteryVoltage;
    _prevCurrent       = data.currentAmps;
    _prevEfficiency    = data.efficiencyKmKwh;
    _prevDataValid     = data.dataValid;
    _prevEngineRunning = data.engineRunning;
}

// ── update — dirty values only ───────────────────────────
void DashboardScreen::update(const VehicleData& data) {
    _drawSpeed     (data.speedKmh,        data.speedKmh        != _prevSpeed);
    _drawRpm       (data.rpmEngine,       data.rpmEngine       != _prevRpm);
    _drawRpmBar    (data.rpmEngine,       data.rpmEngine       != _prevRpm);
    _drawVoltage   (data.batteryVoltage,  data.batteryVoltage  != _prevVoltage);
    _drawCurrent   (data.currentAmps,     data.currentAmps     != _prevCurrent);
    _drawEfficiency(data.efficiencyKmKwh, data.efficiencyKmKwh != _prevEfficiency);
    _drawStatusBar (data, data.dataValid      != _prevDataValid ||
                          data.engineRunning  != _prevEngineRunning);

    _prevSpeed         = data.speedKmh;
    _prevRpm           = data.rpmEngine;
    _prevVoltage       = data.batteryVoltage;
    _prevCurrent       = data.currentAmps;
    _prevEfficiency    = data.efficiencyKmKwh;
    _prevDataValid     = data.dataValid;
    _prevEngineRunning = data.engineRunning;
}

// ── Static frame ─────────────────────────────────────────
void DashboardScreen::_drawFrame() {
    // drawFastHLine(0, ZONE_MID_Y,    LCD_WIDTH, COLOR_ACCENT)  — top/mid separator
    // drawFastHLine(0, ZONE_STATUS_Y, LCD_WIDTH, COLOR_ACCENT)  — mid/status separator
    // drawFastVLine(240, 0,           ZONE_TOP_H, COLOR_ACCENT) — speed/rpm divider
    // drawFastVLine(160, ZONE_MID_Y,  ZONE_MID_H, COLOR_LABEL) — volt/curr divider
    // drawFastVLine(320, ZONE_MID_Y,  ZONE_MID_H, COLOR_LABEL) — curr/eff divider
    // print label "SPEED"      at (SPD_X, SPD_Y), size 2, COLOR_LABEL
    // print label "ENGINE RPM" at (RPM_X, RPM_Y), size 2, COLOR_LABEL
    // print unit  "km/h"       at (SPD_X, SPD_VAL_Y+55), size 1
    // print unit  "rpm"        at (RPM_X, RPM_VAL_Y+55), size 1
    // print label "VOLTAGE"    at (VOLT_VAL_X, ZONE_MID_Y+10), size 1
    // print label "CURRENT"    at (CURR_VAL_X, ZONE_MID_Y+10), size 1
    // print label "EFFICIENCY" at (EFF_VAL_X,  ZONE_MID_Y+10), size 1
    // print unit  "V"          at (VOLT_VAL_X+85, VOLT_VAL_Y), size 1
    // print unit  "A"          at (CURR_VAL_X+65, CURR_VAL_Y), size 1
    // print unit  "km/kWh"     at (EFF_VAL_X+95,  EFF_VAL_Y),  size 1
}

// ── Speed ─────────────────────────────────────────────────
void DashboardScreen::_drawSpeed(uint8_t speed, bool force) {
    if (!force) return;
    _clearRect(SPD_VAL_X, SPD_VAL_Y, SPD_CLEAR_W, SPD_CLEAR_H);
    // color = (speed > SPEED_MAX_KMH) ? COLOR_WARN : COLOR_TEXT
    // setTextSize(6), setCursor(SPD_VAL_X, SPD_VAL_Y)
    // print speed with leading spaces for alignment (3-char field)
}

// ── RPM ───────────────────────────────────────────────────
void DashboardScreen::_drawRpm(uint16_t rpm, bool force) {
    if (!force) return;
    _clearRect(RPM_VAL_X, RPM_VAL_Y, RPM_CLEAR_W, RPM_CLEAR_H);
    // color = rpm > RPM_MAX*0.875 ? COLOR_WARN : rpm > RPM_MAX*0.625 ? COLOR_ORANGE : COLOR_TEXT
    // setTextSize(5), setCursor(RPM_VAL_X, RPM_VAL_Y)
    // print rpm with leading space if < 1000
}

// ── RPM bar ───────────────────────────────────────────────
void DashboardScreen::_drawRpmBar(uint16_t rpm, bool force) {
    if (!force) return;
    // filled = rpm * RPM_BAR_W / RPM_MAX  (clamped to RPM_BAR_W)
    // barColor = same thresholds as _drawRpm
    // drawRect(RPM_BAR_X, RPM_BAR_Y, RPM_BAR_W, RPM_BAR_H, COLOR_LABEL)   — outline
    // fillRect(RPM_BAR_X+1, RPM_BAR_Y+1, filled-1,           RPM_BAR_H-2, barColor) — filled
    // fillRect(RPM_BAR_X+filled, RPM_BAR_Y+1, RPM_BAR_W-filled-1, RPM_BAR_H-2, COLOR_BG) — erase tail
}

// ── Voltage ───────────────────────────────────────────────
void DashboardScreen::_drawVoltage(float v, bool force) {
    if (!force) return;
    _clearRect(VOLT_VAL_X, VOLT_VAL_Y, MID_CLEAR_W, MID_CLEAR_H);
    // color = (v < VOLTAGE_MIN) ? COLOR_WARN : COLOR_TEXT
    // setTextSize(3), _ftoa(v, 1, buf), print buf
}

// ── Current ───────────────────────────────────────────────
void DashboardScreen::_drawCurrent(float a, bool force) {
    if (!force) return;
    _clearRect(CURR_VAL_X, CURR_VAL_Y, MID_CLEAR_W, MID_CLEAR_H);
    // setTextColor(COLOR_TEXT), setTextSize(3)
    // _ftoa(a, 1, buf), print buf
}

// ── Efficiency ────────────────────────────────────────────
void DashboardScreen::_drawEfficiency(float eff, bool force) {
    if (!force) return;
    _clearRect(EFF_VAL_X, EFF_VAL_Y, MID_CLEAR_W, MID_CLEAR_H);
    // color = (eff > 100.0f) ? COLOR_OK : COLOR_TEXT
    // setTextSize(3), _ftoa(eff, 0, buf), print buf
}

// ── Status bar ────────────────────────────────────────────
void DashboardScreen::_drawStatusBar(const VehicleData& data, bool force) {
    if (!force) return;
    _clearRect(0, ZONE_STATUS_Y + 1, LCD_WIDTH, ZONE_STATUS_H - 1);
    // print "SRC:" label at (10, ZONE_STATUS_Y+10), COLOR_LABEL
    // fillCircle(20, ZONE_STATUS_Y+40, 8, data.dataValid ? COLOR_OK : COLOR_WARN)
    // print data.dataValid ? "DATA OK" : "NO DATA" at (35, ZONE_STATUS_Y+34)
    // print data.engineRunning ? "ENGINE ON" : "ENGINE OFF" at (200, ZONE_STATUS_Y+34)
    // print uptime mm:ss at (360, ZONE_STATUS_Y+34), COLOR_LABEL
}

// ── Helpers ───────────────────────────────────────────────
void DashboardScreen::_clearRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    // fillRect(x, y, w, h, COLOR_BG)
}

void DashboardScreen::_ftoa(float val, uint8_t decimals, char* buf, uint8_t bufLen) const {
    dtostrf(val, 4, decimals, buf);
}