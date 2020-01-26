#pragma once

#include "TurnSensor.h"
#include <Zumo32U4.h>


//extern values will be declared as global variables in the main file

extern char Command;
extern bool autonomousControl;
extern bool searchRoom;
extern int STOP_SPEED;
void manualControl(int ls, int rs);
extern Zumo32U4Motors motor;
extern Zumo32U4ProximitySensors pSensors;
extern Zumo32U4Buzzer buzzer;
void turnLeft(int degrees, int tSpeed1, int tSpeed2);
void turnRight(int degrees, int tSpeed1, int tSpeed2);

void searchTheRoom(String room, int degree);


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
