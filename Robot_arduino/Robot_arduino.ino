#include <Servo.h>
#include <NewPing.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

#define TRIGGER_PIN  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A1 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

const int In1 =9;
const int  In2= 8;
const int  In3= 7;
const int  In4= 6;
const int pwm1=10;
const int pwm2=5;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  myservo.attach(0);  // attaches the servo on pin 9 to the servo object
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
}

void forward()
{
  analogWrite(pwm1,100);
  analogWrite(pwm2,100);
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);
  digitalWrite(In3,HIGH);
  digitalWrite(In4,LOW);
  
 }

void backward()
 {
  analogWrite(pwm1,100);
  analogWrite(pwm2,100);
  
  digitalWrite(In1,LOW);
  digitalWrite(In2,HIGH);
  digitalWrite(In3,LOW);
  digitalWrite(In4,HIGH);
 }

 void right()
 {   analogWrite(pwm1,100);
  analogWrite(pwm2,100);
  
   digitalWrite(In1,LOW);
  digitalWrite(In2,LOW);
  digitalWrite(In3,HIGH);
  digitalWrite(In4,LOW);
 } 

 void left()
 { analogWrite(pwm1,100);
  analogWrite(pwm2,100);
  
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);
  digitalWrite(In3,LOW);
  digitalWrite(In4,LOW);
  
 }

 void brake()
 {analogWrite(pwm1,0);
  analogWrite(pwm2,0);
  
  digitalWrite(In1,LOW);
  digitalWrite(In2,LOW);
  digitalWrite(In3,LOW);
  digitalWrite(In4,LOW);
  
 }
void loop() {

  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  forward();
  myservo.write(90);
  if(sonar.ping_cm() < 15)
  {
  
    myservo.write(180);              // tell servo to go to position in variable 'pos'
     delay(50);    
     myservo.write(90);       
     delay(50);    
     myservo.write(0);  // tell servo to go to position in variable 'pos'
     delay(50);  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
    delay(500);                       // waits 15ms for the servo to reach the position
     backward();
  delay(500);
  left();
  }
 
  }
 







 
