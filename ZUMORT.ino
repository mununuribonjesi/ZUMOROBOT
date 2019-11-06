#include <Zumo32U4.h>
#include <Wire.h>

Zumo32U4LCD lcd;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;

int speedr = 0;
int speedl = 0;

//Serial1 communicates over XBee
//Serial communicates over USB cable

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);

}

void loop() {
      if(abs(speedr)>0){
        
        speedr=speedr-speedr/5;
    }
  if(abs(speedl)>0){
        speedl=speedl-speedl/5;
        }
        
  motors.setRightSpeed(speedr);
  
  motors.setLeftSpeed(speedl);
  
  if(Serial1.available() > 0){
      char val = Serial1.read();
    switch(val){
        case 'a':// turn left
        speedr=speedr+30000;
        break;
     case 'd': // turn right
        speedl=speedl+30000;
        break;
     case 'w': // forward
        speedr=speedr+30000;
        speedl=speedl+30000;
        break;
     case 's':// backward
        speedr=speedr-10000;
        speedl=speedl-10000;
        break;   
    }
    }

    delay(5);
    }  
