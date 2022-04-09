#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>
#include <DFRobot_SHT20.h>
#include <BH1750.h>
#include "RTClib.h"
#define data_moist A3        //SoilMoisture
File dataku;
LiquidCrystal_I2C lcd(0x27, 20, 4); // LCD 20x4 (0x27)
DFRobot_SHT20    sht20;
//pushButton
#define buttonhitam  4
#define buttonmerah  5
#define buttonbiru  6
#define DITEKAN LOW
#define BOUNCE 50
//SDCard
int count = 1;
int CS = 53;
//intensitasCahaya
BH1750 lightMeter;
//Sensor Soil Moisture
int AirValue = 547;                   // Nilai batas tanah kering
int WaterValue = 267;                 // Nilai batas tanah basah
int soilMoistureValue;                      // Deklarasi variabel kelembaban
int soilMoisturePercent;                    // Deklarasi variabel persen kelembaban
//SensorSHT
float temp;
float humd;
//RTC
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  sht20.initSHT20();                                  // Init SHT20 Sensor
  sht20.checkSHT20(); 
  //IntensitasCahaya
  lightMeter.begin();
  //PushButton
  pinMode(buttonhitam, INPUT_PULLUP);
  pinMode(buttonmerah, INPUT_PULLUP);
  pinMode(buttonbiru, INPUT_PULLUP);

  Serial.println("Datalogger Sensor");
  Serial.print("Membaca SDcard...");
  if (!SD.begin(CS))
  {
    Serial.println("GAGAL/SDcard rusak!");
    while (1);
  }
  Serial.println("Berhasil");

  if(!rtc.begin()){
    Serial.println("Couldn't Find RTC");
    Serial.flush();
    abort();
  }
  if(rtc.lostPower()){
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  while (!Serial)
  delay(500);
}
void loop(){ 
  MenuSetting();
}

void MenuSetting(){
  //pushButton
  delay(100);
  if(digitalRead(buttonhitam) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonhitam) == DITEKAN){}
    lcd.clear();
    setMENU1();
  }
  else{
  lcd.setCursor(0,0);
  lcd.print(" WELCOME TO PROJECT ");
  lcd.setCursor(0,1);
  lcd.print(" TELKOM UNIVERSITY ");
   lcd.setCursor(0,2);
  lcd.print("         &          ");
   lcd.setCursor(0,3);
  lcd.print("  P.P.T.K GAMBOENG  ");
  MenuSetting();
  }
}

void setMENU1(){
  if(digitalRead(buttonhitam) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonhitam) == DITEKAN){}
    lcd.clear();
    setSUBMENU1();
  }else if(digitalRead(buttonmerah) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonmerah) == DITEKAN){}
    lcd.clear();
    menuEXIT();
  }else if(digitalRead(buttonbiru) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonbiru) == DITEKAN){}
    lcd.clear();
    setMENU2();
  }
  else{
  lcd.setCursor(0,0);
  lcd.print("->SEMUA SENSOR");
  lcd.setCursor(0,1);
  lcd.print("  MOIST DAN TEMP");
  lcd.setCursor(0,2);
  lcd.print("  HUMD DAN LIGHT");
  lcd.setCursor(0,3);
  lcd.print("  EXIT");
  setMENU1();
  }
}

void setMENU2(){
  if(digitalRead(buttonhitam) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonhitam) == DITEKAN){}
    lcd.clear();
    setSUBMENU2();
  }else if(digitalRead(buttonmerah) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonmerah) == DITEKAN){}
    lcd.clear();
    setMENU1();
  }else if(digitalRead(buttonbiru) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonbiru) == DITEKAN){}
    lcd.clear();
    setMENU3();
  }
  lcd.setCursor(0,0);
  lcd.print("  SEMUA SENSOR");
  lcd.setCursor(0,1);
  lcd.print("->MOIST DAN TEMP");
  lcd.setCursor(0,2);
  lcd.print("  HUMD DAN LIGHT");
  lcd.setCursor(0,3);
  lcd.print("  EXIT");
  setMENU2();
}

void setMENU3(){
  if(digitalRead(buttonhitam) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonhitam) == DITEKAN){}
    lcd.clear();
    setSUBMENU3();
  }else if(digitalRead(buttonmerah) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonmerah) == DITEKAN){}
    lcd.clear();
    setMENU2();
  }else if(digitalRead(buttonbiru) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonbiru) == DITEKAN){}
    lcd.clear();
    menuEXIT();
  }
  lcd.setCursor(0,0);
  lcd.print("  SEMUA SENSOR");
  lcd.setCursor(0,1);
  lcd.print("  MOIST DAN TEMP");
  lcd.setCursor(0,2);
  lcd.print("->HUMD DAN LIGHT");
  lcd.setCursor(0,3);
  lcd.print("  EXIT");
  setMENU3();
}
  
