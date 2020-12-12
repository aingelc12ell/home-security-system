/** must include
#include <OneWire.h>
#include <DallasTemperature.h>
**/
/**
#include "libraries/OneWire/OneWire.h"
#include "libraries/DallasTemperature/DallasTemperature.h"
**/
DeviceAddress temperatureSensorAddress;  

void printDeviceAddress(DeviceAddress deviceAddress){
  for (int i = 0; i < 8; i++)
  {
    Serial.print("0x");
    if (deviceAddress[i] < 0x10) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
    if (i < 7) Serial.print(", ");
  }
  Serial.println("");
}

void initKY001()
{
  // start serial port
  Serial.begin(9600);
  // Start up the library
  KY001.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
  int connectedDevicesNomber = KY001.getDeviceCount();   
  Serial.print("Ky001 count ");
  Serial.println(connectedDevicesNomber);
  
  KY001.getAddress(temperatureSensorAddress, 0);                                // get the address of the first device connected to the bus 
  printDeviceAddress(temperatureSensorAddress); 
  
}

float checkKY001()
{ 
  // call KY001.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  //KY001.requestTemperatures(); // Send the command to get temperatures
  
  KY001.requestTemperaturesByAddress(temperatureSensorAddress);                  // command for a device with a specific address to perform a temperature conversion (to read the temperature)
  float tempC = KY001.getTempC(temperatureSensorAddress); 

  Serial.print("Temperature : ");
  //float tempC = KY001.getTempCByIndex(0);
  Serial.println(tempC); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  return tempC;
}