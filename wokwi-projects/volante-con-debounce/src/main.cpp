#include "simulator.hpp"
#include "display.hpp"
#include "buttons.hpp"


void setup() {
  Serial.begin(9600);
  init_display();
  init_buttons();
  init_simulator();
}

void loop() {
  simulate_telemetries();
  handle_button_clicks();
  handle_display();
  // handle_value_read();
}