void menuEXIT(){
  if(digitalRead(buttonhitam) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonhitam) == DITEKAN){}
    lcd.clear();
    MenuSetting();
  }else if(digitalRead(buttonmerah) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonmerah) == DITEKAN){}
    lcd.clear();
    setMENU3();
  }else if(digitalRead(buttonbiru) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonbiru) == DITEKAN){}
    lcd.clear();
    setMENU1();
  }
  lcd.setCursor(0,0);
  lcd.print("  SEMUA SENSOR");
  lcd.setCursor(0,1);
  lcd.print("  MOIST DAN TEMP");
  lcd.setCursor(0,2);
  lcd.print("  HUMD DAN LIGHT");
  lcd.setCursor(0,3);
  lcd.print("->EXIT");
  menuEXIT();
}
//SUBMENU
void setSUBMENU1(){
  if(digitalRead(buttonhitam) == DITEKAN){
    delay(50);
    while(digitalRead(buttonhitam) == DITEKAN){}
    lcd.clear();
    setMENU1();
  }
  else{
  DateTime now = rtc.now();
  Serial.print(count);
  Serial.print(".\t");
  Serial.print(now.year(), DEC);
  Serial.print("/");
  Serial.print(now.month(), DEC);
  Serial.print("/");
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  DateTime future (now + TimeSpan(7, 12, 30, 6));
    
  //Sensor Soil Moisture
  soilMoistureValue = analogRead(data_moist);
  Serial.println(" | Nilai ADC = " + String(soilMoistureValue));
  soilMoisturePercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  if(soilMoisturePercent <0){
      soilMoisturePercent=0;
    }
    else if(soilMoisturePercent>100){
      soilMoisturePercent=100;
    }
  Serial.print("Moisture   : ");
  Serial.println(soilMoisturePercent + String("%"));
  //Sensor SHT
  temp = (sht20.readTemperature()+1);     //Read Temperature
  humd = (sht20.readHumidity()-1.5);        //Read Humidity
  Serial.print(" | Temperature: ");              
  Serial.println(temp + String("C"));
  Serial.print(" | Humidity   : ");
  Serial.println(humd + String("%"));
  
  //intensitasCahaya
  uint16_t intensity = (lightMeter.readLightLevel()*2.5);     //Read Light Sensor
  Serial.println(intensity + String(" lux"));
//  if(intensity <= 200){
//  Serial.print(" | Its DARK, Turn on the LED : ");
//  Serial.println(intensity + String(" lux"));
//  } 
//  else{
//  Serial.print(" | Its BRIGHT, Turn off the LED : ");
//  Serial.println(intensity + String(" lux"));
//  Serial.println("");
//  }
  dataku = SD.open("sensor.txt", FILE_WRITE);
  if (dataku)
  {
    dataku.println("");
    dataku.print(count);
    dataku.print(".\t");
    dataku.print(now.year(), DEC);
    dataku.print("/");
    dataku.print(now.month(), DEC);
    dataku.print("/");
    dataku.print(now.day(), DEC);
    dataku.print(" (");
    dataku.print(daysOfTheWeek[now.dayOfTheWeek()]);
    dataku.print(") ");
    dataku.print(now.hour(), DEC);
    dataku.print(':');
    dataku.print(now.minute(), DEC);
    dataku.print(':');
    dataku.print(now.second(), DEC);
    dataku.print(".\t");
    dataku.print(" | Nilai ADC = " + String(soilMoistureValue));
    dataku.print(" | Moisture    = ");
    dataku.print(soilMoisturePercent + String("%"));
    dataku.print(" | Temperature = ");
    dataku.print(temp + String("C"));
    dataku.print(" | Humidity    = ");
    dataku.print(humd + String("%"));
    dataku.print(" | Light       = ");
    dataku.print(intensity + String(" lux"));
    dataku.close();

    Serial.println(" | Data Tersimpan");
    if(count>5000) count=0; 
    }
    else
    {
      Serial.println(" | Gagal Tersimpan!");
    }
    Serial.println("");
    count = count + 1;

  lcd.setCursor(0,0);
  lcd.print("Moisture   : ");
  lcd.print(soilMoisturePercent);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temperature: ");
  lcd.print(temp);
  lcd.print("C");
  lcd.setCursor(0,2);
  lcd.print("Humidity   : ");
  lcd.print(humd);
  lcd.print("%");
  lcd.setCursor(0,3);
  lcd.print("Light      : ");
  lcd.print(intensity);
  delay(500);
  lcd.clear();
  setSUBMENU1();
  }
}
  
