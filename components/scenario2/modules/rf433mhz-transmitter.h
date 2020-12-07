#include <RH_ASK.h>
#include <SPI.h> 

char *msg; //manipulate for display and sending

void sendRF433(RH_ASK rf_driver, char *msg){
	rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(1000);
}

void initRF433(RH_ASK rf_driver)
{
    rf_driver.init();
	
}
