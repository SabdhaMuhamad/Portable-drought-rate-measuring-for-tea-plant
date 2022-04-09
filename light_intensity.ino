#include <Wire.h>                      
int ldrPin = A3;     
float ldrstatus;
void setup()
{
  pinMode(ldrPin, INPUT);
//  lcd.init();                    
//  lcd.backlight(); 
  Serial.begin(9600);  
  
           
}

void loop()
{
  float ldrStatus = analogRead(ldrPin);
  Serial.print("Light : ");
  Serial.println(ldrStatus + String(" lx"));
  delay(1000);

//if (ldrStatus <= 200) {
//Serial.print("Its DARK, Turn on the LED : ");
//Serial.println(ldrStatus);
//} else {
//Serial.print("Its BRIGHT, Turn off the LED : ");
//Serial.println(ldrStatus);
}
//  lcd.setCursor(0,0);           
//  lcd.print("Int= " + String(ldrStatus));
