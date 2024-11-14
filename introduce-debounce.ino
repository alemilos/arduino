#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // Indirizzo I2C del display LCD 20x4

const int buttonPins[] = {4, 5, 6, 7,8,9,10,11}; // Array dei pin dei pulsanti
const char lettere[] = {'A', 'B', 'C', 'D', 'E','F','G','H','I'}; // Array delle lettere corrispondenti ai pulsanti
const int numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);

void setup() {
  lcd.init();                      // Inizializza il display LCD
  lcd.backlight();                 // Accendi la retroilluminazione del display
  lcd.setCursor(0, 0);
  lcd.print("Premi un pulsante");
}

void loop() {
  // Controlla se uno dei pulsanti è stato premuto
  for (int i = 0; i < numButtons; ++i) {
    if (digitalRead(buttonPins[i]) == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Hai premuto:");
      lcd.setCursor(0, 1);
      lcd.print(lettere[i]);
      delay(10); // Aggiungi un ritardo per evitare il rimbalzo dei pulsanti
    }
  }
}