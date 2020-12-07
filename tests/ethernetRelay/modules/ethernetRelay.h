#include <SPI.h>
#include <Ethernet.h>


// Initialise client
EthernetEthClient EthClient;

void initEthernet() 
{
    
    if (Ethernet.begin(mac) == 0) 
    {
        // Failed to configure Ethernet using DHCP
        Ethernet.begin(mac, ip);
    }

    // give the Ethernet shield a second to initialize
    delay(1000);
}
void sendEthStatus(int stat){
    // if you get a connection, report back via serial
    if (EthClient.connect(HOST_NAME, HTTP_PORT)) 
    {
        Serial.println("connected");
        // Make a HTTP request
        EthClient.println("GET " + PATH_NAME + "?aut=aingel&hid=1&sid=1&stat=" + String(stat) + " HTTP/1.1");
		EthClient.println("Host: " + String(HOST_NAME));
		EthClient.println("Connection: close");
		EthClient.println(); // end HTTP header
		while(EthClient.connected()) {
		  if(EthClient.available()){
			// read an incoming byte from the server and print it to serial monitor:
			char c = EthClient.read();
			Serial.print(c);
		  }
		}
		// the server's disconnected, stop the client:
		EthClient.stop();
    } else {
		Serial.println("connection failed");
	}
}
