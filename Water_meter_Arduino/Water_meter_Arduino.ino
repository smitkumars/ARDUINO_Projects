//  Njarpa
// Arduino Water Doser ml and L
//Water flow sensor YF-S201

#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Pines arduino to lcd

     //-------Pins-----//
int Relay = 13;                 //Solenoid valve open/close
int start_stop = 8;             //Start/Stop button
int rst_sp = 9;                 // Reset Set Point Button
int rst_cnt = 10;               // Reset counter button
int unit = 11;                  // Change Unit Button
const int sensor_pulse =12;     // Sensor Pulse In
//----Analog as Input-----//
int add_one =16;                // +1 Button
int add_ten = 17;               // +10 Button
int add_cien = 18;              // +100 Button
int add_mil = 19;               // +1000 Buton

    //-----Variables for debouncing-----//
boolean currentstart_stop = LOW;         
boolean laststart_stop =LOW;             
boolean lastsensor_pulse = LOW;
boolean currentsensor_pulse = LOW;
boolean lastunit = LOW;
boolean currentunit = LOW;
boolean lastrst_sp = LOW;
boolean currentrst_sp = LOW;
boolean lastrst_cnt = LOW;
boolean currentrst_cnt = LOW;
boolean lastadd_one = LOW;
boolean currentadd_one = LOW;
boolean lastadd_ten = LOW;
boolean currentadd_ten = LOW;
boolean lastadd_cien = LOW;
boolean currentadd_cien = LOW;
boolean lastadd_mil = LOW;
boolean currentadd_mil = LOW;

//-----Storage state for toggle function---//
boolean unitState = LOW;                  //storage for the current state of the unit
boolean RelayState = LOW;                //storage for the current state of the Relay (off/on)

//-------You have to put your pulses x liters here-----//
float cal_1=2.5;                        //Calibrate ml x pulse (cal_1 = 1000/400)
int cal_2= 400;                         //Calibrate pulses x liters
//-----------------------------------------------------//

float counter_1 = 0.0; 
int counter_2= 0; 
int TotalCount_1= 0;
int TotalCount_2= 0;
int set_point_1= 0; 
int set_point_2= 0; 

void setup(){
   lcd.begin(16, 2);
  pinMode(Relay, OUTPUT);     //Pin 13
  pinMode(add_one, INPUT);    //A2 as Input
  pinMode(add_ten, INPUT);    //A3 as Input
  pinMode(add_cien, INPUT);   //A4 as Input
  pinMode(add_mil, INPUT);    //A5 as Input

   lcd.setCursor(0,0);  //Show "SP" on the LCD
   lcd.print("SP"); 
   lcd.setCursor(0,1);  //Show "CNT" on the LCD
   lcd.print("CNT"); 
  
}
   //----Debouncing function for all buttons----//
boolean debounce(boolean last, int pin)
{
boolean current = digitalRead(pin);
if (last != current)
{
delay(5);
current = digitalRead(pin);
}
return current;
}

