#include "buttons.hpp"

/**
 * Button Pins Mapping:
 * - 6  --> Fuel Cell Temperature
 * - 7  --> Speed
 * - 8  --> Super Capacitors Ampere
 * - 9  --> Clacson
 * - 10 --> Passenger Compartment Temperature
 * - 11 --> Fuel Cell Voltage
 * - 12 --> Motor Ampere
 * - 13 --> Go Back Button
 */


int last_button_clicked = -1; // -1 means no button clicked yet

const int button_pins[BUTTONS_COUNT] = { 6, 7, 8, 9, 10, 11, 12, 13 };
int button_states[BUTTONS_COUNT] = { 0 };
int last_button_states[BUTTONS_COUNT] = { LOW };
unsigned long last_debounce_times[BUTTONS_COUNT] = { 0 };

void init_buttons() {
    for (size_t i = 0; i < BUTTONS_COUNT; i++) {
        pinMode(button_pins[i], INPUT);
    }
}

int debounce(int index) {
    // read the state of the switch into a local variable:
    int changed = 0;
    int button_pin = button_pins[index];
    int reading = digitalRead(button_pin);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != last_button_states[index]) {
        // reset the debouncing timer
        last_debounce_times[index] = millis();
    }

    if ((millis() - last_debounce_times[index]) > DEBOUNCE_DELAY) {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != button_states[index]) {
            button_states[index] = reading;

            // only toggle the LED if the new button state is HIGH
            if (button_states[index] == HIGH) {
                changed = 1;
            }
        }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    last_button_states[index] = reading;
    return changed;
}

void handle_button_clicks() {
    for (size_t i = 0; i < BUTTONS_COUNT; i++) {
        if (debounce(i) == 1) last_button_clicked = i;
    }
}

void reset_last_button_clicked() {
    last_button_clicked = -1;
}