#include "ManualControl.h"
#include "TurnSensor.h"
#include <zumo32U4.h>
L3G gyro;
Zumo32U4LCD lcd;

//--Helper Function 

int32_t getAngle() {
  //turn angle is a variable thats in the TurnSensor.cpp file
  //This return just converts the number into degrees turned since the last sensor reset
  return (((int32_t)turnAngle >>16)* 360) >>16;
}

void setup() {
  Serial1.begin(9600);
}

void loop() {
 ManualControl MC;
 MC.moveRobot();
}
