

import processing.serial.*;
import g4p_controls.*;

Serial myPort;
boolean port_available = false;
int selectedPortIndex = 2;
String inString;
int lf = 10;
int[] coords = {640,320};
int[] last_coords = {640,320};


void setup() {
  size(1280, 720);
  createGUI();
  Serial_list.setItems(Serial.list(), selectedPortIndex);
  stop_button.setEnabled(false);
  line(10,15,20,20);
}

void draw() {
  if(last_coords!=coords) {
    line(last_coords[0],last_coords[1],coords[0],coords[1]);
    stroke(255);
    last_coords = coords;
  }
  //background(0);
  //while(myPort !=null) {
  //  while(myPort.available()>0) {
  //    inString = myPort.readStringUntil(lf);
  //    println(inString);
  //    coords = int(split(inString,' '));
  //    print(coords[0]);
  //    print('x');
  //    print(coords[1]);
  //    print('=');
  //    println(coords[0]*coords[1]);
  //  }
  //}
    //while(port_available) {
  //  println(inString);

  //}
}

void serialEvent(Serial p) {
  inString = p.readStringUntil(lf);// reads until carriage return
  if(inString!=null) {
    //print(inString);
    coords = int(split(trim(inString),' '));//cleans beginning and end whitespace characters
    print(coords[0]);
    print('-');
    println(coords[1]);
    //line(100+millis()/1000,100,200,200);
    //stroke(255);
    //redraw();
    //line(last_coords[0]/2.0,last_coords[1]/2.0,coords[0]/2.0,coords[1]/2.0);
    //stroke(255);
    //last_coords = coords;
  }
}
