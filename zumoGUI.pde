import controlP5.*;
import processing.serial.*;
ControlP5 cp5;
Serial myPort; //creates local serial object from serial library

int val; //data received from serial port

void setup(){
  
  size(600,300);

  cp5 = new ControlP5(this);
  
  printArray(Serial.list());
  
 String portName = Serial.list()[1];
 myPort = new Serial(this, portName, 9600);
  
  cp5.addButton("forward").setPosition(120,10).setSize(50,50)
 .setColorBackground(color(30,144,255))
 .setColorLabel(color(0,0,0));
 
   cp5.addButton("left").setPosition(30,100).setSize(50,50)
 .setColorBackground(color(0,255,0))
 .setColorLabel(color(0,0,0));
 
    cp5.addButton("right").setPosition(210,100).setSize(50,50)
 .setColorBackground(color(255,255,0))
 .setColorLabel(color(0,0,0));
  
  cp5.addButton("reverse").setPosition(120,200).setSize(50,50)
 .setColorBackground(color(255,0,0))
 .setColorLabel(color(0,0,0));
 
  cp5.addButton("stop").setPosition(400,100).setSize(150,50)
 .setColorBackground(color(255,0,0))
 .setColorLabel(color(0,0,0));
  
 
}

void draw(){
    background(0,0,0);
 {
  if ( myPort.available() > 0) {  // If data is available,
         // read it and store it in val
  }            // Set background to white
  if (val == 0) {              // If the serial value is 0,
    fill(0);                   // set fill to black
  } 
  else {                       // If the serial value is not 0,
    fill(204);                 // set fill to light gray
  }
  rect(50, 50, 100, 100);
}
  

}

void forward(){
  myPort.write('w');
}

void left(){
  myPort.write('a');
}

void right(){
  myPort.write('d');
}

void reverse(){
  myPort.write('s');
}
