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
ListBox listBox;

void setup() {

  size(700, 600);

  cp5 = new ControlP5(this);

  printArray(Serial.list());

  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');

  listBox = cp5.addListBox("Robot Log").setPosition(300, 300).setSize(300, 800)
    .setColorBackground(color(30, 144, 255))
    .setColorLabel(color(0, 0, 0));

  cp5.addButton("forward").setPosition(120, 10).setSize(50, 50)
    .setColorBackground(color(30, 144, 255))
    .setColorLabel(color(0, 0, 0));

  cp5.addButton("left").setPosition(30, 100).setSize(50, 50)
    .setColorBackground(color(0, 255, 0))
    .setColorLabel(color(0, 0, 0));

  cp5.addButton("right").setPosition(210, 100).setSize(50, 50)
    .setColorBackground(color(255, 255, 0))
    .setColorLabel(color(0, 0, 0));

  cp5.addButton("reverse").setPosition(120, 200).setSize(50, 50)
    .setColorBackground(color(255, 0, 0))
    .setColorLabel(color(0, 0, 0));

  cp5.addButton("stop").setPosition(400, 100).setSize(150, 50)
    .setColorBackground(color(255, 0, 0))
    .setColorLabel(color(0, 0, 0));

  cp5.addButton("L90").setPosition(300, 200).setSize(150, 50)
    .setColorBackground(color(255, 0, 0))
    .setColorLabel(color(0, 0, 0));

  cp5.addButton("R90").setPosition(500, 200).setSize(150, 50)
    .setColorBackground(color(255, 0, 0))
    .setColorLabel(color(0, 0, 0));  
    
    cp5.addButton("clear").setPosition(400, 500).setSize(150, 50)
    .setColorBackground(color(255, 0, 0))
    .setColorLabel(color(0, 0, 0));
    
}

void draw() {
  background(0, 0, 0);  
  move();


  if ( myPort.available() > 0) {  // If data is available,
    
    listBox.addItem(myPort.readString(), 1);
    myPort.clear();
   
 
  }

  // Set background to white
  if (val == 0) {              // If the serial value is 0,
    fill(0);                   // set fill to black
  } else {                       // If the serial value is not 0,
    fill(204);                 // set fill to light gray
  }
  rect(50, 50, 100, 100);
}


void move()
{
  if (keys['c']) 
  {
    myPort.write('c');
  }
  
    if (keys['f']) 
  {
    myPort.write('f');
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

void forward() {
  myPort.write('w');
}

void left() {
  myPort.write('a');
}

void right() {
  myPort.write('d');
}

void clear() {
  listBox.getItems().clear();
}

void stop() {
  myPort.write('p');
}
void reverse() {
  myPort.write('s');
}
void L90() {
  myPort.write('l');
}
void R90() {
  myPort.write('r');
}
