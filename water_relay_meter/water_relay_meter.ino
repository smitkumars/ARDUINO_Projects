#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 9);
#define relayPin 6     //5v relay module attached to Arduino digital pin 4

// Specify the pins for the two counter reset buttons and indicator LED
byte resetButtonA = 7;//reset last reading
byte resetButtonB = 8;//reset all readings
byte statusLed    = 13;//system status led

byte sensorInterrupt = 0;  // 0 = pin 2; 1 = pin 3
byte sensorPin       = 2;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;

volatile byte pulseCount;  

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitresA;
unsigned long totalMilliLitresB;

unsigned long oldTime;

void setup()
{
 lcd.begin (16, 2);//define the LCD as 20 column by 4 rows 
  //switch on the backlight
  
  lcd.setCursor(0, 0);//sets the cursor to 1 row 1 column
  lcd.print("********************");
  lcd.setCursor(0, 1);//sets cursor to 2 row 1 column
  lcd.print("  Water flow meter  ");
//  lcd.setCursor(0, 2);//sets the cursor to 3 row 1 column
//  lcd.print(" sol. valve control ");
 // lcd.setCursor(0, 3);//sets cursor to 4 row 1 column
 // lcd.print("********************");
  delay (4000); //sets delay for 4 seconds
  lcd.clear();//clears the screen
  pinMode(relayPin, OUTPUT);//sets the relayPin as OUTPUT
  digitalWrite(relayPin, HIGH);
  // Initialize a serial connection for reporting values to the host
  Serial.begin(9600);
   
  // Set up the status LED line as an output
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, HIGH);  // We have an active-low LED attached
  
  // Set up the pair of counter reset buttons and activate internal pull-up resistors
  pinMode(resetButtonA, INPUT);
  digitalWrite(resetButtonA, HIGH);
  pinMode(resetButtonB, INPUT);
  digitalWrite(resetButtonB, HIGH);
  
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitresA = 0;
  totalMilliLitresB = 0;
  oldTime           = 0;

  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

/**
 * Main program loop
 */
void loop()
{
  if(digitalRead(resetButtonA) == LOW)
  {
    totalMilliLitresA = 0;
    lcd.setCursor(14, 1);
    lcd.print("0L      ");
  }
  if(digitalRead(resetButtonB) == LOW)
  {
    totalMilliLitresB = 0;
    lcd.setCursor(7, 2);
    lcd.print("0L      ");
  }
  
  if( (digitalRead(resetButtonA) == LOW) || (digitalRead(resetButtonB) == LOW) )
  {
    digitalWrite(statusLed, LOW);
  } else {
    digitalWrite(statusLed, HIGH);
  }
  
  if((millis() - oldTime) > 1000)    // Only process counters once per second
  { 
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(sensorInterrupt);
    //lcd.setCursor(15, 0);
    //lcd.print("*");
    
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    
    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis();
    
    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60) * 1000;
    
    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitresA += flowMilliLitres;
    totalMilliLitresB += flowMilliLitres;
  
    // During testing it can be useful to output the literal pulse count value so you
    // can compare that and the calculated flow rate against the data sheets for the
    // flow sensor. Uncomment the following two lines to display the count value.
    //Serial.print(pulseCount, DEC);
    //Serial.print("  ");
    
    // Write the calculated value to the serial port. Because we want to output a
    // floating point value and print() can't handle floats we have to do some trickery
    // to output the whole number part, then a decimal point, then the fractional part.
    unsigned int frac;
    
    // Print the flow rate for this second in litres / minute
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print(".");             // Print the decimal point
    // Determine the fractional part. The 10 multiplier gives us 1 decimal place.
    frac = (flowRate - int(flowRate)) * 10;
    Serial.print(frac, DEC) ;      // Print the fractional part of the variable

    // Print the number of litres flowed in this second
    Serial.print(" ");             // Output separator
    Serial.print(flowMilliLitres);

    // Print the cumulative total of litres flowed since starting
    Serial.print(" ");             // Output separator
    Serial.print(totalMilliLitresA);
    Serial.print(" ");             // Output separator
    Serial.println(totalMilliLitresB);
    
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Flow rate:");
    if(int(flowRate) < 10)
    {
      lcd.print(" ");
    }
    lcd.print((int)flowRate);   // Print the integer part of the variable
    lcd.print('.');             // Print the decimal point
    lcd.print(frac, DEC) ;      // Print the fractional part of the variable
    lcd.print(" L/min");   
    
    lcd.setCursor(0, 1);
    lcd.print("Last reading: ");
    lcd.setCursor(14, 1);
    lcd.print(int(totalMilliLitresA / 1000));
    lcd.print("L");
    lcd.setCursor(0, 2);
    lcd.print("Total: ");
    lcd.setCursor(7, 2);
    lcd.print(int(totalMilliLitresB / 1000));
    lcd.print("L");
    lcd.setCursor(0, 3);
    lcd.print("Reset all - button B");
if (int(totalMilliLitresA / 1000) >= 10) //water limit set
  {
    digitalWrite(relayPin, LOW);
  }
  else {
    digitalWrite(relayPin, HIGH);
  }
    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;
    
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }
}

/**
 * Invoked by interrupt0 once per rotation of the hall-effect sensor. Interrupt
 * handlers should be kept as small as possible so they return quickly.
 */
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
