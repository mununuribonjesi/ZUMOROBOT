#ifndef AutonomousControl_h
#define AutonomousControl_h

#include "ZumoMotors.h"
#include <Arduino.h>
#include "TurnSensor.h"


#define NUM_SENSORS 5

class AutonomousControl {
  public:
    Zumo32U4LineSensors lineSensors;
    uint16_t lineSensorValues[NUM_SENSORS];
    bool useEmitters = true;
    uint8_t selectedSensorIndex = 0;
    void setup();
    void loadCustomCharacters();
  
  private:
};
#endif
