#include "IRremote.h"

const int receiver = 2; 
const int led = 13;

IRrecv ir_receiver(receiver);           
decode_results results;          

void setup()   
{
  Serial.begin(9600);
  ir_receiver.enableIRIn(); 
  pinMode(led, OUTPUT);  
}


void loop() 
{
  if (ir_receiver.decode(&results))

  {
    Serial.println(results.value, HEX);
    translateIR(); 
    ir_receiver.resume(); 
    delay(200); 
  } 
  
}

void translateIR() 

{
  int sensorValue=0;
  sensorValue = digitalRead(led);
  
  switch(results.value){

  case 0x900BCB5:
    if (sensorValue==0){
      
      Serial.println(" ON"); 
      digitalWrite(led, HIGH); 
      break;
    }
    if (sensorValue==1){
      
      Serial.println(" OFF"); 
      digitalWrite(led, LOW); 
      break;
    }
    
    case 0x900030A:
      Serial.println(" BLINK");
      for(int i=1;i<5;i++){
        digitalWrite(led, HIGH);
        delay(500);
        digitalWrite(led, LOW);
        delay(500);
      }
      if (sensorValue==1){
        digitalWrite(led, HIGH);
      }
      break;
  default: 
    Serial.println(" other button");
  }
}