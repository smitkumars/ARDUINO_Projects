#include <MFRC522.h>
#include <SPI.h>

#include <Servo.h>

// twelve servo objects can be created on most boards


#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
Servo myservo;  // create servo object to control a servo

MFRC522::MIFARE_Key key; 

int code[] = {151,76,20,98}; //This is the stored UID
int code1[]= {06,236,203,27};
int codeRead = 0;
 int buzzer=8;
 int red=3;
 int green=4;
 int red1=5;
 int green1=7;
int flag=0;
String uidString;
unsigned char i, j ;
void setup() {
  
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  pinMode(buzzer,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(red1,OUTPUT);
  pinMode(green1,OUTPUT);
  myservo.attach(6);
  myservo.write(160);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  
 Serial.println("PODAR INTERNATIONAL SCHOOL, NANDED");
  
  
}

void loop() {

  digitalWrite(buzzer,HIGH);
  if(  rfid.PICC_IsNewCardPresent())
  {
      readRFID();
  }
  delay(100);

}

void readRFID()
{
  
  rfid.PICC_ReadCardSerial();
  Serial.print(F("\nPICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

    
   
    Serial.println("Scanned PICC's UID:");
    printDec(rfid.uid.uidByte, rfid.uid.size);

    uidString = String(rfid.uid.uidByte[0])+" "+String(rfid.uid.uidByte[1])+" "+String(rfid.uid.uidByte[2])+ " "+String(rfid.uid.uidByte[3]);
    
  //  printUID();

    int i = 0;
    boolean match = true;
    boolean match1 = true;
    while(i<rfid.uid.size)
    {
      if(!(rfid.uid.uidByte[i] == code[i]))
      {
           match = false;
          
           
      }
       if(!(rfid.uid.uidByte[i] == code1[i]))
      {
           match1 = false;
          
           
      }
      i++;


      
    }

    if(match)
    {
      Serial.println("\nACCESS GRANTED!");
      Serial.println("Student Name: Shashank Sandipkumar Lath");
      Serial.println("GRADE VIII");
      flag=1;
      digitalWrite(green,HIGH);
       digitalWrite(green1,HIGH);
    digitalWrite(buzzer,LOW);
    delay(500);
    digitalWrite(buzzer,HIGH);
      delay(1000);
      digitalWrite(green,LOW);
       digitalWrite(green1,LOW);
    }
    
    else if(match1)
    {
      
       Serial.println("\nACCESS GRANTED!");
      Serial.println("Faculty Name: Govindsai Makwana");
      Serial.println("Employee code:15421");
      flag=1;
      digitalWrite(green,HIGH);
       digitalWrite(green1,HIGH);
    digitalWrite(buzzer,LOW);
    delay(500);
    digitalWrite(buzzer,HIGH);
      delay(1000);
      digitalWrite(green,LOW);
       digitalWrite(green1,LOW);
      
      
      }
    
    
    else
    {
      flag=2;
      Serial.println("\nACCESS DENIED");
      digitalWrite(red,HIGH);
       digitalWrite(red1,HIGH);
      digitalWrite(buzzer,LOW);
      myservo.write(90);
    delay(5000);
    digitalWrite(buzzer,HIGH);
    digitalWrite(red,LOW);
    digitalWrite(red1,LOW);
    myservo.write(160);
      
    }



   
    // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}

 

  void printUID()
  {
    Serial.println("UID no");
    Serial.println(uidString);
    
  }

 




 
