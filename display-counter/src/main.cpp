#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

const int DEBOUNCE_DELAY = 50;
const int PINS = 3;
int count = 0;


void writeToScreen();

const int rs = 12, enable = 11, d4 = 3, d5 = 4, d6 = 5, d7 = 6;
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

const int buttonPins[PINS] = { 8,2 ,7};
int buttonStates[PINS];
int lastButtonStates[PINS] = {LOW, LOW, LOW};

unsigned long lastDebounceTimes[PINS] = {0, 0, 0};

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting");
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print("Sto funzionando ?");

    for (size_t i = 0; i < PINS; i++)
    {
        pinMode(buttonPins[i], INPUT);
    }

    delay(1000);
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
              writeToScreen();
            }
        }
    }

    lastButtonStates[index] = reading;
}


void writeToScreen(){
  Serial.println("button clicked");
  lcd.clear();
  lcd.print(count++);
}

void debounce_buttons()
{
    for (size_t i = 0; i < PINS; i++)
    {
        debounce_button(i);
    }
}

void loop()
{
    debounce_buttons();
     lcd.setCursor(0,1);
    lcd.print(millis());
}
