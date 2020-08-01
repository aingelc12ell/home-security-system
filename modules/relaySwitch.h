
int relaySwitchPin = 6;

void initRelaySwitch(){
	pinMode(relaySwitchPin,OUTPUT);
}
void relaySwitchOn(){
	digitalWrite(relaySwitchPin, HIGH);
}
void relaySwitchOff(){
	digitalWrite(relaySwitchPin, LOW);
}