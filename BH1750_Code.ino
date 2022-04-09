#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  lightMeter.begin();
  Serial.println("Sensing started!...");
  delay(500);
  
}

void loop() {
  uint16_t intensity= lightMeter.readLightLevel();
  Serial.print("Light intesnsity: ");  
  Serial.print(intensity);
  Serial.println(" lx");
  delay(500);
}
