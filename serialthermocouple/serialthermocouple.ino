#include <max6675.h>
#include <Ticker.h>

Ticker ThermoCoupleTicker;

int thermoDO = 12;
int thermoCS = 15;
int thermoCLK = 14;

float dbTemp = 0;
float data_filtered[2] = {0, 0};

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

int readThermoCouple(){
  float alpha = 0.7;
  dbTemp = (float)thermocouple.readCelsius();
  // Low Pass Filter
  data_filtered[1] = alpha * dbTemp + (1 - alpha) * data_filtered[0];
  data_filtered[0] = data_filtered[1];
  return data_filtered[1];
}

void ThermoCoupleTask(){
  Serial.println(readThermoCouple());
}

void setup() {
  Serial.begin(9600);
  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);

  ThermoCoupleTicker.attach(0.25, ThermoCoupleTask); 
}

void loop() { 

}
