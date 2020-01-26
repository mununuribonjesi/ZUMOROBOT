#include "ManualControl.h"
#include "TurnSensor.h"
#include <zumo32U4.h>
#include "AutonomousControl.h"
#include <Zumo32U4.h>
#include "calibrateRobot.h"
#define FORWARD_SPEED     80
#define REVERSE_DURATION  200  // ms

//Global Variables 

int leftSensor = 0;
int centerSensor = 1;
int rightSensor = 2;

int TURN_SPEED = 100;
int STOP_SPEED = 0;
int CALIBERATE_SPEED = 200;
int calibrateData[3];
int TURN_DURATION = 100;  // ms
int NUM_SENSORS = 3;
int lineSensorValues[3];
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motor;
Zumo32U4ProximitySensors pSensors;
Zumo32U4Buzzer buzzer;

char Command;
L3G gyro;
int countsLeft;
int countsRight;
int speedl = 110;
int speedr = 97;
bool autonomousControl = false;
bool searchRoom = false;


void setup() {

  Serial1.begin(9600);
  delay(3000);
  calibrateRobot();
  turnSensorSetup();
  delay(500);
  turnSensorReset();
  pSensors.initThreeSensors();

}

void loop() {
  //autonomous control
  automaticControl();
  //manual control 
  manualControl(speedl,speedr);
}
