void updateLCD() {
  
  lcd.setCursor(0,0);
  lcd.print("Button pressed");
  lcd.setCursor(0,1);
  lcd.print("A0 value:");
  lcd.print(map(analogRead(A0),0,1023,0,12));
}

