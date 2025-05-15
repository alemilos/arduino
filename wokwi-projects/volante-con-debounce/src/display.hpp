#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "buttons.hpp"

extern int pages[BUTTONS_COUNT];
extern LiquidCrystal_I2C lcd;  // Just declare here

// Generic and Controllers

void init_display();
void handle_display();
void change_display_page();
void handle_display_page();
void reset_all_pages();

// Display Pages

void display_menu();
void display_fuel_cell_temp();
void display_speed();
void display_clacson();
void display_super_cap_ampere_page_1();
void display_super_cap_ampere_page_2();
void display_passenger_compartment_temp();
void display_fuel_cell_volt();
void display_motor_ampere();

#endif