#include "AutonomousControl.h"
#include "TurnSensor.h"

//if sensor detects wall return true response

bool detectWall(int sensor)
{
  bool response = false;

  if (lineSensorValues[sensor] > calibrateData[sensor] / 2)
  {
    response = true;
  }

  return response;
}

//check if sensors have hit wall if not just keep robot in between the lines

void hitWall(int sensor, int cSensor, int negativeTurnValue, int positiveTurnValue)
{
  int i = 0;
  while (autonomousControl == true && i < 80)
  {
    i++;

    delay(1);

    lineSensors.readCalibrated(lineSensorValues);

    if (detectWall(sensor))
    {
      motor.setSpeeds(-80, -80);
      delay(250);
      motor.setSpeeds(0, 0);
      autonomousControl = false;
      Serial1.println("Hit wall \n");
      turnSensorReset();
    }

    lineSensors.readCalibrated(lineSensorValues);

    if (detectWall(cSensor))
    {
      motor.setSpeeds(-80, -80);
      delay(250);
      motor.setSpeeds(0, 0);
      autonomousControl = false;
      Serial1.println("Hit wall \n");
      turnSensorReset();
    }
  }


  if (autonomousControl == true)
  {
    delay(1);
    motor.setSpeeds(negativeTurnValue, positiveTurnValue);
    delay(TURN_DURATION);
    motor.setSpeeds(speedl, speedr);
  }
}


//autonomous control function 

void automaticControl(){
  if (autonomousControl == true)
  {

    lineSensors.readCalibrated(lineSensorValues);

    if (detectWall(leftSensor))
    {
      lineSensors.readCalibrated(lineSensorValues);
      hitWall(rightSensor, centerSensor, TURN_SPEED, -TURN_SPEED);
    }

    lineSensors.readCalibrated(lineSensorValues);

    if (detectWall(rightSensor))
    {
      lineSensors.readCalibrated(lineSensorValues);
      hitWall(leftSensor, centerSensor, -TURN_SPEED, TURN_SPEED);
    }
  }
}
