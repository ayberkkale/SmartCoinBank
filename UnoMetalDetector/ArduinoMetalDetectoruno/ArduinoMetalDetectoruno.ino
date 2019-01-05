
/*
 * 
 Ref:https://www.allaboutcircuits.com/projects/metal-detector-with-arduino/
 
 */

// Number of cycles from external counter needed to generate a signal event
#define CYCLES_PER_SIGNAL 5000


// Frequency delta threshold for metal detector to trigger
#define SPINNER_THRESHOLD 700 //700

// Pin definitions
#define SENSITIVITY_POT_APIN 1



unsigned long lastSignalTime = 0;
unsigned long signalTimeDelta = 0;

boolean firstSignal = true;
unsigned long storedTimeDelta = 0;

int indicator=0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This signal is called whenever OCR1A reaches 0
// (Note: OCR1A is decremented on every external clock cycle)
SIGNAL(TIMER1_COMPA_vect)
{
  unsigned long currentTime = micros();
  signalTimeDelta =  currentTime - lastSignalTime; //difference between rising edges
  lastSignalTime = currentTime;

  if (firstSignal)
  {
    firstSignal = false;
  }
  else if (storedTimeDelta == 0)
  {
    storedTimeDelta = signalTimeDelta;
  }

  // Reset OCR1A
  OCR1A += CYCLES_PER_SIGNAL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{

  Serial.begin(57600);
  // Set WGM(Waveform Generation Mode) to 0 (Normal)
  TCCR1A = 0b00000000;
  
  // Set CSS(Clock Speed Selection) to 0b111 (External clock source on T0 pin
  // (ie, pin 5 on UNO). Clock on rising edge.)
  TCCR1B = 0b00000111;

  // Enable timer compare interrupt A (ie, SIGNAL(TIMER1_COMPA_VECT))
  TIMSK1 |= (1 << OCIE1A);

  // Set OCR1A (timer A counter) to 1 to trigger interrupt on next cycle
  OCR1A = 1;

  pinMode(13, OUTPUT);          // sets the digital pin 13 as output


}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
 


float sensitivity = 7.28; //MULTIPLIER
    int storedTimeDeltaDifference = (storedTimeDelta - signalTimeDelta) * sensitivity; //TIME DIFFERENCE


    if (storedTimeDeltaDifference > SPINNER_THRESHOLD)// control metal level
    {


    indicator=1;
    
      
      
    }
    else
    {
   


    }
 if(indicator==1){ // send message to Arduino Mega

  Serial.println("Metal Detected");
 // delay(50);

  digitalWrite(13, HIGH);       // sets the digital pin 13 on
  indicator=0;
 delay(5000);
  digitalWrite(13, LOW);        // sets the digital pin 13 off
  
 }

  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float mapFloat(int input, int inMin, int inMax, float outMin, float outMax)
{
  float scale = (float)(input - inMin) / (inMax - inMin);
  return ((outMax - outMin) * scale) + outMin;
}

