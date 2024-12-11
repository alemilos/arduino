#include <Arduino.h>
#include <Servo.h>
#define esc 3

Servo DC_br;



const int potenziometroPin = A0;//PIN DEL POTENZIOMETRO
const int uscitaCorrentePin = 11; //mettere pin corretto dell' ESC
const float resistenzaTotalePotenziometro = 20000.00;  // Sostituisci con il valore effettivo
int Speed = 0;
int valorePotenziometro;
float resistenzaPotenziometro;
float tensionePotenziometro;
float potenza;

void setup() {
  pinMode(uscitaCorrentePin, OUTPUT);
 
  DC_br.attach(esc);
  Serial.begin(9600);
}

void loop() {
  valorePotenziometro = analogRead(potenziometroPin);

  resistenzaPotenziometro = (20000.00 / 1023.00) * valorePotenziometro;
  tensionePotenziometro = (5.00 / 1023.00) * valorePotenziometro;
  //float valoreCorrente = (tensionePotenziometro / resistenzaPotenziometro) * 1000;
  potenza = ((tensionePotenziometro * tensionePotenziometro) / (resistenzaPotenziometro +0.0001)) * 1000;

  Speed = map(valorePotenziometro, 0, 1023, 0, 180);
  DC_br.write(Speed);

 

 
  Serial.print(" - Resistenza potenziometro: ");
  if (resistenzaPotenziometro >= 20000)
  {
    Serial.print("20000");
  }
  else
  {
    Serial.print(resistenzaPotenziometro);
  }
  Serial.print(" - Tensione potenziometro: ");
  Serial.println(tensionePotenziometro);
  //Serial.print(" - Corrente assorbita(mA) : ");
  //Serial.println(valoreCorrente);
  Serial.print(" - Potenza assorbita(mW): ");
   if (potenza <= 0.05)
  {
    Serial.print("0");
  }
  else
  {
    Serial.print(potenza);
  }
  //Serial.print("Valore potenziometro: ");
  //Serial.print(valorePotenziometro);
  Serial.print("Speed:");
Serial.println(Speed);
  delay(1000);
}