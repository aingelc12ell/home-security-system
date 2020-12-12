
void initRelaySwitch(int relaySwitchPin){
	pinMode(relaySwitchPin,OUTPUT);
}
void relaySwitch(int relaySwitchPin,int onOff){
	digitalWrite(relaySwitchPin, onOff);
}
void relaySwitchOn(int relaySwitchPin){
	relaySwitch(relaySwitchPin, HIGH);
}
void relaySwitchOff(int relaySwitchPin){
	relaySwitch(relaySwitchPin, LOW);
}
