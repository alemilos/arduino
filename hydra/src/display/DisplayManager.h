#pragma once
#include "../display/screens/IScreen.h"
#include "../data/VehicleData.h"

// DisplayManager is a router, not a renderer.
// It owns the TFT object and the active IScreen pointer.
// All dirty-checking and drawing logic lives inside the IScreen implementations.
class DisplayManager {
public:
    DisplayManager();
    void begin();

    // Called by scheduler every TASK_PERIOD_DISPLAY_MS
    void update(const VehicleData& data);

    // Switch active screen (0 = dashboard, ... there are no other screens yet)
    void setScreen(uint8_t screenId);

private:
    IScreen*  _activeScreen;   // non-owning pointer into _screens[]
    uint8_t   _activeScreenId;
    bool      _needsFullDraw;  // true after setScreen() or begin()

    // Screen registry — add new screens here
    // (static storage, no heap allocation)
    // e.g. DashboardScreen _dashboard;
    //      DebugScreen     _debug;
    // IScreen* _screens[N] = { &_dashboard, &_debug, ... };
};