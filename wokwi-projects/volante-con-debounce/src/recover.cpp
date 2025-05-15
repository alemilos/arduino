// #include <Arduino.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// const int BUTTONS_COUNT = 8; // the number of buttons
// const int DEBOUNCE_DELAY = 50; // ms of debounce

// LiquidCrystal_I2C lcd(0x27, 20, 4); // initialize lcd

// const int buttons_pins[BUTTONS_COUNT] = { 1,2,3,4,5,6,7,8 };
// int buttons_pages[BUTTONS_COUNT] = { 0 };
// int buttons_states[BUTTONS_COUNT] = { LOW };
// int last_buttons_states[BUTTONS_COUNT] = { LOW };
// unsigned long last_debounce_times[BUTTONS_COUNT] = { 0 };

// // Utilities 
// void change_page(int index);
// int debounce_button(int index);
// void handle_button_click(int index);
// void buttons_controller();

// // Display Functions
// void display_menu();
// void display_page(int index);
// void display_fuel_temperature();
// void display_speed();
// void display_passenger_compartment();
// void display_fuel_volt();
// void display_ISuperC();
// void display_IsuperC_page_1();
// void display_IsuperC_page_2();
// void display_clacson();
// void display_IMotor();


// void setup() {
//     lcd.init();         // initialize the LCD
//     lcd.backlight();    // turn on backlight
//     display_menu();

//     for (size_t i = 0; i < BUTTONS_COUNT; i++) {
//         pinMode(buttons_pins[i], INPUT); // All Buttons are INPUT mode
//     }

// }

// void loop() {
//     // Read button states for each button pin
//     buttons_controller();
// }

// /*
//   Display the Home Menu
// */
// void display_menu() {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("1)FuelTmp 2)AbitTemp");
//     lcd.setCursor(0, 1);
//     lcd.print("3)Velocit 4)VoltFuel");
//     lcd.setCursor(0, 2);
//     lcd.print("5)ISuperC 6)IMotore");
//     lcd.setCursor(0, 3);
//     lcd.print("7)Clacson 8)Altro..");
// }

// void display_fuel_temperature() {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print(" Fuel Cell Temp.");
// }

// void display_passenger_compartment() {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print(" Temp. Abitacolo");
// }

// void display_speed() {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print(" Velocita'");
// }

// void display_fuel_volt() {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("Tensione Fuel Cell");
// }

// void display_clacson() {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("Beep Beep");
// }

// void display_IMotor() {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("Corrente Motore");
// }

// void display_ISuperC() {
//     // TODO make it use a variable instead of hardcoded "2"
//     if (buttons_pages[2] == 1) display_IsuperC_page_1();
//     else if (buttons_pages[2] == 2) display_IsuperC_page_2();
// }

// void display_IsuperC_page_1() {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("Corrente Super Cond.");
// }

// void display_IsuperC_page_2() {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("Page 2");
// }

// void buttons_controller() {
//     for (size_t i = 0; i < BUTTONS_COUNT; i++) {
//         // if (debounce_button(i) == 1) {
//         if (digitalRead(buttons_pins[i]) == HIGH) {
//             Serial.println(i);

//             // handle_button_click(i);
//         }
//         // }
//     }
// }

// void handle_button_click(int index) {
//     change_page(index);
//     display_page(index);
// }

// void display_page(int index) {
//     int button_pin = buttons_pins[index];
//     if (buttons_pages[index] == 0) {
//         display_menu();
//         return;
//     }

//     switch (button_pin) {
//     case 1:
//         display_fuel_temperature();
//         break;
//     case 2:
//         display_speed();
//         break;
//     case 3:
//         display_ISuperC();
//         break;
//     case 4:
//         display_clacson();
//         break;
//     case 5:
//         display_passenger_compartment();
//         break;
//     case 6:
//         display_fuel_volt();
//         break;
//     case 7:
//         display_IMotor();
//         break;
//     case 8:
//         display_menu();
//         break;
//     }
// }

// void change_page(int index) {
//     int button_pin = buttons_pins[index];

//     switch (button_pin) {
//     case 1:
//     case 2:
//     case 4:
//     case 5:
//     case 6:
//     case 7:
//         // Called for all the above cases
//         if (buttons_pages[index] == 0) {
//             buttons_pages[index] = 1;
//         }
//         else {
//             buttons_pages[index] = 0;
//         }
//         break;
//     case 3:
//         // Multiple pages handler for pin 3
//         if (buttons_pages[index] == 0) {
//             buttons_pages[index] = 1; // go to first page
//         }
//         else if (buttons_pages[index] == 1) {
//             buttons_pages[index] = 2; // go to second page
//         }
//         else {
//             buttons_pages[index] = 0; // reset to home
//         }
//         break;

//     default:
//         break;
//     }

//     // Reset all the pins pages (except the current one)
//     int ith_button_pin;
//     for (size_t i = 0; i < BUTTONS_COUNT; i++) {
//         ith_button_pin = buttons_pins[i];
//         if (button_pin != ith_button_pin) {
//             buttons_pages[i] = 0;
//         }
//     }
// }

// int debounce_button(int index)
// {
//     int changed = 0;
//     int button_pin = buttons_pins[index];
//     int reading = digitalRead(button_pin);

//     if (reading != last_buttons_states[index])
//     {
//         last_debounce_times[index] = millis();
//     }

//     if ((millis() - last_debounce_times[index]) > DEBOUNCE_DELAY)
//     {

//         if (reading != buttons_states[index])
//         {
//             buttons_states[index] = reading;

//             if (buttons_states[index] == HIGH)
//             {
//                 // the buttons changed state... click logic goes here.
//                 changed = 1;
//             }
//         }
//     }

//     last_buttons_states[index] = reading;
//     return changed;
// }
