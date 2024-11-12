#include <Arduino.h>

#define DEBOUNCE_DELAY 50
#define PINS 4

const int ledPins[PINS] = {13, 12, 11, 10};
int ledStates[PINS] = {HIGH, HIGH, HIGH, HIGH};

const int buttonPins[PINS] = {8, 7, 6, 5};
int buttonStates[PINS];
int lastButtonStates[PINS] = {LOW, LOW, LOW, LOW};

unsigned long lastDebounceTimes[PINS] = {0, 0, 0, 0};

void setup()
{
    Serial.begin(9600);
    for (size_t i = 0; i < PINS; i++)
    {
        pinMode(ledPins[i], OUTPUT);
        pinMode(buttonPins[i], INPUT_PULLUP);
        digitalWrite(ledPins[i], ledStates[i]);
    }
}

void debounce_button(int index)
{
    int buttonPin = buttonPins[index];
    int ledPin = ledPins[index];

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
                ledStates[index] = !ledStates[index];
                Serial.println("button clicked");
            }
        }
    }

    digitalWrite(ledPin, ledStates[index]);
    lastButtonStates[index] = reading;
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
}
