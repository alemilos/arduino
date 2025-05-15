#include "display.hpp"

int pages[BUTTONS_COUNT] = { 0 }; // all pages start at zero (non-visible)

LiquidCrystal_I2C lcd(0x27, 20, 4);

void init_display() {
    lcd.init();
    lcd.backlight();
    display_menu();
}


void display_menu() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1)FuelTmp 2)AbitTemp");
    lcd.setCursor(0, 1);
    lcd.print("3)Velocit 4)VoltFuel");
    lcd.setCursor(0, 2);
    lcd.print("5)ISuperC 6)IMotore");
    lcd.setCursor(0, 3);
    lcd.print("7)Clacson 8)Altro..");
}

void handle_display() {
    if (last_button_clicked == -1) return;
    change_display_page();
    handle_display_page();
    reset_last_button_clicked(); // make sure that last_button_clicked is reset so the display happen once
}

void change_display_page() {
    // check if the page needs to be updated
    switch (last_button_clicked) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
        if (pages[last_button_clicked] == 0) pages[last_button_clicked] = 1; // go to first page
        else pages[last_button_clicked] = 0; // go back menu
        break;
    case 2: // super capacitor has 2 pages
        if (pages[last_button_clicked] == 0) pages[last_button_clicked] = 1; // go to first page 
        else if (pages[last_button_clicked] == 1) pages[last_button_clicked] = 2; // go to second page
        else pages[last_button_clicked] = 0; // go back menu
        break;
    case 7: // last button handles the go back to menu
        reset_all_pages();
        break;
    default:
        break;
    }

    // Reset all pages except the last one
    for (int i = 0; i < BUTTONS_COUNT; i++) {
        if (i != last_button_clicked) pages[i] = 0;
    }

}

void reset_all_pages() {
    for (size_t i = 0; i < BUTTONS_COUNT; i++) {
        pages[i] = 0;
    }
}

void handle_display_page() {
    if (pages[last_button_clicked] == 0) {
        display_menu();
        return;
    }

    switch (last_button_clicked) {
    case 0: // Fuel Cell Temperature
        display_fuel_cell_temp();
        break;
    case 1: // Speed
        display_speed();
        break;
    case 2: // Ampere super capacitors 
        if (pages[2] == 1) display_super_cap_ampere_page_1();
        else if (pages[2] == 2) display_super_cap_ampere_page_2();
        break;
    case 3: // Clacson
        display_clacson();
        break;
    case 4: // Passenger Compartment Temperature
        display_passenger_compartment_temp();
        break;
    case 5: // Fuel Cell Voltage
        display_fuel_cell_volt();
        break;
    case 6: // Ampere Motor
        display_motor_ampere();
        break;
    case 7: //  
        display_menu();
        break;
    }

}


void display_fuel_cell_temp() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Fuel Cell Temp.");
    lcd.setCursor(8, 2);
    lcd.print(20);
    lcd.print(" C");
}

void display_speed() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Velocita'");
    lcd.setCursor(8, 2);
    lcd.print(40);
    lcd.print(" km/h");
}

void display_clacson() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Beep Beep");
}

void display_super_cap_ampere_page_1() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Corrente SuperCap. 1");
    lcd.setCursor(0, 1);
    lcd.print("1) 20  A  4) 40  A");
    lcd.setCursor(0, 2);
    lcd.print("2) 39  A  5) 120 A");
    lcd.setCursor(0, 3);
    lcd.print("3) 200 A  6) 112 A");
}

void display_super_cap_ampere_page_2() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Corrente SuperCap. 2");
    lcd.setCursor(0, 1);
    lcd.print("7) 11  A  10) 23 A");
    lcd.setCursor(0, 2);
    lcd.print("8) 137 A  11) 74 A");
    lcd.setCursor(0, 3);
    lcd.print("9) 99  A  12) 7  A");
}

void display_passenger_compartment_temp() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Temp. Abitacolo");
    lcd.setCursor(8, 2);
    lcd.print(29);
    lcd.print(" C");
}

void display_fuel_cell_volt() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tensione Fuel Cell");
    lcd.setCursor(8, 2);
    lcd.print(60);
    lcd.print(" V");
}

void display_motor_ampere() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Corrente Motore");
    lcd.setCursor(8, 2);
    lcd.print(100);
    lcd.print(" A");
}