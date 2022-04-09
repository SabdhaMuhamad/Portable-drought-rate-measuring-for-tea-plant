
#include <Wire.h>
//#include "DFRobot_SHT20.h"

int adc, output;

void setup()
{
    Serial.begin(9600);
//    Serial.println("SHT20 Example!");
//    sht20.initSHT20();                                  // Init SHT20 Sensor
//    delay(100);
//    sht20.checkSHT20();                                 // Check SHT20 Sensor




}


void loop()
{
//    float humd = sht20.readHumidity();                  // Read Humidity
//    float temp = sht20.readTemperature();               // Read Temperature
//    Serial.print(" Temperature:");
//    Serial.print(temp);
//    Serial.print("C");
//    Serial.print(" Humidity:");
//    Serial.print(humd);
//    Serial.print("%");
//    Serial.println();
  adc=55;
  output = map(adc,0,100,540,313);
  Serial.println(output);
    delay(3000);
}
