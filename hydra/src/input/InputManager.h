#pragma once
#include "ButtonDefs.h"
#include <Arduino.h>

// Clean edge detection without interrupt or delay().
// "wasPressed"  → true ONE TIME when the button is pressed
// "wasReleased" → true ONE TIME when the button is released
// After read, the flag is cleared.

static constexpr uint8_t  PIN_MAP[BUTTON_COUNT] = {
    2, 3, 4, 5, 6, 7, 8, 9   // corrispondenti a ButtonID::LN..RW (excluding COUNT)
};
static constexpr uint32_t DEBOUNCE_MS = 50;

class InputManager {
public:
    InputManager();

    // Chiama ogni TASK_PERIOD_INPUT_MS nel loop principale
    void update(uint32_t nowMs);

    // Edge detection — consuma il flag
    bool wasPressed (ButtonID id);
    bool wasReleased(ButtonID id);

    // Stato istantaneo (non edge)
    bool isHeld(ButtonID id) const;

private:
    struct ButtonState {
        bool     currentRaw;       // lettura GPIO raw
        bool     lastDebounced;    // stato dopo debounce
        bool     pressedFlag;      // edge rising, consumabile
        bool     releasedFlag;     // edge falling, consumabile
        uint32_t lastChangeMs;     // timestamp ultima transizione
    };

    ButtonState _buttons[BUTTON_COUNT];

    uint8_t _idx(ButtonID id) const { return static_cast<uint8_t>(id); }
};
