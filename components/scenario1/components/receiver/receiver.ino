
// add RadioHead Library into Arduino IDE
// receiver reserved pin on Arduino Uno: D11

#include <RH_ASK.h>
#include <SPI.h> 

include "../../modules/rf433mhz-receiver.h"
RH_ASK rftx;

void setup(){
	Serial.begin(9600);
	initRF433(rftx);
}

void loop(){
	readRF433();
	delay(1000);
}