#include <Arduino.h>

const int RELAY = 13;
bool isRelayUp = false;

void up(size_t ms);
void down(size_t ms);
void makeBeat(size_t ms);
void song();

void setup()
{
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
}

void loop()
{
  song();
}

void up(size_t ms)
{
  digitalWrite(RELAY, HIGH); // Ensure relay starts OFF if active HIGH
  isRelayUp = true;
  delay(ms);
}

void down(size_t ms)
{
  digitalWrite(RELAY, LOW); // Ensure relay starts OFF if active HIGH
  isRelayUp = false;
  delay(ms);
}

void makeBeat(size_t ms)
{
  if (isRelayUp)
    down(ms);
  else
    up(ms);
}

void song()
{
  // Base rhythm: Fast and strong
  for (int i = 0; i < 4; i++)
  {
    makeBeat(100);
    makeBeat(100);
    makeBeat(50);
    makeBeat(50);
  }
  delay(200);

  // Variation 1: Syncopated rhythm
  makeBeat(150);
  makeBeat(75);
  makeBeat(150);
  makeBeat(75);
  delay(100);

  // Fast burst
  for (int i = 0; i < 8; i++)
  {
    makeBeat(50);
  }
  delay(200);

  // Variation 2: Triplets
  for (int i = 0; i < 3; i++)
  {
    makeBeat(80);
  }
  delay(100);

  // Build-up
  for (int i = 0; i < 4; i++)
  {
    makeBeat(100);
    makeBeat(50);
  }
  delay(200);

  // Climax: Fast and intense
  for (int i = 0; i < 16; i++)
  {
    makeBeat(25);
  }
  delay(300);

  // Final rhythm: Strong finish
  makeBeat(200);
  makeBeat(100);
  makeBeat(200);
  makeBeat(100);
  delay(400);
}