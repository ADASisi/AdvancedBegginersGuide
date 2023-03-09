#include "Arduino.h"
#include "Servo.h"


// Pin Definitions
#define SERVO360MICRO_PIN_SIG	2

Servo servo360Micro;

const int timeout = 10000;       
char menuOption = 0;
long time0;
int locked = 0;

void setup() 
{

    Serial.begin(9600);
    while (!Serial) ; 
    Serial.println("start");
        
}

void loop() 
{
    servo360Micro.attach(SERVO360MICRO_PIN_SIG);
    open_close();
    delay(2000);                                                           
    servo360Micro.detach();                     
    
}

void open_close()
{
  if(locked == 1)
  {
    servo360Micro.write(60); 
    locked = 0;
  }
  else
  {
    servo360Micro.write(160); 
    locked = 1;
  }
}