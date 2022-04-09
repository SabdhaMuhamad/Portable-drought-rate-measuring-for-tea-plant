#define data_pH A0        // Definisi pin GPIO35 untuk sensor pH

//Sensor pH
int sensorValue = 0;                          // Nilai ADC sensor pH
float pH = 0.0;                               // Nilai pH setelah dikonversi
float Voltage;

void setup() {
  Serial.begin(9600);
}

void loop() {
    //Sensor pH Haya
//  sensorValue = analogRead(data_pH);
//  Voltage = sensorValue * (5 / 1023.0);
//  pH = ((0.0599*sensorValue)-16.949)+0.5;        // rumus berdasarkan datasheet
//  
//  //Mencetak output Sensor pH ke Serial Monitor
//  Serial.print("ADC Values = ");
//  Serial.print(sensorValue);
//  Serial.print("   ");
//  Serial.print("Voltage = ");
//  Serial.print(Voltage);
//  Serial.print("      pH Level = ");
//  Serial.println(pH);
//  Serial.println("");

  //Sensor pH Datasheet
  sensorValue = analogRead(data_pH);
  pH = (-0.0693*sensorValue)+7.3855;        // rumus berdasarkan datasheet
  Voltage = sensorValue * (5 / 1023.0);
  //Mencetak output Sensor pH ke Serial Monitor
  Serial.print("Nilai ADC = ");
  Serial.print(sensorValue);
  Serial.print("   ");
  Serial.print("Voltage = ");
  Serial.print(Voltage);
  Serial.print("  Kadar pH = ");
  Serial.println(pH);
  Serial.println("");
  delay(5000);
}
