
#include "ManualControl.h"

ManualControl::ManualControl()
{
}
void ManualControl::moveRobot()
{
if (Serial1.available() > 0) {

    guiCommand = Serial1.read();
    
    if (guiCommand == 'w')
    {
      speedr = 400;
      speedl = 400;
      motor.setSpeeds(speedr, speedl);
    }

    if (guiCommand == 'a')
    {
      speedl = 200;
      motor.setRightSpeed(speedl);
      
    }

    if (guiCommand == 'd')
    {
      speedr = 200;
      motor.setLeftSpeed(speedr);
    }

    if (guiCommand == 's')
    {

   
      speedl = -400;
      speedr = -400;
      motor.setSpeeds(speedl,speedr);
    }

     if (guiCommand == 'p')
    {
      motor.setSpeeds(0, 0);
    }
  
}
}
