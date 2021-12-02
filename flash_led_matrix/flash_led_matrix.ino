//initialize the port numbers. You can easily change them here if you connected your LEDs in another way than I suggested
int led0 = 0;
int led1 = 1;
int led2 = 2;
int led6 = 6;
int led7 = 7;
int led8 = 8;
int led9 = 9;
int led10 = 10;

//the time we will wait after lighting one LED (in ms)
int time = 300;

void setup(){ //this method will be run once after powering up the arduino
  //put all the pins in output mode so they can light up the LEDs
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);
  
  //ensure all the LEDs are off
}


void loop(){ //this method will be repeated once the setup is finished
  digitalWrite(led2,HIGH);//we basicly keep calling this method
  
  digitalWrite(led9,LOW); 


}
