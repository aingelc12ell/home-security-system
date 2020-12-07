#include <RH_ASK.h>
#include <SPI.h> 

void initRF433(RH_ASK rf_driver)
{
    rf_driver.init();
}
 
void readRF433(RH_ASK rf_driver)
{
    uint8_t buf[16];
    uint8_t buflen = sizeof(buf);
    if (rf_driver.recv(buf, &buflen))
    {
      Serial.print("Message Received: ");
      Serial.println((char*)buf);
    }
}
