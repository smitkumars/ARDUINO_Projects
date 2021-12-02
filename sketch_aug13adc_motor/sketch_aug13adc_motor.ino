void setup() {
  // put your setup code here, to run once:
digitalWrite(10,OUTPUT);
digitalWrite(9,OUTPUT);
digitalWrite(8,OUTPUT);
digitalWrite(7,OUTPUT);
digitalWrite(6,OUTPUT);
digitalWrite(5,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(10,100);
digitalWrite(9,HIGH);
digitalWrite(8,LOW);
analogWrite(5,100);
digitalWrite(7,HIGH);
digitalWrite(6,LOW);

delay(1000);


}
