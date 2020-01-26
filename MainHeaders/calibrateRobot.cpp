#include "calibrateRobot.h"

void calibrateRobot() {

  lineSensors.initThreeSensors();

  for (int i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      //spin right
      motor.setSpeeds(-CALIBERATE_SPEED, CALIBERATE_SPEED);
    }
    else
    {
      // spin left
      motor.setSpeeds(CALIBERATE_SPEED, -CALIBERATE_SPEED);
    }

    lineSensors.calibrate();
    delay(10);
  }

  for (int i = 0; i < 3; i++)
  {
    calibrateData[i] = lineSensors.calibratedMaximumOn[i]; 
    //use these values to check lines instead of QTR threshold
  }

  motor.setSpeeds(STOP_SPEED, STOP_SPEED);
}