void setSUBMENU2(){
    if(digitalRead(buttonhitam) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonhitam) == DITEKAN){}
    lcd.clear();
    setMENU2();
  }
  else{
    DateTime now = rtc.now();
    Serial.print(count);
    Serial.print(".\t");
    Serial.print(now.year(), DEC);
    Serial.print("/");
    Serial.print(now.month(), DEC);
    Serial.print("/");
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    DateTime future (now + TimeSpan(7, 12, 30, 6));
    //Sensor Soil Moisture
    soilMoistureValue = analogRead(data_moist);
    Serial.println(" | Nilai ADC = " + String(soilMoistureValue));
    soilMoisturePercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    if(soilMoisturePercent <0){
        soilMoisturePercent=0;
      }
      else if(soilMoisturePercent>100){
        soilMoisturePercent=100;
      }
    Serial.print(" | Moisture   : ");
    Serial.println(soilMoisturePercent + String("%"));
    //SHT20
    float temp = (sht20.readTemperature()+1);     //Read Temperature
    Serial.print(" | Temperature: ");              
    Serial.println(temp + String(" C"));
    
    if (soilMoisturePercent>=0 && soilMoisturePercent<=33 && temp>=25){
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Kering");
      Serial.println("Kondisi : Kering");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Panas");
      Serial.println("Kondisi : Panas");
    }
    else if (soilMoisturePercent>=0 && soilMoisturePercent<=33 && temp>=17 && temp<25){
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Kering");
      Serial.println("Kondisi : Kering");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Normal");
      Serial.println("Kondisi : Normal");
    }
    else if (soilMoisturePercent>=0 && soilMoisturePercent<=33 && temp<17){
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Kering");
      Serial.println("Kondisi : Kering");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Dingin");
      Serial.println("Kondisi : Dingin");
    }
    else if (soilMoisturePercent>33 && soilMoisturePercent<=66 && temp>=25){ 
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Normal");
      Serial.println("Kondisi : Normal");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Panas");
      Serial.println("Kondisi : Panas");
    }
    else if (soilMoisturePercent>33 && soilMoisturePercent<=66 && temp>=17 && temp<25){ 
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Normal");
      Serial.println("Kondisi : Normal");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Normal");
      Serial.println("Kondisi : Normal");
    }
    else if (soilMoisturePercent>33 && soilMoisturePercent<=66 && temp<17){ 
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Normal");
      Serial.println("Kondisi : Normal");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Dingin");
      Serial.println("Kondisi : Dingin");
    }
    else if (soilMoisturePercent>66 && temp>=25){ 
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Lembap");
      Serial.println("Kondisi : Lembap");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Panas");
      Serial.println("Kondisi : Panas");
    }
    else if (soilMoisturePercent>66 && temp>=17 && temp<25){
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Lembap");
      Serial.println("Kondisi : Lembap");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Normal");
      Serial.println("Kondisi : Normal");
    }
    else if (soilMoisturePercent>66 && temp<17){
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Lembap");
      Serial.println("Kondisi : Lembap");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Dingin");
      Serial.println("Kondisi : Dingin");
    }
    
    dataku = SD.open("sensor.txt", FILE_WRITE);
    if (dataku)
    {
    dataku.println("");
    dataku.print(count);
    dataku.print(".\t");
    dataku.print(now.year(), DEC);
    dataku.print("/");
    dataku.print(now.month(), DEC);
    dataku.print("/");
    dataku.print(now.day(), DEC);
    dataku.print(" (");
    dataku.print(daysOfTheWeek[now.dayOfTheWeek()]);
    dataku.print(") ");
    dataku.print(now.hour(), DEC);
    dataku.print(':');
    dataku.print(now.minute(), DEC);
    dataku.print(':');
    dataku.print(now.second(), DEC);
    dataku.print(".\t");
    dataku.print(" | Nilai ADC = " + String(soilMoistureValue));
    dataku.print(" | Moisture    = ");
    dataku.print(soilMoisturePercent + String("%"));
    dataku.print(" | Temperature = ");
    dataku.print(temp + String("C"));
    dataku.close();

    Serial.println(" | Data Tersimpan");
    if(count>5000) count=0; 
    }
    else
    {
      Serial.println(" | Gagal Tersimpan!");
    }
    Serial.println("");
    count = count + 1;
    
    lcd.setCursor(0,0);
    lcd.print("Moist   : ");
    lcd.print(soilMoisturePercent);
    lcd.print("%");
    lcd.setCursor(0,2);
    lcd.print("Temp    : ");
    lcd.print(temp);
    lcd.print("C");
    delay(500);
    lcd.clear();
    setSUBMENU2();
    }
}
void setSUBMENU3(){
    if(digitalRead(buttonhitam) == DITEKAN){
    delay(BOUNCE);
    while(digitalRead(buttonhitam) == DITEKAN){}
    lcd.clear();
    setMENU3();
  }
    else{
    DateTime now = rtc.now();
    Serial.print(count);
    Serial.print(".\t");
    Serial.print(now.year(), DEC);
    Serial.print("/");
    Serial.print(now.month(), DEC);
    Serial.print("/");
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    DateTime future (now + TimeSpan(7, 12, 30, 6));
    //Sensor SHT
    float humd = (sht20.readHumidity()-1.5);        //Read Humidity
    Serial.print(" | Humidity   : ");
    Serial.println(humd + String(" %"));
    //intensitasCahaya
    uint16_t intensity = (lightMeter.readLightLevel()*2.5);     //Read Light Sensor
    Serial.println(intensity + String(" lux"));
//    if (intensity <= 500){
//    Serial.print(" | Its DARK, Turn on the LED : ");
//    Serial.println(intensity + String(" lux"));
//    Serial.println("");
//    } 
//    else {
//    Serial.print(" | Its BRIGHT, Turn off the LED : ");
//    Serial.println(intensity + String(" lux"));
//    }
    if (humd>=0 && humd<=33 && intensity>=20000){
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Panas");
      Serial.println("Kondisi : Panas");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Terang");
      Serial.println("Kondisi : Terang");
    }
    else if (humd>=0 && humd<=33 && intensity>=2000 && intensity<20000){
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Panas");
      Serial.println("Kondisi : Panas");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Normal");
      Serial.println("Kondisi : Normal");
    }
    else if (humd>=0 && humd<=33 && intensity<2000){
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Panas");
      Serial.println("Kondisi : Panas");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Gelap");
      Serial.println("Kondisi : Gelap");
    }
    else if (humd>33 && humd<=66 && intensity>=20000){ 
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Normal");
      Serial.println("Kondisi : Normal");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Terang");
      Serial.println("Kondisi : Terang");
    }
    else if (humd>33 && humd<=66 && intensity>=2000 && intensity<20000){ 
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Normal");
      Serial.println("Kondisi : Normal");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Normal");
      Serial.println("Kondisi : Normal");
    }
    else if (humd>33 && humd<=66 && intensity<2000){ 
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Normal");
      Serial.println("Kondisi : Normal");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Gelap");
      Serial.println("Kondisi : Gelap");
    }
    else if (humd>66 && intensity>=20000){ 
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Lembap");
      Serial.println("Kondisi : Lembap");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Terang");
      Serial.println("Kondisi : Terang");
    }
    else if (humd>66 && intensity>=2000 && intensity<20000){
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Lembap");
      Serial.println("Kondisi : Lembap");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Normal");
      Serial.println("Kondisi : Normal");
    }
    else if (humd>66 && intensity<2000){
      lcd.setCursor(0,1);
      lcd.print("Kondisi : Lembap");
      Serial.println("Kondisi : Lembap");
      lcd.setCursor(0,3);
      lcd.print("Kondisi : Gelap");
      Serial.println("Kondisi : Gelap");
    }
    
    dataku = SD.open("sensor.txt", FILE_WRITE);
    if (dataku)
    {
    dataku.println("");
    dataku.print(count);
    dataku.print(".\t");
    dataku.print(now.year(), DEC);
    dataku.print("/");
    dataku.print(now.month(), DEC);
    dataku.print("/");
    dataku.print(now.day(), DEC);
    dataku.print(" (");
    dataku.print(daysOfTheWeek[now.dayOfTheWeek()]);
    dataku.print(") ");
    dataku.print(now.hour(), DEC);
    dataku.print(':');
    dataku.print(now.minute(), DEC);
    dataku.print(':');
    dataku.print(now.second(), DEC);
    dataku.print(".\t");
    dataku.print(" | Humidity    = ");
    dataku.print(humd + String("%"));
    dataku.print(" | Light       = ");
    dataku.print(intensity + String(" lux"));
    dataku.close();

    Serial.println(" | Data Tersimpan");
    if(count>5000) count=0; 
    }
    else
    {
      Serial.println(" | Gagal Tersimpan!");
    }
    Serial.println("");
    count = count + 1;

    lcd.setCursor(0,0);
    lcd.print("Humid   : ");
    lcd.print(humd);
    lcd.print("%");
    lcd.setCursor(0,2);
    lcd.print("Light   : ");
    lcd.print(intensity);
    lcd.print("lux");
    delay(500);
    lcd.clear();
    setSUBMENU3();
    }
  }
