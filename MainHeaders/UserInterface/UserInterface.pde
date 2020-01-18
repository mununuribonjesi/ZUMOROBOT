import controlP5.*;
import processing.serial.*;
ControlP5 cp5;
Serial myPort; //creates local serial object from serial library

boolean [] keys = new boolean[128];
ListBox l;
int val; //data received from serial port
int inBuffer;
String text;
int cnt =0;
Textarea myTextarea;


 void setup(){
  
  size(700,600);

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
 
   myTextarea = cp5.addTextarea("txt")
                  .setPosition(50,300)
                  .setSize(200,200)
                  .setFont(createFont("arial",12))
                  .setLineHeight(14)
                  .setColor(color(128))
                  .setColorBackground(color(255,100))
                  .setColorForeground(color(255,100));
 

  }
  




void draw(){
    background(0,0,0);  


  if ( myPort.available() > 0) {  // If data is available,
     myTextarea.setText(myPort.readString());

  }            // Set background to white
  if (val == 0) {              // If the serial value is 0,
    fill(0);                   // set fill to black
  } 
  else {                       // If the serial value is not 0,
    fill(204);                 // set fill to light gray
  }
  rect(50, 50, 100, 100);
}


void move()
{
  
  if(keys['w']) 
  {
    myPort.write('w');
  }

  else if(keys['a']) 
  {
    myPort.write('a');
  }
  
  else if(keys['s']) 
  {
    myPort.write('s');
  }
   
  else if(keys['d']) 
  {
    myPort.write('d');
  }
  else 
  {
    myPort.write('p');
  }
  
}


void keyPressed()
{  
  keys[key] = true;

}

void keyReleased()
{
  keys[key] = false;
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

void stop(){
  myPort.write('p');
}
void reverse(){
  myPort.write('s');
}
