#include "IRremote.h"
//#include <NewTone.h>

// defines pins numbers
const int buzzerPin = 9;

const int receiver = 8;
const int led = 13;

const int front_trigPin = 3;
const int front_echoPin = 2;

const int left_trigPin = 5;
const int left_echoPin = 4;

const int right_trigPin = 7;
const int right_echoPin = 6;

const int minDistance = 3;
const int midDistance = 12;
const int maxDistance = 15;

int isOn = 0;

IRrecv ir_receiver(receiver);           
decode_results results;

// defines variables
long front_duration;
long left_duration;
long right_duration;

int front_distance = 0;
int left_distance = 0;
int right_distance = 0;
int distance = 0;

void setup() {
  pinMode(front_trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(front_echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(left_trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(left_echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(right_trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(right_echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600); // Starts the serial communication

  ir_receiver.enableIRIn(); 
  pinMode(led, OUTPUT);  
}

void loop() {
  if (isOn == 1)
  {
    if ((distance > 0) && (distance <= minDistance))
    {
      digitalWrite(buzzerPin, HIGH);   // turn the BUZZER on (HIGH is the voltage level)
    }
    else if ((distance > minDistance) && (distance <= midDistance))
    {
      digitalWrite(buzzerPin, HIGH);   // turn the BUZZER on (HIGH is the voltage level)
      delay(30*(distance-minDistance));  
      digitalWrite(buzzerPin, LOW);    // turn the BUZZER off (LOW is the voltage level)
      delay(30*(distance-minDistance));// wait for a set time
    }
    else if ((distance > midDistance) && (distance <= maxDistance))
    {
      digitalWrite(buzzerPin, HIGH);   // turn the BUZZER on (HIGH is the voltage level)
      delay(300);  
      digitalWrite(buzzerPin, LOW);    // turn the BUZZER off (LOW is the voltage level)
      delay(300);
    }
    else if (distance > maxDistance)
    {
      digitalWrite(buzzerPin, LOW);
    }

    digitalWrite(front_trigPin, HIGH);
    delay(10);
    digitalWrite(front_trigPin, LOW);
    front_duration = pulseIn(front_echoPin, HIGH);
    front_distance = front_duration / 58;

    distance = front_distance;
    
    digitalWrite(right_trigPin, HIGH);
    delay(10);
    digitalWrite(right_trigPin, LOW);
    right_duration = pulseIn(right_echoPin, HIGH);
    right_distance = right_duration / 58;

    /*digitalWrite(left_trigPin, HIGH);
    delay(10);
    digitalWrite(left_trigPin, LOW);
    left_duration = pulseIn(left_echoPin, HIGH);
    left_distance = left_duration / 58;*/
    if(right_distance <= 8)
    {
      left_distance = 8 - right_distance; // the distance between the sensors is 18cm and the car width is 10cm
    }
    else
    {
      left_distance = right_distance;
    }

    delay(10);
    Serial.print("Left distance: ");
    Serial.print(left_distance);
    Serial.print("cm | ");
    Serial.print("Front distance: ");
    Serial.print(front_distance);
    Serial.print("cm | ");
    Serial.print("Right distance: ");
    Serial.print(right_distance);
    Serial.println("cm");
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }

  if (ir_receiver.decode(&results))
  {
    //Serial.println(results.value, HEX);
    translateIR(); 
    ir_receiver.resume(); 
    delay(200); 
  }
}

void translateIR() 

{
  switch(results.value){
  case 0xFFFFFFFF:
    if (isOn==0){
      
      Serial.println(" ON");
      digitalWrite(led, HIGH);
      isOn = 1;
      break;
    }
    else if (isOn==1){
      
      Serial.println(" OFF"); 
      digitalWrite(led, LOW);
      isOn = 0;
      break;
    }
  /*default: 
    Serial.println(" other button");*/
  }
}