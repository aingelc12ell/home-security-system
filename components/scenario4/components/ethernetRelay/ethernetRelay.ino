//ethernet Relay

#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>

int systat;



// MAC address for controller
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// IP address for controller
IPAddress ip(192,168,1,177);
IPAddress myDns(8, 8, 8, 8);

// Web Server adress
int    HTTP_PORT   = 80;
String HTTP_METHOD = "GET";
char   HOST_NAME[] = "hss.systemsbybit.com";
String PATH_NAME   = "/";

EthernetClient EthClient;

#include "modules/ethernetRelay.h"

#define i2cScenario3 40
#include "modules/i2c.h"

void setup(){
	Serial.begin(9600);
	initEthernet();
	Wire.begin();
}

void loop(){
	Serial.print("........reading main system : ");
	systat = i2cRead(i2cScenario3);
	Serial.println(systat);
	sendEthStatus(systat);
	delay(1000);
}
