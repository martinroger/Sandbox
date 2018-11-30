
#include <LiquidCrystal.h>

//I am unsure which button pin is which but they seem to span from A0 to A5. This sketch gets the LCD to display 
//which button is being pressed.

LiquidCrystal lcd(8,9,4,5,6,7);
int prevValue = 0;
int currentValue = 0;

void setup() {
  Serial.begin(115200);
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
  if(anyButton()) {
    updateLCD();
    //rolling value
    prevValue = currentValue;
    currentValue = analogRead(A0);
    //double plot
    Serial.print(map(currentValue,0,1023,0,12));
    Serial.print(" ");
    Serial.println(map(prevValue,0,1023,0,12)); 
  }
  else {
    lcd.clear();
  }
}

