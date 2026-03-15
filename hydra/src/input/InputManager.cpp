#include "InputManager.h"

InputManager::InputManager() {
    for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
        pinMode(PIN_MAP[i], INPUT_PULLUP);
        _buttons[i] = { false, false, false, false, 0 };
    }
}

void InputManager::update(uint32_t nowMs) {
    for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
        // INPUT_PULLUP: LOW = premuto, HIGH = rilasciato
        bool raw = (digitalRead(PIN_MAP[i]) == LOW);
        ButtonState& btn = _buttons[i];

        // Debounce: cambia stato solo se raw è stabile per DEBOUNCE_MS
        if (raw != btn.lastDebounced) {
            if ((nowMs - btn.lastChangeMs) >= DEBOUNCE_MS) {
                bool prev          = btn.lastDebounced;
                btn.lastDebounced  = raw;
                btn.lastChangeMs   = nowMs;

                // Genera edge
                if (!prev && raw)  btn.pressedFlag  = true;  // rising edge
                if (prev  && !raw) btn.releasedFlag = true;  // falling edge
            }
        } else {
            // Resetta il timer se il segnale è tornato allo stato debounced
            if (raw == btn.lastDebounced) btn.lastChangeMs = nowMs;
        }

        btn.currentRaw = raw;
    }
}

bool InputManager::wasPressed(ButtonID id) {
    ButtonState& btn = _buttons[_idx(id)];
    bool val = btn.pressedFlag;
    btn.pressedFlag = false;   // consume
    return val;
}

bool InputManager::wasReleased(ButtonID id) {
    ButtonState& btn = _buttons[_idx(id)];
    bool val = btn.releasedFlag;
    btn.releasedFlag = false;  // consume
    return val;
}

bool InputManager::isHeld(ButtonID id) const {
    return _buttons[_idx(id)].lastDebounced;
}