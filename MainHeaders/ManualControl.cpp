
#include "ManualControl.h"


//move the robot depending on the gui command
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
      turnLeft(90, 100, 100);
    }

    if (Command == 'f')
    {

      searchRoom = true;
      autonomousControl = false;
      motor.setSpeeds(0, 0);
      turnSensorReset();
    }



    if (Command == 'r')
    {
      turnRight(90, 100, 100);
    }

    if (Command == 'p')
    {
      motor.setSpeeds(0, 0);
    }
  }
}

//turn robot using gyro
void turnLeft(int degrees, int tSpeed1, int tSpeed2) {
  turnSensorReset();
  String left = "left";
  motor.setSpeeds(-tSpeed1, tSpeed2);
  pSensors.read();
  int angle = 0;
  do {
    delay(1);
    turnSensorUpdate();
    angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
    pSensors.read();
  } while (angle < degrees);
  motor.setSpeeds(0, 0);
  searchTheRoom(left, 90);
}

void turnRight(int degrees, int tSpeed1, int tSpeed2) {
  turnSensorReset();
  String right = "right";
  motor.setSpeeds(tSpeed1, -tSpeed2);
  pSensors.read();
  int angle = 0;
  do {
    delay(1);
    turnSensorUpdate();
    angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
    pSensors.read();
  } while (angle > -degrees);
  motor.setSpeeds(0, 0);
  searchTheRoom(right, 90);
}


//function to search the room using proximity sensors 

void searchTheRoom(String room, int turn)
{

  if (searchRoom == true) {
    if (pSensors.countsFrontWithLeftLeds() >= 6 || pSensors.countsFrontWithRightLeds() >= 6)
    {
      Serial1.println("found person in: " + room + ":" + "room :");

      searchRoom = false;
      buzzer.playFrequency(440, 200, 15);
      
      if (room == "left")
      {
        turnRight(turn, 100, 100);
      }
      else
      {
        turnLeft(turn, 100, 100);
      }
      delay(1000);
    }
  }

}
