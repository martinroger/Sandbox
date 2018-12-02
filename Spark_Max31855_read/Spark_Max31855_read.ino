#include <SparkFunMAX31855k.h>



#include <SPI.h>


#define MAXDO 50 //corresponds to MISO output on header, connects to DO
#define MAXCLK 52 //clock on ICSP header to CLK
#define SS 6 //Slave select from D6 to CS

//create thermocouple object
SparkFunMAX31855k thermocouple(6,2,3);
//Adafruit_MAX31855 thermocouple(MAXCLK,SS,MAXDO);
//MAX6675 thermocouple(MAXCLK,SS,MAXDO);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  delay(1000);

}

void loop() {
//  Serial.print("Measured: ");
//  Serial.println(thermocouple.readInternal());
//  Serial.print("C=");
   Serial.println(thermocouple.readTempC());
  //Serial.println(thermocouple.readError());

  delay(1000);
  // put your main code here, to run repeatedly:

}
