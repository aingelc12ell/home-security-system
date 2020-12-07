//#include <LiquidCrystal_I2C.h>
#include <RH_ASK.h>
#include <SPI.h> 

RH_ASK rf_driver;
//LiquidCrystal_I2C lcd(0x26, 16, 2);
 
void initRF433()
{
    rf_driver.init();
    lcd.begin();
    lcd.backlight();
    Serial.begin(9600);
}
 
void setRF433()
{
    //lcd.clear();
    //lcd.print("Awaiting message");
    // Set buffer to size of expected message
    uint8_t buf[16];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
      //lcd.setCursor(0,1);
      //lcd.print((char*)buf);
      Serial.print("Message Received: ");
      Serial.println((char*)buf);
    }
    //delay(500);
}

//////////////////////////////
void setup(){
	initRF433();
}
void loop(){
	setRF433();
}