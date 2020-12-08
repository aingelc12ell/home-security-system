/** Must include
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
**/


void initNRF(){
	NRFradio.begin();                  //Starting the Wireless communication
	NRFradio.openWritingPipe(NRFaddress); //Setting the address where we will send the data
	NRFradio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
	NRFradio.stopListening();          //This sets the module as transmitter
}
