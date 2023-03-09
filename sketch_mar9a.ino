

// Import the Liquid Crystal library
#include <LiquidCrystal.h>;
//Initialise the LCD with the arduino. LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(5,4,3,2,1,0);
#include <Keypad.h>;

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

String pad;
byte rowPins[ROWS] = {6,7,8,9}; 
byte colPins[COLS] = {10,11,12,13}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  // Switch on the LCD screen
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Input pass: ");
  lcd.setCursor(0, 1);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char Key = customKeypad.getKey();
  
  if (Key){
    Serial.print(Key);
  }
}