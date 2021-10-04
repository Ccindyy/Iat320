//Reference: Example from the Adafruit TSL2591 library

int led = 9;
int brightness = 0;

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); // pass in a number for the sensor identifier (for your use later)


void displaySensorDetails(void) //used for testing
{
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(sensor.max_value); Serial.println(F(" lux"));
  Serial.print  (F("Min Value:    ")); Serial.print(sensor.min_value); Serial.println(F(" lux"));
  Serial.print  (F("Resolution:   ")); Serial.print(sensor.resolution, 4); Serial.println(F(" lux"));  
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
  delay(500);
}

void configureSensor(void)
{
  tsl.setGain(TSL2591_GAIN_LOW);    // 1x gain (bright light)
  tsl.setTiming(TSL2591_INTEGRATIONTIME_400MS); //how long it takes to sense light

  /* Display the gain and integration time for reference sake */  
//  Serial.println(F("------------------------------------"));
//  Serial.print  (F("Gain:         "));
//  tsl2591Gain_t gain = tsl.getGain();
//  switch(gain)
//  {
//    case TSL2591_GAIN_LOW:
//      Serial.println(F("1x (Low)"));
//      break;
//    case TSL2591_GAIN_MED:
//      Serial.println(F("25x (Medium)"));
//      break;
//    case TSL2591_GAIN_HIGH:
//      Serial.println(F("428x (High)"));
//      break;
//    case TSL2591_GAIN_MAX:
//      Serial.println(F("9876x (Max)"));
//      break;
//  }
//  Serial.print  (F("Timing:       "));
//  Serial.print((tsl.getTiming() + 1) * 100, DEC); 
//  Serial.println(F(" ms"));
//  Serial.println(F("------------------------------------"));
//  Serial.println(F(""));
}

void setup(void) 
{
  //Serial.begin(9600);
  
//  Serial.println(F("Starting Adafruit TSL2591 Test!"));
//  
//  if (tsl.begin()) 
//  {
//    Serial.println(F("Found a TSL2591 sensor"));
//  } 
//  else 
//  {
//    Serial.println(F("No sensor found ... check your wiring?"));
//    while (1);
//  }
    
  /* Display some basic information on this sensor */
  
  /* Configure the sensor */
  configureSensor();

  //configure LED
  pinMode(led, OUTPUT);

}

void simpleRead(void)
{
  
  uint16_t x = tsl.getLuminosity(TSL2591_VISIBLE); //get value from the sensor

//  Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
//  Serial.print(F("Luminosity: "));
//  Serial.println(x, DEC);

  //map the brightness according to the light sensor. The less light, the brighter the LED.
  brightness = map(x, 0, 100, 0, 255);
 
  //Serial.println(brightness);
}

void loop(void) 
{ 
  simpleRead(); 
  analogWrite(led, brightness);
  
  delay(500);
  
}
