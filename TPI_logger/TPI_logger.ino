#include <SPI.h>
#include <SD.h>
//The card is set to 3.3V
#include <MAX31855.h>
//Uncomment to use the MAX6675 thermocouple interface. Watch out for supply voltage
//#include <max6675.h>

/*  The chip select for the Catalex SD cad interface HAS to be on there. It cannot be moved from using the default hardware SPI pins.
    The Catalex SD card interface REQUIRES the board to be set to 5V, or at least the VCC-GND to be provided by 5V.
    Hardware SPI pin layout

    MISO  | VCC
    CLK   | MOSI
    RST   | GND

*/
#define SD_CS 53

//The MAX breakout will be on a different physical SPI because of the Enable on Catalex
#define MAX_DO 33
#define MAX_CLK 35
#define MAX_CS 31

//Initialise global variable
boolean recording_active = false;
String filename = "Log_";
unsigned long last_read = 0;
unsigned long t_offset = 0;
int interval = 500;
int TC_error;

//Initialise instances
File LOG;
MAX31855 thermocouple(MAX_CLK, MAX_CS, MAX_DO);
//MAX6675 thermocouple(MAX_CLK,MAX_CS,MAX_DO);

//make sure the Bluetooth breakout is connected to Serial2 (Pins 16 and 17)
void setup() {

  //Assign #13 to be blinking when it is recording
  //pinMode(13, OUTPUT);

  //Start up the serial ports
  Serial.begin(9600);
  Serial2.begin(9600);

  //Start up the thermocouple reader
  thermocouple.begin();

  //Hang operations until some form of Serial communication is established on either stream
  while (!Serial || !Serial2) {
    //Quick time-out in case the system has to be fully autonomous
    //Note that it will give 30 more seconds before moving on with naming
    if (millis() > 30000) {
      recording_active = true;
      t_offset = millis();
      break;
    }
  }

  //Once Serial has been established some way or not, check SD card opening
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card Issue !");
    Serial2.println("SD Card Issue !");
    while (1); // This effectively hang the Arduino
  }

  //If the SD Card is fine, go to prefix selection
  Serial.println("Card OK");
  Serial2.println("Card OK");

  int i = 0;
  Serial.println("Provide prefix: ");
  Serial2.println("Provide prefix: ");
  //Wait for something to come on either serial for another 30 seconds
  while ((Serial.available() == 0) && (Serial2.available() == 0)) {
    //Print some cheeky dots
    Serial.print('.');
    Serial2.print('.');
    delay(1000);
    //if a minute has elapsed since start...
    if (millis() > 60000) {
      Serial.println('.');
      Serial2.println('.');
      Serial.println("Default name selected");
      Serial2.println("Default name selected");
      recording_active = true; //Auto-start because lack of response but all green lights
      t_offset = millis();
      break;
    }
  }
  //If the user actually inputs something on one of the two channels
  if ((Serial.available() > 0)) {
    filename = Serial.readStringUntil('\n');
  }
  if ((Serial2.available() > 0)) {
    filename = Serial2.readStringUntil('\n');
  }

  //Check if the file exists. If it does, just increment the number. Careful with the number of characters !
  while (SD.exists(filename + i + ".log")) {
    i = i + 1;
    if (i > 999) {
      Serial.println("Too many similar filenames");
      Serial2.println("Too many similar filenames");
      while (1); //Park the system
    }
  }
  //If the filename is valid, construct the full filename
  filename = filename + i + ".log";
  Serial.print("Filename selected: ");
  Serial.println(filename);
  Serial2.print("Filename selected: ");
  Serial2.println(filename);

  //Setup is complete.
}


void loop() {

  //Check that recording has been set to active
  if (recording_active) {
    //Open the SD Card if possible
    LOG = SD.open(filename, FILE_WRITE);
    if (LOG) {
      //Hold operations until the interval has elapsed
      while ((millis() - last_read) < interval) {
        ;
      }

      //Check that the MAX31855 is not setting off on an error.
      TC_error = thermocouple.read();
      last_read = millis();
      if (TC_error != 0) {
        LOG.print(last_read - t_offset);
        LOG.print(' ');
        LOG.print("TC Error: ");
        LOG.println(TC_error);
        LOG.close();
        Serial.println("TC Error: " + TC_error);
        Serial2.println("TC Error: " + TC_error);
        recording_active = false;
      }
      else {
        //If the recording is fine
        LOG.print(last_read - t_offset);
        LOG.print(' ');
        LOG.println(thermocouple.getTemperature());
        LOG.close();
        Serial.print(last_read - t_offset);
        Serial.print(' ');
        Serial.println(thermocouple.getTemperature());
        Serial2.print(last_read - t_offset);
        Serial2.print(' ');
        Serial2.println(thermocouple.getTemperature());
      }
    }
    else { //The case where the SD open failed
      Serial.println("Issue opening file");
      Serial2.println("Issue opening file");
      recording_active = false;
    }
  }
  //End of loop()
}

//Use of serialEvent and serialEvent() for basic remote control
void serialEvent() {
  while (Serial.available()) { //If there is something in the buffer
    String temp = Serial.readStringUntil('\n');
    if (temp.equals("START")) { //Start command
      recording_active = true;
      t_offset = millis();
      Serial.println("Recording set to active at:" + (String)(t_offset / 1000.0));
    }

    if (temp.equals("STOP")) { //Stop command
      recording_active = false;
      Serial.println("Recording stopped after:" + (String)(millis() - t_offset) + "ms");
    }
  }
}


void serialEvent2() {
  while (Serial2.available()) { //If there is something in the buffer
    String temp = Serial2.readStringUntil('\n');
    if (temp.equals("START")) { //Start command
      recording_active = true;
      t_offset = millis();
      Serial2.println("Recording set to active at:" + (String)(t_offset / 1000.0));
    }

    if (temp.equals("STOP")) { //Stop command
      recording_active = false;
      Serial2.println("Recording stopped after:" + (String)(millis() - t_offset) + "ms");
    }
  }
}
