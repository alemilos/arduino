#include <LiquidCrystal.h>
#include <Arduino.h>

const int rs = 12, enable = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

int x = 0;
int y = 0;


void setup()
{
  Serial.begin(9600);
  lcd.begin(20, 4);  // Initialize the LCD with 20 columns and 4 rows
  lcd.setCursor(0, 1);  // Set the cursor position to the top-left corner (0, 0)
}

void loop() {
  lcd.print("Hello World!");  // Print your text
}