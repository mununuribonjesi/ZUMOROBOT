#pragma once
#include <Zumo32U4.h>


extern Zumo32U4LineSensors lineSensors;
extern Zumo32U4Motors motor;
extern int calibrateData[3];
extern int STOP_SPEED;
extern int CALIBERATE_SPEED;

void calibrateRobot();
