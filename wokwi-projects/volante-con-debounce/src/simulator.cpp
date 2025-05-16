#include "simulator.hpp"

unsigned long last_update_time = 0;
bool update_acknowledged = false;

int vehicle_speed;
int fuel_cell_temperature;
double fuel_cell_voltage;
int supercap_amperes[SUPERCAPACITORS_COUNT];
int overall_supercap_amperes;
int case_temp;
int motor_ampere;


void init_simulator() {
    randomSeed(analogRead(A0)); // Todo make sure A0 is free
}

int random_int_range(int min, int max) {
    return random(min, max + 1); // Arduino random is [min, max)
}
double random_double_range(int min, int max) {
    long scale = 10; // 1 decimal places of precision
    long scaled_min = (long)(min * scale);
    long scaled_max = (long)(max * scale);
    long result = random(scaled_min, scaled_max + 1);
    return (double)result / scale;
}


void simulate_telemetries() {
    unsigned long current_time = millis();
    if (current_time - last_update_time >= UPDATE_INTERVAL) {
        last_update_time = current_time;

        // Simulate telemetries
        vehicle_speed = random_int_range(0, 60); // km/h
        fuel_cell_temperature = random_int_range(40, 90); // °C
        fuel_cell_voltage = random_double_range(200, 400); // V
        case_temp = random_int_range(18, 30); // °C
        motor_ampere = random_int_range(100, 600); // A
        overall_supercap_amperes = random_int_range(100, 600); // A

        for (int i = 0; i < SUPERCAPACITORS_COUNT; i++) {
            supercap_amperes[i] = random_int_range(-50, 150); // A
        }


        update_acknowledged = false;
    }
}

/**
 * Change the udpate state as acknoledged
 */
void set_update_acknowledged() {
    update_acknowledged = true;
}

