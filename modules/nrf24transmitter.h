#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 RF24Tx(8, 9); // CE, CSN         
const byte address[6] = "AABBC";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.

void initRF24Tx() {
	RF24Tx.begin();                  //Starting the Wireless communication
	RF24Tx.openWritingPipe(address); //Setting the address where we will send the data
	RF24Tx.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
	RF24Tx.stopListening();          //This sets the module as transmitter
}

void doRF24Tx(){
	Serial.println(systemStatus);
	//if(sizeof(systemStatus) > 1)
	//{
		RF24Tx.write(&systemStatus, sizeof(systemStatus));                  //Sending the message to receiver
	//}
	//const char text[] = "Simple Message";
	//char text[32] = lcdMessage[systemStatus];
	//RF24Tx.write(&text,sizeof(text));
}
