/**
 * Touch Screen driven Peristaltic Pump.
 * 
 * Authors: Emil Dark, Ville Kivikko, Miika Sikala, Lauri Klemettilä
 *          Oulu University, 2019
 */

#include "main.h"

// Motor
const int stepsPerRev = 200;  // this is motor specific
const int potPin = A0;

// Construct a stepper instance
Stepper pump(stepsPerRev, 3, 4);

bool dispense = false;
int potVal = 0;



void setup()
{
  // Serial.begin(9600);

  // debug
  dispense = true;
}


void loop()
{
  potVal = analogRead(potPin);

  // let it flow!
  if (dispense)
  {
    // we must map the pot val to a reasonable range
    operatePump(map(potVal, 0, 1023, 0, 100));
  }
}

/**
 * Operates the pump at predefined speed.
 * 
 * @param int speed
 * @return void
 */
void operatePump(int speed)
{
  if (speed > 0)
  {
    pump.setSpeed(speed);
    pump.step(speed / 100);
  }
}
