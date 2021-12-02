#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2 ,3 , 9, 10, 11, 12); //(Rs,En,D4,D5,D6,D7)
//LiquidCrystal lcd(2, 3, 4, 10, 11, 12);

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
int frequency = 0;
int Red=0;
int Green=0;
int Blue=0;
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
   pinMode(A2,OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}
void loop() {
  // Setting red filtered photodiodes to be read
digitalWrite(A0,HIGH);
  digitalWrite(A1,LOW);
   digitalWrite(A2,HIGH);
   
  lcd.setCursor(2,0);
     lcd.noDisplay();
  
 lcd.print("*PIS NANDED*");
 lcd.setCursor(2,1);
 lcd.print("WELCOMES YOU");

  
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Red= frequency;
  if(Red<=100)
   {
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print("Red Colour");
    delay(1000);
    
    }
  Serial.print("R= ");//printing name
  Serial.print(Red);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  Green=frequency;
   if(Green<=100)
   {
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print("Green Colour");
    delay(1000);
    
    }
 
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(Green);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  Blue=frequency;
   if(Blue<=100)
   {
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print("Blue Colour");
    delay(1000);
    
    }
 
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(Blue);//printing RED color frequency
  Serial.println("  ");
  delay(100);

  lcd.display();
  delay(700);
}
