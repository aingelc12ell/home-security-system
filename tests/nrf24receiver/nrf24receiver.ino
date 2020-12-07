#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 RF24Rx(8, 9); // CE, CSN
const byte address[6] = "AABBC";
char defMsg[16] = "Awaiting Status";
char *lcdMessage[] = {
  "System Normal" //0
  ,"Fire Alarm" //1
  ,"Air Quality Alarm" //2
  ,"Reed Switched" //3
  ,"Ultrasonic On" //4
  ,"Hall Magnetized" //5
  ,"Linear Hall" //6
  ,"Mercury Tilted  " //7
  ,"Alarm # 8" //8
  ,"Alarm # 9" //9
  ,"Alarm # 10" //10
  ,"Alarm: Ultrasonic" //11
  ,"Alarm: Laser Tripwire" //12
  ,"Alarm: Reed Switch" // 13
  ,"Alarm # 14" // 14
  ,"Alarm # 15" //15
  ,"Alarm" //16
};
int intdata;

#include "modules/lcd.h"

void setup() {
	Serial.begin(9600);
	RF24Rx.begin();
	RF24Rx.openReadingPipe(0, address);   //Setting the address at which we will receive the data
	RF24Rx.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
	RF24Rx.startListening();              //This sets the module as receiver
	
	initLCD();
}
void loop()
{
	if (RF24Rx.available())              //Looking for the data.
	{
        //Saving the incoming data
		RF24Rx.read(&intdata, sizeof(intdata));    //Reading the data
		Serial.println(intdata);
		doLCD(lcdMessage[intdata]);
   //char text[32] = "";
   //RF24Rx.read(&text,sizeof(text));
   //Serial.println(text);
   //doLCD(text);
	}
	 else{
		doLCD(defMsg);
    Serial.println("No data");
	 }
	delay(500);
}
