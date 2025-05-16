#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "buttons.hpp"

extern int pages[BUTTONS_COUNT];
extern int current_page;

const int LCD_ROWS = 4;
const int LCD_COLS = 20;
extern LiquidCrystal_I2C lcd;

// LCD Enhancments 

void lcd_clear_line(int line);

// Generic and Controllers

void init_display();
void handle_display();
void update_display();
void change_display_page();
void handle_display_page(int page);
void reset_all_pages();

// Display Pages


void display_status_bar();
void display_home();
void display_fuel_cell_temp();
void display_speed();
void display_clacson();
void display_super_cap_ampere_page_1();
void display_super_cap_ampere_page_2();
void display_case_temp();
void display_fuel_cell_volt();
void display_motor_ampere();
void display_menu();

#endif