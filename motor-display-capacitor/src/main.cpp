#include <Arduino.h>
#include<Servo.h>
#include <LiquidCrystal.h>
#include <Wire.h>

const int rs = 12, enable = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

Servo DC_br;


const int power_min = 0;
const int power_max = 150; // kw

const int esc = 8;

const int POTENTIOMETER_PIN= A1;

const float resistenzaTotalePotenziometro = 10000.00;  // Sostituisci con il valore effettivo
int Speed = 0;
int valorePotenziometro;
float resistenzaPotenziometro;
float tensionePotenziometro;
float potenza;

void setup() {
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  Serial.begin(9600);
  DC_br.attach(esc);
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

void update_capacitor_potentiometer(){
  int capacitorValue = analogRead(A0);
  int potentiometerValue= analogRead(POTENTIOMETER_PIN);

  double capacitorVolt = (capacitorValue * 5) / 1023.0;
  double potentiometerVolt= (potentiometerValue * 5) / 1023.0;

  char capacitorString[64];
  char potentiometerString[64];
  
  dtostrf(capacitorVolt, 3, 2, capacitorString);
  dtostrf(potentiometerVolt, 3, 2, potentiometerString);


  lcd.setCursor(0,0);
  lcd.print(capacitorString);
  lcd.setCursor(12,0);
  lcd.print(potentiometerString);


}

void loop() {
  valorePotenziometro = analogRead(POTENTIOMETER_PIN);

  resistenzaPotenziometro = (10000.00 / 1023.00) * valorePotenziometro;
  tensionePotenziometro = (5.00 / 1023.00) * valorePotenziometro;
  //float valoreCorrente = (tensionePotenziometro / resistenzaPotenziometro) * 1000;
  potenza = ((tensionePotenziometro * tensionePotenziometro) / (resistenzaPotenziometro +0.0001)) * 1000;

  Speed = map(valorePotenziometro, 0, 1023, 0, 180);
Serial.println(Speed);
  DC_br.write(Speed);

  long millliseconds = millis();
  update_time(millliseconds);
  update_capacitor_potentiometer();

  delay(200);
}