void loop(){
          //-----Debounce Buttons-----//
  currentstart_stop = debounce(laststart_stop, start_stop);    //Debounce for Start/Stop Button
  currentsensor_pulse = debounce(lastsensor_pulse, sensor_pulse); //Debounce for Sensor
  currentunit = debounce(lastunit, unit);             //Debounce for unit Button
  currentrst_sp = debounce(lastrst_sp, rst_sp);       //Debounce for reset set point Button
  currentrst_cnt = debounce(lastrst_cnt, rst_cnt);    //Debounce for reset counter Button
  currentadd_one = debounce(lastadd_one, add_one);    //Debounce for +1 Button
  currentadd_ten = debounce(lastadd_ten, add_ten);    //Debounce for +10 Button
  currentadd_cien = debounce(lastadd_cien, add_cien); //Debounce for +100 Button
  currentadd_mil = debounce(lastadd_mil, add_mil);    //Debounce for +1000 Button


  //-----Start/Stop toggle function----//
  if (currentstart_stop == HIGH && laststart_stop == LOW){
    
    if (RelayState == HIGH){         //Toggle the state of the Relay
      digitalWrite(Relay, LOW);
      RelayState = LOW;
    } 
    else{
      digitalWrite(Relay, HIGH);
      RelayState = HIGH;
    }
  }
  
  laststart_stop = currentstart_stop;

  //-------Unit toggle function----//
 if(RelayState == LOW){            //You only can change unit while system is not running!  
 
  //------ Lt/ml unit toggle function----//
  if (currentunit == HIGH && lastunit == LOW){
    lcd.setCursor(4, 1);        //Clear lcd(CNT area) between unit change,keeping last count
    lcd.print("          ");
    lcd.setCursor(3,0);        //Clear lcd (SP area) between unit change, keeping last SP
    lcd.print("           ");
    
    if (unitState == HIGH){         //Toggle the state of the unit (L/ml)
      digitalWrite(unit, LOW);
      unitState = HIGH;
       }
    else{
      digitalWrite(unit, HIGH);
      unitState = HIGH;  
    }
  }
  lastunit = currentunit;
 }
     //------Print unit state-----//
 if(unitState==HIGH){        //Unit state HIGH = L       
    lcd.setCursor(14,0);
    lcd.print("Lt");
    lcd.setCursor(14, 1);
    lcd.print("Lt");
    
 }
 //End Print unit state
 
 //--------------------------// 
//------------Ml Counter-----//
//---------------------------//


 //--------------------------// 
//------------Lt Counter-----//
//---------------------------//

if(unitState== HIGH){      //HIGH = Lt state
 
 //-----------------------//
 //-----Settings----------//
 //----------------------//

if(RelayState == LOW){     // You only can change settings while system is not running!
 
   //-----Adders Buttons (set point_2)---//
   if (currentadd_one == HIGH && lastadd_one == LOW){  // Add +1 
    set_point_2 = set_point_2 +1;
    }
  lastadd_one = currentadd_one;
  
   if (currentadd_ten == HIGH && lastadd_ten == LOW){  // Add +10
    set_point_2 = set_point_2 +10;
  }
  lastadd_ten = currentadd_ten;

     
  
  //-------Reset Buttons----//
  if (currentrst_sp == HIGH && lastrst_sp == LOW){  //Reset Set Point
    lcd.setCursor(3, 0);         // Clear SP area
    lcd.print("          ");
    set_point_2 = 0;
  }
   lastrst_sp = currentrst_sp;
  if (currentrst_cnt == HIGH && lastrst_cnt == LOW){//Reset Counter
    lcd.setCursor(4, 1);         // Clear CNT area
    lcd.print("         ");
    counter_2= 0;         
    TotalCount_2= 0;
  }
  lastrst_cnt = currentrst_cnt;
  }//-----End Settings-----// 

 //----Start Counter------//
  if(RelayState == HIGH){    // Only counts while relay is HIGH
  if (lastsensor_pulse== LOW && currentsensor_pulse == HIGH){
      counter_2 = counter_2 + 1;
  }
  }
 lastsensor_pulse = currentsensor_pulse;
 
//-------Counter function-----//
if(counter_2 == cal_2){
  TotalCount_2 = TotalCount_2 + 1;
  counter_2 = 0;                     //Counter  reset
  }

 lcd.setCursor(3, 0);           //Show set point
 lcd.print(set_point_2);
 lcd.setCursor(4, 1);           // Show counter
 lcd.print(TotalCount_2);

 //--Stop Counter.You can´t start if set point is lower or equal to counter--//
 if(set_point_2 <= TotalCount_2){ 
  RelayState = LOW;
  TotalCount_2=0;
  counter_2=0;
  digitalWrite(Relay, LOW);
 }
  
   
}//End unit state HIGH (L)



}//End Void Loop
