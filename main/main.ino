/**
 * Touch Screen driven Peristaltic Pump.
 * 
 * Authors: Emil Dark, Ville Kivikko, Miika Sikala, Lauri Klemettilä
 *          Oulu University, 2019
 */

#include "main.h"

// Create button: NexButton(page_id, obj_id, obj_name)
NexButton dispenseBtn = NexButton(0, 2, "btn_dispense");

bool dispense = false;        // wheter we are operating the pump or not

const int stepPin     = 3;
const int dirPin      = 4;

// Pulse configuration
const int stepsPerRev = 10;
const int pulseWidth  = 10;

NexTouch *nex_listen_list[] = 
{
    &dispenseBtn,
    NULL
};


void setup()
{
  nexInit();

  // attach callbacks for events
  dispenseBtn.attachPop(dispenseBtnPopped);
  dispenseBtn.attachPush(dispenseBtnPushed);

  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}


void loop()
{
  nexLoop(nex_listen_list);

  if (dispense) {
    // map the pot val to a reasonable range
    // operatePump(map(potVal, 0, 1023, 0, 100));
    operatePump();
  }
}



/***********************************
 *          FUNCTIONS
 **********************************/

/**
 * Callback function for dispense button.
 * Called when button is pressed.
 * 
 * @return void
 */
void dispenseBtnPushed()
{
    dispense = true;
}

/**
 * Callback function for dispense button.
 * Called when button is released.
 * 
 * @return void
 */
void dispenseBtnPopped()
{
    dispense = false;
}


/**
 * Operates the pump at given speed.
 * 
 * @param int speed
 * @return void
 */
void operatePump()
{ 
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction

  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < stepsPerRev; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(pulseWidth);
    
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(pulseWidth); 
  }
  
  digitalWrite(dirPin,LOW); //Changes the rotations direction

  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < stepsPerRev; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(pulseWidth);
    
    digitalWrite(stepPin,LOW);
    delayMicroseconds(pulseWidth);
  }
  
  delay(1);
}
