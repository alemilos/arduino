#include "display.hpp"
#include "simulator.hpp"

int pages[BUTTONS_COUNT] = { 0 }; // all pages start at zero (non-visible)
int current_page = 0;


LiquidCrystal_I2C lcd(0x27, LCD_COLS, LCD_ROWS);

void init_display() {
    lcd.init();
    lcd.backlight();
    display_home();
}

void handle_display() {
    if (last_button_clicked == -1) {
        if (current_page >= 0 && update_acknowledged == false) update_display();
        return;
    }
    change_display_page();
    handle_display_page(last_button_clicked);
    reset_last_button_clicked(); // make sure that last_button_clicked is reset so the display happen once
}

void update_display() {
    handle_display_page(current_page);
    set_update_acknowledged();
}

void change_display_page() {
    current_page = last_button_clicked; // Update the current page 

    switch (current_page) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        if (pages[current_page] == 0) pages[current_page] = 1; // go to first page
        else pages[current_page] = 0; // go back home 
        break;
    case 2: // super capacitor has 2 pages
        if (pages[current_page] == 0) pages[current_page] = 1; // go to first page 
        else if (pages[current_page] == 1) pages[current_page] = 2; // go to second page
        else pages[current_page] = 0; // go back home  
        break;
    default:
        break;
    }

    // Reset all pages except the last one
    for (int i = 0; i < BUTTONS_COUNT; i++) {
        if (i != current_page) pages[i] = 0;
    }

}

void reset_all_pages() {
    for (size_t i = 0; i < BUTTONS_COUNT; i++) {
        pages[i] = 0;
    }
}

void handle_display_page(int page) {
    if (pages[page] == 0) {
        display_home();
        return;
    }

    switch (page) {
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
    case 4: // Case Temperature
        display_case_temp();
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


void display_status_bar() {
    lcd_clear_line(0); // clear first line
    char buffer[21];
    snprintf(buffer, sizeof(buffer), "%2d C  %3d A  %2d Km/h", case_temp, overall_supercap_amperes, vehicle_speed);
    lcd.print(buffer);
}

void display_home() {
    lcd.clear();
    display_status_bar();

    // Vehicle speed 
    lcd.setCursor(0, 2);
    lcd.print("Premi l'ultimo bott-");
    lcd.setCursor(0, 3);
    lcd.print("tone per il Menu");
}

void display_fuel_cell_temp() {
    lcd.clear();
    display_status_bar();
    lcd.setCursor(2, 2);
    lcd.print(" Fuel Cell Temp.");
    lcd.setCursor(8, 3);
    lcd.print(fuel_cell_temperature);
    lcd.print(" C");
}

void display_speed() {
    lcd.clear();
    display_status_bar();
    lcd.setCursor(4, 2);
    lcd.print(" Velocita'");
    lcd.setCursor(6, 3);
    lcd.print(vehicle_speed);
    lcd.print(" km/h");
}

void display_clacson() {
    lcd.clear();
    display_status_bar();
    lcd.setCursor(5, 2);
    lcd.print("Beep Beep");
}

void display_super_cap_ampere_page_1() {
    lcd.clear();
    display_status_bar();

    char line2[21];
    char line3[21];
    char line4[21];

    snprintf(line2, sizeof(line2), "1) %3d A    4) %3d A", supercap_amperes[0], supercap_amperes[3]);
    snprintf(line3, sizeof(line2), "2) %3d A    5) %3d A", supercap_amperes[1], supercap_amperes[4]);
    snprintf(line4, sizeof(line2), "3) %3d A    6) %3d A", supercap_amperes[2], supercap_amperes[5]);

    lcd.setCursor(0, 1);
    lcd.print(line2);
    lcd.setCursor(0, 2);
    lcd.print(line3);
    lcd.setCursor(0, 3);
    lcd.print(line4);
}

void display_super_cap_ampere_page_2() {
    lcd.clear();
    display_status_bar();

    char line2[21];
    char line3[21];
    char line4[21];

    snprintf(line2, sizeof(line2), "7) %3d A   10) %3d A", supercap_amperes[6], supercap_amperes[9]);
    snprintf(line3, sizeof(line2), "8) %3d A   11) %3d A", supercap_amperes[7], supercap_amperes[10]);
    snprintf(line4, sizeof(line2), "9) %3d A   12) %3d A", supercap_amperes[8], supercap_amperes[11]);

    lcd.setCursor(0, 1);
    lcd.print(line2);
    lcd.setCursor(0, 2);
    lcd.print(line3);
    lcd.setCursor(0, 3);
    lcd.print(line4);
}

void display_case_temp() {
    lcd.clear();
    display_status_bar();
    lcd.setCursor(0, 2);
    lcd.print(" Temp. Contenitore");
    lcd.setCursor(8, 3);
    lcd.print(case_temp);
    lcd.print(" C");
}

void display_fuel_cell_volt() {
    char voltage_str[6];
    dtostrf(fuel_cell_voltage, 5, 1, voltage_str); // float values can't be displayed if they are not strings 

    lcd.clear();
    display_status_bar();
    lcd.setCursor(1, 2);
    lcd.print("Tensione Fuel Cell");
    lcd.setCursor(6, 3);
    lcd.print(voltage_str);
    lcd.print(" V");
}

void display_motor_ampere() {
    lcd.clear();
    display_status_bar();
    lcd.setCursor(2, 2);
    lcd.print("Corrente Motore");
    lcd.setCursor(7, 3);
    lcd.print(motor_ampere);
    lcd.print(" A");
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

// LCD Enhancments

/**
 * Clear the LCD line at given line, and reset the cursor to the start of that line
 */
void lcd_clear_line(int line) {
    lcd.setCursor(0, line);
    for (size_t i = 0; i < LCD_COLS; i++) {
        lcd.print(" ");
    }
    lcd.setCursor(0, line);
}