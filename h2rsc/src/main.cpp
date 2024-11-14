#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // Indirizzo I2C del display LCD 20x4

#define DEBOUNCE_DELAY 50
#define BUTTONS_NUM 8

const int buttonPins[BUTTONS_NUM] = {4,    5,   6,   7,  8,   9,  10,  11}; // Array dei pin dei pulsanti
const char letters[BUTTONS_NUM] =   {'A', 'B', 'C', 'D', 'E','F', 'G', 'H' };//, 'I'}; // Array delle lettere corrispondenti ai pulsanti

int buttonStates[BUTTONS_NUM];
int lastButtonStates[BUTTONS_NUM];

unsigned long lastDebounceTimes[BUTTONS_NUM] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  lcd.init();                      // Inizializza il display LCD
  lcd.backlight();                 // Accendi la retroilluminazione del display
  lcd.setCursor(0, 0);
  lcd.print("Premi un pulsante");
}

void debounce_button(int index)
{
    int buttonPin = buttonPins[index];

    int reading = digitalRead(buttonPin);

    if (reading != lastButtonStates[index])
    {
        lastDebounceTimes[index] = millis();
    }

    if ((millis() - lastDebounceTimes[index]) > DEBOUNCE_DELAY)
    {

        if (reading != buttonStates[index])
        {
            buttonStates[index] = reading;

            if (buttonStates[index] == HIGH)
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Hai premuto:");
                lcd.setCursor(0, 1);
                lcd.print(letters[i]);
            }
        }
    }
    lastButtonStates[index] = reading;
}

void debounce_buttons()
{
    for (size_t i = 0; i < BUTTONS_NUM; i++)
    {
        debounce_button(i);
    }
}

void loop() {
  // Controlla se uno dei pulsanti è stato premuto
  debounce_buttons();
}


