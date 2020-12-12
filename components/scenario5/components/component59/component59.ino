//ethernet Relay

#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>

int systat,cycle = 500; // number fo cycles until it reads/records a normal status
int cycleOrig = cycle;



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

#define i2cScenario5 50
#include "modules/i2c.h"

void setup(){
	Serial.begin(9600);
	initEthernet();
	Wire.begin();
}

void loop(){
	Serial.print("........reading main system : ");
	int systat = i2cRead(i2cScenario5);
	Serial.println(systat);
	if(systat > 0){
		sendEthStatus(systat);
    cycle = 1; //next cycle can record normal status
	}else{
		if(cycle == 0){
			sendEthStatus(systat);
			cycle = cycleOrig;
		}
		cycle--; //will not record this cycle
	}
  //systat = 0; //reset
  delay(500);
}
