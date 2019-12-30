#ifndef ManualControl_h
#define ManualControl_h
#include <Zumo32U4.h>
#include <Arduino.h>

class ManualControl {
  public:
    ManualControl();
    Zumo32U4Motors motor;
    char guiCommand;
    void moveRobot();
    int speedr = 0;
    int speedl = 0;
    bool flip = true;
};

#endif
