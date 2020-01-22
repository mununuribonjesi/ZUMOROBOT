#pragma once
#include <Zumo32U4.h>


extern int calibrateData[3];
bool detectWall(int sensor);
extern Zumo32U4LineSensors lineSensors;
extern bool autonomousControl;
extern Zumo32U4Motors motor;
extern int NUM_SENSORS;
extern int lineSensorValues[3];
extern int TURN_DURATION;
extern int speedl;
extern int speedr;
extern int leftSensor;
extern int centerSensor;
extern int rightSensor;
extern int TURN_SPEED;
void hitWall(int sensor, int cSensor, int negativeTurnValue, int positiveTurnValue);
void automaticControl();
