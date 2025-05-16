#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <Arduino.h>

const int SUPERCAPACITORS_COUNT = 12;
const unsigned long UPDATE_INTERVAL = 2000; // ms

extern bool update_acknowledged;
extern unsigned long last_update_time;

// Telemetries

extern int vehicle_speed;
extern int fuel_cell_temperature;
extern double fuel_cell_voltage;
extern int supercap_amperes[SUPERCAPACITORS_COUNT];
extern int overall_supercap_amperes;
extern int case_temp;
extern int motor_ampere;


void init_simulator();
int random_int_range(int min, int max);
void simulate_telemetries();
void set_update_acknowledged();

#endif