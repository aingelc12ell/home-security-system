
// add RadioHead Library into Arduino IDE
// tranmitter reserved pin on Arduino Uno: D12
#include <RH_ASK.h>
#include <SPI.h> 

include "../../modules/rf433mhz-transmitter.h"
RH_ASK rftx;

String a;

void setup(){
	Serial.begin(9600);
	initRF433(rftx);
}

void loop(){
	while(Serial.available()) {
		a = Serial.readString();
		Serial.println(a);
		sendRF433(rftx,a);
	}
}