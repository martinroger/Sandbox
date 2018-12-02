#include "MAX31855.h"

//#include <max6675.h>

//#include <Adafruit_MAX31855.h>


#include <SPI.h>


#define MAXDO 6 //corresponds to MISO output on header, connects to DO
#define MAXCLK 7 //clock on ICSP header to CLK
#define SS 5 //Slave select from D6 to CS

//create thermocouple object

MAX31855 thermocouple(MAXCLK,SS,MAXDO);
//MAX6675 thermocouple(MAXCLK,SS,MAXDO);
int error =0;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  delay(1000);
  thermocouple.begin();

}

void loop() {
//  Serial.print("Measured: ");
//  Serial.println(thermocouple.readInternal());
//  Serial.print("C=");
error = thermocouple.read();
if(error ==0) {
  Serial.println(thermocouple.getTemperature());
}
   else {
    Serial.print("Error code:");
    Serial.println(error);
   }
   //Serial.println((float)thermocouple.readCelsius());
  //Serial.println(thermocouple.readError());

  delay(1000);
  // put your main code here, to run repeatedly:

}
