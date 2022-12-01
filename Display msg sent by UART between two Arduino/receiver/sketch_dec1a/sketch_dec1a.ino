/*
  *receiver code
*/
#include <LiquidCrystal.h>
const short int rs = 12 , en = 11 , D4 = 5 , D5 = 4 , D6 = 3 , D7 = 2;
LiquidCrystal lcd(rs,en,D4,D5,D6,D7);
#define ready 'r'
String str;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2); 
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(ready); //I am ready to receive messages
  while(Serial.available() < 1)
    ;
  
  lcd.print(Serial.readString());
  delay(100);
}
