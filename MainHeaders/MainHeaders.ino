#include "ManualControl.h"
#include "TurnSensor.h"
#include <zumo32U4.h>

#define NUM_SENSORS 3

#define QTR_THRESHOLD     700 // microseconds

// These might need to be tuned for different motor types.
#define REVERSE_SPEED     50  // 0 is stopped, 400 is full speed
#define TURN_SPEED        120
#define STOP_SPEED        0
#define FORWARD_SPEED     80
#define REVERSE_DURATION  200  // ms
#define TURN_DURATION     100  // ms
#define CALIBERATE_SPEED  200
#define leftSensor 0
#define centerSensor 1
#define rightSensor 2
int calibrateData[3];

int lineSensorValues[NUM_SENSORS];
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motor;
char guiCommand;
int  speedl = 80;
int speedr = 67;
bool b = false;


//--Helper Function

/*int32_t getAngle() {
  //turn angle is a variable thats in the TurnSensor.cpp file
  //This return just converts the number into degrees turned since the last sensor reset
  return (((int32_t)turnAngle >>16)* 360) >>16;
  }*/

void setup() {
  Serial1.begin(9600);
  delay(3000);
  calibrateRobot();

}

void loop() {

  if (b == true)
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



  if (Serial1.available() > 0) {
    Serial1.flush();
    guiCommand = Serial1.read();

    if (guiCommand == 'w')
    {
      b = true;

      motor.setSpeeds(speedl, speedr);

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


      speedl = -100;
      speedr = -100;
      motor.setSpeeds(speedl, speedr);
    }

    if (guiCommand == 'p')
    {
      motor.setSpeeds(0, 0);
    }

  }
}


bool detectWall(int sensor)
{
  bool response = false;

  if (lineSensorValues[sensor] > calibrateData[sensor] / 2)
  {
    response = true;
  }

  return response;
}

void hitWall(int sensor, int cSensor, int negativeTurnValue, int positiveTurnValue)
{
  Serial1.println("hit right wall");
  int i = 0;
  while (b == true && i < 100)
  {
    i++;
    
    delay(0.6);
    
    lineSensors.readCalibrated(lineSensorValues);

    if (detectWall(sensor))
    {

      motor.setSpeeds(-80, -80);
      delay(600);
      Serial1.println("hit leftwall");
      motor.setSpeeds(0, 0);
      b = false;
    }
    
    lineSensors.readCalibrated(lineSensorValues);
   
    if (detectWall(cSensor))
    {
      motor.setSpeeds(-80, -80);
      delay(600);
      Serial1.println("hit center sensor");
      motor.setSpeeds(0, 0);
      b = false;
    }

  }

  if (b == true)
  {
    delay(1);
    motor.setSpeeds(negativeTurnValue, positiveTurnValue);
    delay(TURN_DURATION);
    motor.setSpeeds(speedl, speedr);
  }
}

void calibrateRobot() {

  lineSensors.initThreeSensors();

  Serial1.print(readBatteryMillivolts(), DEC);
  Serial1.println("");

  for (int i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      // On above numbers spin right
      motor.setSpeeds(-CALIBERATE_SPEED, CALIBERATE_SPEED);

    }
    else
    {
      // on other numbers spin left
      motor.setSpeeds(CALIBERATE_SPEED, -CALIBERATE_SPEED);
    }

    lineSensors.calibrate();
    delay(10);
  }

  for (int i = 0; i < NUM_SENSORS; i++)
  {
    calibrateData[i] = lineSensors.calibratedMaximumOn[i];
  }

  motor.setSpeeds(STOP_SPEED, STOP_SPEED);

  Serial1.println(String(calibrateData[0]));
  Serial1.println(String(calibrateData[2]));

}
