#include "display.hpp"
#include "buttons.hpp"


void setup() {
  init_display();
  init_buttons();
}

void loop() {
  handle_button_clicks();
  handle_display();
  // handle_value_read();
}


