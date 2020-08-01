int photoLightPin = 0; //analog
int laserPin = 4;

void initLaser(){
	pinMode(laserPin,OUTPUT);
}

void checkLaser(){
	digitalWrite(laserPin,HIGH);
	int lightVar = analogRead(photoLightPin);
	Serial.print("Laser read: ");
	Serial.println(lightVar);
	if(lightVar < 300){
		codeShow(4);
		setAlarm = HIGH;
	}
}