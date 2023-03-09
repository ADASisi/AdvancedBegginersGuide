#include "Arduino.h"
#include "Servo.h"


// Pin Definitions
#define SERVO360MICRO_PIN_SIG	2

Servo servo360Micro;

const int timeout = 10000;       
char menuOption = 0;
long time0;

void setup() 
{

    Serial.begin(9600);
    while (!Serial) ; 
    Serial.println("start");
        
}

void loop() 
{

     
    servo360Micro.attach(SERVO360MICRO_PIN_SIG);         
    servo360Micro.write(180);  
    delay(2000);                              
    servo360Micro.write(0);    
    delay(2000);                             
    servo360Micro.write(90);    
    delay(2000);                              
    servo360Micro.detach();                    
    
    
}