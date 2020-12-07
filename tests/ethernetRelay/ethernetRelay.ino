
int systemStatus = 0;

#include "modules/ethernetRelay.h"
// MAC address for controller
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// IP address for controller
IPAddress ip(192,168,0,177);
// Web Server adress
int    HTTP_PORT   = 80;
String HTTP_METHOD = "GET";
char   HOST_NAME[] = "hss.systemsbybit.com";
String PATH_NAME   = "/";


#include "modules/i2c.h"
#define I2C_SLAVE_ADDR 9

void receiveI2Cdata(){
	while (0 < Wire.available()) {
		int x = Wire.read(); //only interested in last byte
	}
	if(x > 0){
		systemStatus = x;
		sendEthStatus(systemStatus);
		delay(500);
	}
}

void setup(){
	Serial.begin(9600);
	initEthernet();
	initI2CSlave(I2C_SLAVE_ADDR);
}

void loop(){
}