
#include <LiquidCrystal.h>

//I am unsure which button pin is which but they seem to span from A0 to A5. This sketch gets the LCD to display 
//which button is being pressed.

LiquidCrystal lcd(8,9,4,5,6,7);


void setup() {
//  pinMode(A0,INPUT_PULLUP);
//  pinMode(A1,INPUT_PULLUP);
//  pinMode(A2,INPUT_PULLUP);
//  pinMode(A3,INPUT_PULLUP);
//  pinMode(A4,INPUT_PULLUP);
//  pinMode(A5,INPUT_PULLUP);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
//  lcd.print("A0:0 A1:0 A2:0");
//  lcd.setCursor(0,1);
//  lcd.print("A3:0 A4:0 A5:0");
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print(map(analogRead(A0),0,1023,0,255));
  delay(1000);
  lcd.clear();
}

//void loop() {
//  // put your main code here, to run repeatedly:
//  if(!digitalRead(A0)) {
//    lcd.setCursor(3,0);
//    lcd.print("1");
//  }
//  else {
//    lcd.setCursor(3,0);
//    lcd.print("0");
//  }
//  if(!digitalRead(A1)) {
//    lcd.setCursor(8,0);
//    lcd.print("1");
//  }
//  else {
//    lcd.setCursor(8,0);
//    lcd.print("0");
//  }
//  
//  if(!digitalRead(A2)) {
//    lcd.setCursor(13,0);
//    lcd.print("1");
//  }
//  else {
//    lcd.setCursor(13,0);
//    lcd.print("0");
//  }
//  
//  if(!digitalRead(A3)) {
//    lcd.setCursor(3,1);
//    lcd.print("1");
//  }
//  else {
//    lcd.setCursor(3,1);
//    lcd.print("0");
//  }
//
//  if(!digitalRead(A4)) {
//    lcd.setCursor(8,1);
//    lcd.print("1");
//  }
//  else {
//    lcd.setCursor(8,1);
//    lcd.print("0");
//  }
//
//  if(!digitalRead(A5)) {
//    lcd.setCursor(13,1);
//    lcd.print("1");
//  }
//  else {
//    lcd.setCursor(13,1);
//    lcd.print("0");
//  }
//}
