#include <RH_ASK.h>
#include <SPI.h> 

int val;
char *msg; //manipulate for display and sending
 
RH_ASK rf_driver;
 
//include modules here
#include "../../modules/tapShock.h"
#include "../../modules/ballSwitch.h"

void sendRF433(char *msg){
    Serial.print("Sending: ");
	Serial.println(msg);
	
	rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
	
    delay(1000);
}

void setup()
{
    rf_driver.init();
	//initialize Modules here
	initTapSwitch();
	initballSwitch();
	///////////
    Serial.begin(9600);
}
 
void loop()
{
    //check Modules here
	msg = checkTapShock();
	if(msg!=""){
		sendRF433(msg);
	}
	msg = checkballSwitch();
	if(msg!=""){
		sendRF433(msg);
	}
}
