#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define data_moist A2

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int AirValue = 567;                  // Nilai batas tanah kering
const int WaterValue = 306;                 // Nilai batas tanah basah
int soilMoistureValue;                      // Deklarasi variabel kelembaban
int soilMoisturePercent;                    // Deklarasi variabel persen kelembaban


void setup()
{
Serial.begin(9600);// open serial port, set the baud rate as 9600 bps
lcd.init();
lcd.backlight();
}
void loop() {
  soilMoistureValue = analogRead(data_moist);
  Serial.println("Nilai ADC = " + String(soilMoistureValue));
  soilMoisturePercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  Serial.println(soilMoisturePercent + String("%"));
  if(soilMoisturePercent <0){
      soilMoisturePercent=0;
    }
    else if(soilMoisturePercent>100){
      soilMoisturePercent=100;
    }
//  lcd.setCursor(0,0);
//  lcd.print("SMc  : ");
//  lcd.print(soilMoisturePercent);
//  lcd.print("%");
//  int val;
//  val = analogRead(data_moist);
//  Serial.println(val);
  delay(1000);
}
