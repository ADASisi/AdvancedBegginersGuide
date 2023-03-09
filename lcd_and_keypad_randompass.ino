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

byte rowPins[ROWS] = {6,7,8,9}; 
byte colPins[COLS] = {10,11,12,13}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

String combination;

int flag=0;
int pass;

void setup() {
  randomSeed(analogRead(0));
  pass=random(1000,10000);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Input pass|");
  lcd.print(pass,HEX);
  lcd.print("|");
  lcd.setCursor(0, 1);
  lcd.print(">");

}

void loop() {
  // put your main code here, to run repeatedly:
  char Key = customKeypad.getKey();


   if(Key=='*' && flag==0){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Input pass|");
      lcd.print(pass,HEX);
      lcd.print("|");
      lcd.setCursor(0, 1);
      lcd.print(">");
      combination='\0';
     //delet
   }else if(flag==1 && Key=='A'){

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Input pass|");
      lcd.print(pass,HEX);
      lcd.print("|");
      lcd.setCursor(0, 1);
      lcd.print(">");
      combination='\0';   
      flag=0;
     //full reset
    }else if(Key=='#'){
     int combo=combination.toInt();
     Serial.println(combo);

      if(combo==pass){

      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Correct!"); 
      flag=1;

      }else{

      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Incorrect!");
      delay(1250);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Input pass|");
      lcd.print(pass,HEX);
      lcd.print("|");
      lcd.setCursor(0, 1);
      lcd.print(">");
      combination='\0';
      
     }

    }else if (Key){

    lcd.print(Key);
    combination+=Key;

   }
}