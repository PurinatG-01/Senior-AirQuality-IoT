#include <CO2Sensor.h>


CO2Sensor co2Sensor(A0,0.99,100);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  printf("----Initialize----");
  co2Sensor.calibrate();

}

void loop() {
  // put your main code here, to run repeatedly:
  int CO2 = co2Sensor.read();
  Serial.print("CO2 : ");
  Serial.print(CO2);
  Serial.print("\n");
}
