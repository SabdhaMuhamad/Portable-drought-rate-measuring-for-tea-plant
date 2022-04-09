
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
char array1[] = "  TELKOM UNIVERSITY";  // CHANGE THIS AS PER YOUR NEED 
char array2[] = "  ft. PPTK GAMBOENG";     // CHANGE THIS AS PER YOUR NEED 
char array3[] = "     ----------";   // CHANGE THIS AS PER YOUR NEED
char array4[] = "       by A11";     // CHANGE THIS AS PER YOUR NEED

LiquidCrystal_I2C lcd(0x27, 20, 4); // CHANGE THE 0X27 ADDRESS TO YOUR SCREEN ADDRESS IF NEEDED
void setup()
{
  lcd.init();
  lcd.backlight();
  
  lcd.print(array1);
  
  lcd.setCursor(0,1);
  lcd.print(array2);
  
  lcd.setCursor(0,2);
  lcd.print(array3);
  
  lcd.setCursor(0,3);
  lcd.print(array4);
}
void loop()
{}
