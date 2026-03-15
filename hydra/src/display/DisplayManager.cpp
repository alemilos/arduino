#include "DisplayManager.h"
#include "screens/DashboardScreen.h"
#include <TFT_eSPI.h>


// ── Static screen instances (no heap) ───────────────────
static TFT_eSPI tft;                    
static DashboardScreen s_dashboard(tft);
static IScreen* s_screens[] = { &s_dashboard };
static constexpr uint8_t NUM_SCREENS = 1;

DisplayManager::DisplayManager()
    : _activeScreen(nullptr),
      _activeScreenId(0),
      _needsFullDraw(true)
{}

void DisplayManager::begin() {
    // tft.begin(); tft.setRotation(1); tft.fillScreen(COLOR_BG);
    // _activeScreen = s_screens[0];
    // _activeScreen->onEnter();
}

void DisplayManager::update(const VehicleData& data) {
    if (!_activeScreen) return;

    if (_needsFullDraw) {
        _needsFullDraw = false;
        _activeScreen->drawFull(data);  // full redraw on mount
    } else {
        _activeScreen->update(data);    // dirty-only redraw every tick
    }
}

void DisplayManager::setScreen(uint8_t screenId) {
    // if (screenId >= NUM_SCREENS) return;
    if (screenId == _activeScreenId && _activeScreen) return;

    if (_activeScreen) _activeScreen->onExit();

    _activeScreenId = screenId;
    // _activeScreen   = s_screens[screenId];
    _needsFullDraw  = true;

    if (_activeScreen) _activeScreen->onEnter();
}