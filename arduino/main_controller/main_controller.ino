#include <CO2Sensor.h>
#include "CO2Sensor.h"
#include "sSense_BME680.h"


// Sensor Instance
CO2Sensor co2Sensor(A0,0.99,100);
BME680_Class BME680;


// Utils function
// BME680
float altitude(const float seaLevel=1013.25) 
{
  /*wikipedia equation - original Zanshin code*/
  static float Altitude;
  int32_t temp, hum, press, gas;
  BME680.getSensorData(temp,hum,press,gas); // Get the most recent values from the device
  Altitude = 44330.0*(1.0-pow(((float)press/100.0)/seaLevel,0.1903)); // Convert into altitude in meters
  return(Altitude);
} // of method altitude()

float calculate_altitude( float pressure, bool metric = true, float seaLevelPressure = 101325)
{
  /*Equations courtesy of NOAA - code ported from BME280*/;
  float altitude = NAN;
  if (!isnan(pressure) && !isnan(seaLevelPressure)){
    altitude = 1000.0 * ( seaLevelPressure - pressure ) / 3386.3752577878;
  }
  return metric ? altitude * 0.3048 : altitude;
}

float temperatureCompensatedAltitude(int32_t pressure, float temp=21.0 /*Celsius*/, float seaLevel=1013.25) 
{
  /*Casio equation - code written by itbrainpower.net*/
  float Altitude;
  Altitude = (pow((seaLevel/((float)pressure/100.0)), (1/5.257))-1)*(temp + 273.15) / 0.0065; // Convert into altitude in meters
  return(Altitude);  //this are metric value
} 



void setup() {
 
//  Set baud rate 
  Serial.begin(9600);

//  while(!Serial) {delay(10);} // Wait
  
//  Setup Sensor
// ---------MG811----------
  co2Sensor.calibrate();
    
// --------BME680----------
//  while (!BME680.begin(I2C_STANDARD_MODE)) // Start BME680 using I2C protocol
//  {
//    Serial.println("-  Unable to find BME680. Waiting 1 seconds.");
//    delay(1000);
//  } // of loop until device is located  
//  
//  Serial.println("- Setting 16x oversampling for all sensors");
//  BME680.setOversampling(TemperatureSensor,Oversample16); // Use enumerated type values
//  BME680.setOversampling(HumiditySensor,   Oversample16);
//  BME680.setOversampling(PressureSensor,   Oversample16);
//  
//  Serial.println("- Setting IIR filter to a value of 4 samples");
//  BME680.setIIRFilter(IIR4);
//  
//  Serial.println("- Setting gas measurement to 320C for 150ms");
//  BME680.setGas(320,150); // 320ï¿½c for 150 milliseconds
//  Serial.println();
  
}

void loop() {
  // put your main code here, to run repeatedly:

// --------  [ MG811 : A0 Pin : C02 sensor ] --------
int co2 = co2Sensor.read();
  Serial.print(" CO2 : ");
  Serial.print(co2);
  Serial.print("\n");

// -------- [ BME680 : A4,A5 Pin : Temperature, Humidity, Pressure, Gas] ---------
//static int32_t temperature, humidity, pressure, gas;
//BME680.getSensorData(temperature,humidity,pressure,gas); // Get most recent readings
//  Serial.print("\r\nSensor data >>\t\t");                       // Temperature in deci-degrees
//  Serial.print(temperature/100.0,2);                       // Temperature in deci-degrees
//  Serial.print("C\t");                          
//  Serial.print(humidity/1000.0,2);                         // Humidity in milli-percent
//  Serial.print("%\t");
//  Serial.print(pressure/100.0,2);                          // Pressure in Pascals
//  Serial.print("hPa\t");
//  //Serial.print(pressure);                          // Pressure in Pascals
//  //Serial.print("Pa ");
//  Serial.print(gas/100.0,2);
//  Serial.println("mOhm");
//
//  Serial.println("\r\nCalculated altitude");
//
//  Serial.print("temp comp [CASIO equation]: ");
//
//  //temperatureCompensatedAltitude(int32_t pressure, float temp =21.0, const float seaLevel=1013.25)
//  Serial.print(temperatureCompensatedAltitude(pressure, temperature/100.0/*, 1022.0*/),2); 
//  Serial.print("m\t");
//
//
//  Serial.print("NOAA equation: ");
//
//  //float calculate_altitude( float pressure, bool metric = true, float seaLevelPressure = 101325)
//  Serial.print(calculate_altitude((long)pressure,true),2); //calculate_altitude
//  //Serial.print(calculate_altitude((long)pressure,true, (long)102200.0),2); //calculate_altitude
//  Serial.print("m\t");
//
//  Serial.print("WIKI equation: ");
//  Serial.print(altitude(),2); 
//  Serial.println("m \r\n");
//
//

// Global delay
//  delay(1000);
}
