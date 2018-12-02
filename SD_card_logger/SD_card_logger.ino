#include <SPI.h>
#include <SD.h>

// The CATALEX Sd card unit is connected on harware SPI with CS on pin 53 of the arduino.
#define SD_CS 53

boolean recording_active = false;
String filename = "Log_";
File LOG;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card issue");
    while (1);
  }
  Serial.println("Card OK");
  int i = 0;
  Serial.println("Provide prefix:");
  while (Serial.available() == 0) {
    Serial.print('.');
    delay(1000);
    if (millis() > 30000) {
      Serial.println("Default name chosen");
      break;
    }
  }
  if (Serial.available() > 0) {
    filename = Serial.readStringUntil('\n');
  }
  while (SD.exists(filename + i + ".log")) {
    i = i + 1;
    if (i > 5000) {
      Serial.println("Excessive logs");
      while (1);
    }
  }
  filename = filename + i + ".log";
  Serial.print("Filename created:");
  Serial.println(filename);

  // put your setup code here, to run once:

}

void loop() {

  if (recording_active) {
    LOG = SD.open(filename, FILE_WRITE);
    if (LOG) {
      LOG.println(millis());
      LOG.close();
    }
    else {
      Serial.println("Issue opening file");
      recording_active = false;
    }
    delay(500);
    // put your main code here, to run repeatedly:
  }
}

void serialEvent() {
  while (Serial.available()) {
    String temp = Serial.readStringUntil('\n');
    if (temp.equals("START")) {
      recording_active = true;
      Serial.println("Recording set to active");
    }
    if (temp.equals("STOP")) {
      recording_active = false;
      Serial.println("Recording set to inactive");
    }


  }

}
