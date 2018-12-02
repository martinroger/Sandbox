

void setup() {
  pinMode(18,OUTPUT);
  pinMode(19,OUTPUT);
  digitalWrite(19,HIGH);
  digitalWrite(18,LOW);
  Serial.begin(9600);
  Serial2.begin(9600);
  
  
  // put your setup code here, to run once:

}

void loop() {
  Serial.println(millis());
  //delay(500);
  Serial2.println(millis());
  delay(500);// put your main code here, to run repeatedly:

}
