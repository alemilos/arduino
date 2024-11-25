#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

const int rs = 12, enable = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

const int power_min = 0;
const int power_max = 150; // kw

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
}


char * get_minutes(long milliseconds){
  int minutes = ((milliseconds/1000) /60 ) % 60;
   char* str = malloc(3 * sizeof(char)); // Allocate space for 2 digits + null terminator
    if (!str) {
        return NULL; // Handle allocation failure
    }

    if (minutes == 0){
      str[0] = 48;
      str[1] = 48;
    }else if (minutes < 10) {
        str[0] = 48;                // Prefix with '0'
        str[1] = minutes + 48;      // Convert number to ASCII
    } else {
        str[0] = (minutes/ 10) + 48; // Tens place
        str[1] = (minutes% 10) + 48; // Units place
    }
    str[2] = '\0'; // Null-terminate the string

    return str;
}

char * get_hours(long milliseconds){
  int hours = (((milliseconds / 1000) / 60 )/ 60) % 24;
  
  char* str = malloc(3 * sizeof(char)); // Allocate space for 2 digits + null terminator
    if (!str) {
        return NULL; // Handle allocation failure
    }
    if (hours == 0){
      str[0] = 48;
      str[1] = 48;
    } else if (hours< 10) {
        str[0] = 48;                // Prefix with '0'
        str[1] = hours + 48;      // Convert number to ASCII
    } else {
        str[0] = (hours/ 10) + 48; // Tens place
        str[1] = (hours % 10) + 48; // Units place
    }
    str[2] = '\0'; // Null-terminate the string

    return str;
}

char* get_seconds(long milliseconds) {
    int seconds = (milliseconds / 1000) % 60;
    char* str = malloc(3 * sizeof(char)); // Allocate space for 2 digits + null terminator
    if (!str) {
        return NULL; // Handle allocation failure
    }

    if (seconds < 10) {
        str[0] = 48;                // Prefix with '0'
        str[1] = seconds + 48;      // Convert number to ASCII
    } else {
        str[0] = (seconds / 10) + 48; // Tens place
        str[1] = (seconds % 10) + 48; // Units place
    }
    str[2] = '\0'; // Null-terminate the string

    return str;
}

void update_time(long milliseconds){
  char * seconds = get_seconds(milliseconds);
  char * minutes = get_minutes(milliseconds);
  char * hours = get_hours(milliseconds);

  lcd.setCursor(0,1);
  lcd.print(hours);
  lcd.setCursor(2,1);
  lcd.print(":");

  lcd.setCursor(3,1);
  lcd.print(minutes);
  lcd.setCursor(5,1);
  lcd.print(":");

  lcd.setCursor(6,1);
  lcd.print(seconds);

  free(seconds);
  free(minutes);
  free(hours);
}

int power_to_acc(int curr_power){
    int acc_min = 0;
    int acc_max = 40; // km/h
    Serial.println(power_min);
    Serial.println(power_max);

    // make the value passed fit into the range
    if (curr_power < power_min) curr_power = power_min;
    if (curr_power > power_max) curr_power = power_max;

    // return the math function for Linear Interpolation
    Serial.println(acc_min + ((acc_max - acc_min) / (power_max - power_min)) * (curr_power- power_min));
    return acc_min + ((acc_max - acc_min) / (power_max - power_min)) * (curr_power- power_min);
}

void update_acceleration(){
    int power = random(power_min, power_max);
    int acceleration = power_to_acc(power);

    Serial.println(acceleration);
    lcd.setCursor(0,0);
    lcd.print(power);

    lcd.setCursor(4,0);
    lcd.print("kw/h");

    lcd.setCursor(9,0);
    lcd.print(acceleration);

    lcd.setCursor(12,0);
    lcd.print("km/h");
}


void loop() {
  // put your main code here, to run repeatedly:
  long millliseconds = millis();
  update_time(millliseconds);
  update_acceleration();
  delay(500);
}
