#ifndef BUTTONS_HPP
#define BUTTONS_HPP

#include <Arduino.h>

const int BUTTONS_COUNT = 8;
const int DEBOUNCE_DELAY = 50;
extern int last_button_clicked;

extern const int button_pins[BUTTONS_COUNT];
extern int button_states[BUTTONS_COUNT];
extern int last_button_states[BUTTONS_COUNT];
extern unsigned long last_debounce_times[BUTTONS_COUNT];

void init_buttons();
int debounce(int index);
void handle_button_clicks();
void reset_last_button_clicked();

#endif 