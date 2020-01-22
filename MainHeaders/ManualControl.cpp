
#include "ManualControl.h"

void manualControl(int ls, int rs)
{
  if (Serial1.available() > 0) {
    Serial1.flush();
    Command = Serial1.read();

    if (Command == 'w')
    {
      motor.setSpeeds(ls, rs);
    }

    if (Command == 'c')
    {
      autonomousControl = true;
      motor.setSpeeds(ls, rs);
    }

    if (Command == 'a')
    {
      motor.setSpeeds(-150, 80);
      delay(100);
      motor.setSpeeds(0, 0);
    }

    if (Command == 'd')
    {
      motor.setSpeeds(150, -80);
      delay(100);
      motor.setSpeeds(0, 0);
    }

    if (Command == 's')
    {
      motor.setLeftSpeed(-ls);
      motor.setRightSpeed(-rs);
      delay(200);
      motor.setSpeeds(0, 0);
    }
    if (Command == 'l')
    {
      turnLeft(90,100,100);
    }

    if (Command == 'f')
    {
      if (searchRoom == false)
      {
        searchRoom = true;
        autonomousControl = false;
        motor.setSpeeds(0, 0);
      }

    }

    else
    {
      searchRoom = false;
    }

    if (Command == 'r')
    {
      turnRight(90,100,100);
    }

    if (Command == 'p')
    {
      motor.setSpeeds(0, 0);
    }
  }
}


void turnLeft(int degrees,int tSpeed1,int tSpeed2) {
  turnSensorReset();
  String left = "left";
  motor.setSpeeds(-tSpeed1, tSpeed2);
  pSensors.read();
  searchTheRoom(left);
  int angle = 0;
  do {
    delay(1);
    turnSensorUpdate();
    angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
    pSensors.read();
    searchTheRoom(left);
  } while (angle < degrees);
  motor.setSpeeds(0, 0);
}

void turnRight(int degrees,int tSpeed1,int tSpeed2) {
  turnSensorReset();
  String right = "right";
  motor.setSpeeds(tSpeed1, -tSpeed2);
  pSensors.read();
  searchTheRoom(right);
  int angle = 0;
  do {
    delay(1);
    turnSensorUpdate();
    angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
    pSensors.read();
    searchTheRoom(right);
  } while (angle > -degrees);
  motor.setSpeeds(0, 0);
}

void searchTheRoom(String room)
{

  if (searchRoom == true) {
    if (pSensors.countsFrontWithLeftLeds() >= 6 || pSensors.countsFrontWithRightLeds() >= 6)
    {
      Serial1.println("found person in: " + room + ":" + "room :");
      
      searchRoom = false;
      buzzer.playFrequency(440, 200, 15);
      // Delay to give the tone time to finish.
      delay(1000);

    }
  }

}
