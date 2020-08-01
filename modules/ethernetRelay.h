#include <Wire.h>

const byte ethernetI2C = 25;

void sendEthernetSignal(int xx){
	Wire.beginTransmission(ethernetI2C);
    Wire.write(xx);
    Wire.endTransmission();
}
void initEthernetRelay(){
	//Serial.begin(9600);
	Wire.begin();
}

/////////////////////////////////////

