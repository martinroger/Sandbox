#include <max6675.h>
#include <SPI.h> //Don't forget that guy
#include <LiquidCrystal.h>

#define MAX_GND 43
#define MAX_VCC 41
#define MAX_SCK 39
#define MAX_CS 37
#define MAX_DO 35

#define LCD_RS 8
#define LCD_ENABLE 9
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
MAX6675 TC(MAX_SCK, MAX_CS, MAX_DO);

double max_T = 0.00;
int interval = 250;
double delta[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
unsigned long last_read = 0;
double T = 0;
double previous_T = 0;
int i = 0;
double avg_delta;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(MAX_VCC, OUTPUT);
  pinMode(MAX_GND, OUTPUT);
  digitalWrite(MAX_VCC, HIGH);
  digitalWrite(MAX_GND, LOW);
  lcd.setCursor(0, 0);
  lcd.print("T/MAX ");
  lcd.setCursor(0, 1);
  lcd.print("Delta:");
  delay(1000);
  //Doesn't look like the thermocouple has a .begin()
}

void loop() {
  // put your main code here, to run repeatedly:

  last_read = millis();
  T = TC.readCelsius();
  Serial.println(T);
  lcd.setCursor(6, 0);
  lcd.print((int)T);
  lcd.print('/');
  max_T = max(T, max_T);
  lcd.print((int)max_T);
  for(i=0;i<=4;i++) {
    delta[i] = delta[i+1];
  }
  delta[5]=(T-previous_T)/(interval/1000.0);
  lcd.setCursor(6,1);
  avg_delta = 0.0;
  for(i=0;i<=5;i++) {
    //
avg_delta = avg_delta+(delta[i]);
  }
  //avg_delta = sqrt(avg_delta/6);
  avg_delta = (avg_delta/6);
  lcd.print(avg_delta);
  previous_T = T;
  

  while ((millis() - last_read) < interval) {
    ;
  }
  
}
