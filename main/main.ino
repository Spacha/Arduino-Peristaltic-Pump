/**
 * Touch Screen driven Peristaltic Pump.
 * 
 * Authors: Emil Dark, Ville Kivikko, Miika Sikala, Lauri Klemettilä
 *          Oulu University, 2019
 */

#include "main.h"

// Constants
const int stepsPerRev = 200;  // this is motor specific
const int potPin = A0;        // for debug

// Construct a stepper instance
Stepper pump(stepsPerRev, 3, 4);

// Create button: NexButton(page_id, obj_id, obj_name)
NexButton dispenseBtn = NexButton(0, 2, "btn_dispense");

bool dispense = false;        // wheter we are operating the pump or not
int potVal = 0;               // defines the engine speed

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

  pinMode(5, OUTPUT);
}


void loop()
{
  nexLoop(nex_listen_list);
  potVal = analogRead(potPin);

  digitalWrite(5, dispense);

  // let it flow!
  if (dispense)
  {
    // map the pot val to a reasonable range
    operatePump(map(potVal, 0, 1023, 0, 100));
  } else {
    operatePump(0);
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
void operatePump(int speed)
{
  // if (speed > 0)
  pump.setSpeed(speed);
  pump.step(speed / 100);
}
