#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define PINS 4
#define LEFT_PIN 10
#define RIGHT_PIN 9
#define UP_PIN 8
#define DOWN_PIN 7
#define DEBOUNCE_DELAY 50 // ms

const int rs = 12, enable = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

int x = 0;
int y = 0;
char player = 'V'; // a white box

const int buttonPins[PINS] = {LEFT_PIN, RIGHT_PIN, UP_PIN, DOWN_PIN};
int buttonStates[PINS];
int lastButtonStates[PINS] = {LOW, LOW};

unsigned long lastDebounceTimes[PINS] = {0, 0};

void setup()
{
  for (int i = 0; i < PINS; i++)
  {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  Serial.begin(9600);
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setCursor(x, y);
}

void right()
{
  if (x < 15)
    x++;
}

void left()
{
  if (x > 0)
    x--;
}

void up()
{
  if (y == 1)
    y = 0;
}

void down()
{
  if (y == 0)
    y = 1;
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
        if (buttonPin == LEFT_PIN)
        {
          Serial.println("moving left");
          left();
        }
        else if (buttonPin == RIGHT_PIN)
        {
          Serial.println("moving right");
          right();
        }
        else if (buttonPin == UP_PIN)
        {
          Serial.println("moving up");
          up();
        }
        else if (buttonPin == DOWN_PIN)
        {
          Serial.println("moving down");
          down();
        }
      }
    }
  }

  // Here op...

  lastButtonStates[index] = reading;
}

void handle_clicks()
{
  for (int i = 0; i < PINS; i++)
  {
    debounce_button(i);
  }
}

void loop()
{
  lcd.clear();
  lcd.setCursor(x, y);
  lcd.print(player);
  handle_clicks();
}