// ----------------------- Library -------------------------------

// Protothreading
#include <TimedAction.h>

// Sensors
#include "CO2Sensor.h"
#include "sSense_BME680.h"
#include "PMS.h"
#include <SoftwareSerial.h>
#include <Wire.h>

// Blynk 
#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

// Thinger
#include <ThingerWiFiNINA.h>

// ------------------- Global Variable ---------------------------
// Sensor Instance
CO2Sensor co2Sensor(A0,0.99,100);
BME680_Class BME680;
PMS pms(Serial1);
PMS::DATA data;

int loop_count = 0;


// WiFi
#define SECRET_SSID "NB-001 3735"
#define SECRET_PASS "1122334455"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

// Blynk
#define BLYNK_PRINT Serial
char auth[] = "GS3mZFpy8AJTO97oFDyxUd8d_sujg_d_";

// Thinger
#define USERNAME "senior2020airquality"
#define DEVICE_ID "Arduino_1"
#define DEVICE_CREDENTIAL "m&z-B@M!ZyzT"
ThingerWiFiNINA thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);


// ----------------------------- Utils function -----------------------------
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

// -------------------------Timed Action------------------------------

int mg_process(){
  int co2 = co2Sensor.read();
  Serial.println("[ MG811 ]");
  Serial.print("CO2 : ");
  Serial.print(co2);
  Serial.println("\n");

  // Blynk
//  Blynk.virtualWrite(V0,co2);

  return co2;
}

void bme_process(){
  static int32_t temperature, humidity, pressure, gas;
  Serial.println("[ BME680 ]");
  BME680.getSensorData(temperature,humidity,pressure,gas); // Get most recent readings
  Serial.print("Temperature : ");                       // Temperature in deci-degrees
  Serial.print(temperature/100.0,2);                       // Temperature in deci-degrees
  Serial.println(" C\t");
  int rTemp = round(temperature/100.0);
 
  Serial.print("Humidity : ");                          
  Serial.print(humidity/1000.0,2);                         // Humidity in milli-percent
  Serial.println("%\t");
  int rHumidity = humidity/1000.0;
  
  Serial.print("Pressure : ");
  Serial.print(pressure/100.0,2);                          // Pressure in Pascals
  Serial.println(" hPa\t");
  int rPressure = pressure/100.0;
  
  Serial.print("Gas : ");
  Serial.print(gas/100.0,2);
  Serial.println(" mOhm\n");
  int rGas = gas/100.0;
  
  // Blynk write data
//  Blynk.virtualWrite(V1, rTemp);
//  Blynk.virtualWrite(V2, rHumidity);
//  Blynk.virtualWrite(V3, rPressure);
//  Blynk.virtualWrite(V4, rGas);
  
}

void pms_process(){
  
  pms.requestRead();
  if (pms.readUntil(data))
  {
    Serial.println("[ PMS7003 ]");
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);
  }
  else
  {
    Serial1.println("No data.");
  }

// Blynk
//  Blynk.virtualWrite(V5, data.PM_AE_UG_1_0);
//  Blynk.virtualWrite(V6, data.PM_AE_UG_2_5);
//  Blynk.virtualWrite(V7, data.PM_AE_UG_10_0);
  

}

TimedAction mgAction = TimedAction(0,mg_process);
TimedAction bmeAction = TimedAction(0,bme_process);
TimedAction pmsAction = TimedAction(0,pms_process);


// ----------------------------------------------------------------
// ----------------------------- Main -----------------------------
// ----------------------------------------------------------------

void setup() {
 
//  Set baud rate 
  Serial.begin(9600);
  
  while(!Serial) {delay(10);} // Wait
  
//  Setup Sensor
// ---------MG811----------
  co2Sensor.calibrate();
    
// --------BME680----------
  while (!BME680.begin(I2C_STANDARD_MODE)) // Start BME680 using I2C protocol
  {
    Serial.println("-  Unable to find BME680. Waiting 1 seconds.");
    delay(1000);
  } // of loop until device is located  
  
  Serial.println("- Setting 16x oversampling for all sensors");
  BME680.setOversampling(TemperatureSensor,Oversample16); // Use enumerated type values
  BME680.setOversampling(HumiditySensor,   Oversample16);
  BME680.setOversampling(PressureSensor,   Oversample16);
  
  Serial.println("- Setting IIR filter to a value of 4 samples");
  BME680.setIIRFilter(IIR4);
  
  Serial.println("- Setting gas measurement to 320C for 150ms");
  BME680.setGas(320,150); // 320ï¿½c for 150 milliseconds
  Serial.println();

//  --------PMS7003----------
  Serial1.begin(9600);

// --------------- WiFi + Blynk --------------
  Blynk.begin(auth, ssid, pass);

// --------------- WiFi + Thinger ------------
  thing.add_wifi(SECRET_SSID, SECRET_PASS);

  thing["TestData"] >> [](pson &out){
    out["Data_1"] = 1;
  };
  
//  
}

// -------------------------------------------------------------------


void loop() {
  Serial.print("--------------- ");
  Serial.print(loop_count++);
  Serial.println(" ---------------");
  
//  Blynk function invoke
  Blynk.run();
// Thinger function invoke
  thing.handle();

// --------  [ MG811 : A0 Pin : C02 sensor ] --------
//  mgAction.check();

// -------- [ BME680 : A4,A5 Pin : Temperature, Humidity, Pressure, Gas ] ---------
//  bmeAction.check();

// -------- [ PMS7003 : TX,RX Pin : PM 1.0, 2.5, 10.0 ] ---------
//  pmsAction.check();

    Serial.println("Start");
  thing.write_bucket("Arduino_1_bucket", "TestData");

  delay(3000);

}
