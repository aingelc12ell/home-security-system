#include <Wire.h>
#define ANSWERSIZE 5

void initI2CMaster(){
	Wire.begin();
}
void initI2CSlave(int addr){
	Wire.begin(addr);
	Wire.onReceive(receiveI2Cdata);
}

void doI2CMaster(int addr){
	Wire.beginTransmission(addr);
	Wire.write(0);
	Wire.endTransmission();
}
