/** must include
#include <OneWire.h>
#include <DallasTemperature.h>
**/
/**
#include "libraries/OneWire/OneWire.h"
#include "libraries/DallasTemperature/DallasTemperature.h"
**/



void initKY001()
{
  // start serial port
  Serial.begin(9600);
  // Start up the library
  KY001.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
}

float checkKY001()
{ 
  // call KY001.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  KY001.requestTemperatures(); // Send the command to get temperatures

  Serial.print("Temperature : ");
  float tempC = KY001.getTempCByIndex(0);
  Serial.println(tempC); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  return tempC;
}