#include "ManualControl.h"
#include "TurnSensor.h"
#include <zumo32U4.h>
#define NUM_SENSORS 3
#define QTR_THRESHOLD     700 // microseconds

// These might need to be tuned for different motor types.
#define REVERSE_SPEED     50  // 0 is stopped, 400 is full speed
#define TURN_SPEED        100
#define STOP_SPEED        0
#define FORWARD_SPEED     80
#define REVERSE_DURATION  200  // ms
#define TURN_DURATION     100  // ms
#define CALIBERATE_SPEED  200
#define leftSensor 0
#define centerSensor 1
#define rightSensor 2
int calibrateData[3];
int count = 1;

Zumo32U4Buzzer buzzer;
int lineSensorValues[NUM_SENSORS];
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proximitySensors;
Zumo32U4Motors motor;
L3G gyro;
int countsLeft;
int countsRight;
char guiCommand;
int speedl = 110;
int speedr = 97;
bool autonomousControl = false;
bool searchRoom = false;

const char fugue[] PROGMEM =
  "! O5 L16 agafaea dac+adaea fa<aa<bac#a dac#adaea f"
  "O6 dcd<b-d<ad<g d<f+d<gd<ad<b- d<dd<ed<f+d<g d<f+d<gd<ad"
  "L8 MS <b-d<b-d MLe-<ge-<g MSc<ac<a ML d<fd<f O5 MS b-gb-g"
  "ML >c#e>c#e MS afaf ML gc#gc# MS fdfd ML e<b-e<b-"
  "O6 L16ragafaea dac#adaea fa<aa<bac#a dac#adaea faeadaca"
  "<b-acadg<b-g egdgcg<b-g <ag<b-gcf<af dfcf<b-f<af"
  "<gf<af<b-e<ge c#e<b-e<ae<ge <fe<ge<ad<fd"
  "O5 e>ee>ef>df>d b->c#b->c#a>df>d e>ee>ef>df>d"
  "e>d>c#>db>d>c#b >c#agaegfe f O6 dc#dfdc#<b c#4";

void setup() {

  Serial1.begin(9600);

  delay(3000);
  calibrateRobot();
  turnSensorSetup();
  delay(500);
  turnSensorReset();
  proximitySensors.initThreeSensors();

}

void loop() {

  if (autonomousControl == true)
  {
    if (count <= 1)
    {
      count = 1;
      Serial1.println("Autonomous\n");
      count++;
    }

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
      motor.setSpeeds(speedl, speedr);
    }

    if (guiCommand == 'c')
    {
      autonomousControl = true;
      motor.setSpeeds(speedl, speedr);
    }

    if (guiCommand == 'a')
    {
      motor.setSpeeds(-150, 80);
      delay(100);
      motor.setSpeeds(STOP_SPEED, STOP_SPEED);
    }

    if (guiCommand == 'd')
    {
      motor.setSpeeds(150, -80);
      delay(100);
      motor.setSpeeds(STOP_SPEED, STOP_SPEED);

    }

    if (guiCommand == 's')
    {
      motor.setLeftSpeed(-speedl);
      motor.setRightSpeed(-speedr);
      delay(200);
      motor.setSpeeds(STOP_SPEED, STOP_SPEED);
    }
    if (guiCommand == 'l')
    {
      turnLeft(90);
    }

    if (guiCommand == 'f')
    {
        if(searchRoom == false)
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

    if (guiCommand == 'r')
    {
      turnRight(90);
    }

    if (guiCommand == 'p')
    {
      motor.setSpeeds(0, 0);
    }
  }
}

void turnLeft(int degrees) {
  turnSensorReset();
  String left = "left";
  motor.setSpeeds(-TURN_SPEED, TURN_SPEED);
  proximitySensors.read();
  searchTheRoom(left);
  int angle = 0;
  do {
    delay(1);
    turnSensorUpdate();
    angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
    proximitySensors.read();
    searchTheRoom(left);
  } while (angle < degrees);
  motor.setSpeeds(0, 0);
}


void searchTheRoom(String room)
{
 
  if (searchRoom == true) {
    if (proximitySensors.countsFrontWithLeftLeds() >= 6 || proximitySensors.countsFrontWithRightLeds() >= 6)
    {
      Serial1.println("found person in: " + room + ":" +"room :" + count + "");
      count++;
      searchRoom= false;
      buzzer.playFrequency(440, 200, 15);
      // Delay to give the tone time to finish.
      delay(1000);

    }
  }

}
void turnRight(int degrees) {
  turnSensorReset();
  String right = "right";
  motor.setSpeeds(TURN_SPEED, -TURN_SPEED);
  proximitySensors.read();
  searchTheRoom(right);
  int angle = 0;
  do {
    delay(1);
    turnSensorUpdate();
    angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
    proximitySensors.read();
    proximitySensors.read();
    searchTheRoom(right);
  } while (angle > -degrees);
  motor.setSpeeds(0, 0);
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
      count = 0;
    }

    lineSensors.readCalibrated(lineSensorValues);

    if (detectWall(cSensor))
    {
      motor.setSpeeds(-80, -80);
      delay(250);
      motor.setSpeeds(0, 0);
      autonomousControl = false;
      Serial1.println("Hit wall \n");
      count = 0;
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

void calibrateRobot() {

  lineSensors.initThreeSensors();

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
}
