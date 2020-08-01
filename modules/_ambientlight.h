int ambientLightPin = 0; //analog
int ambientLightVal = 0;

void initAmbientLight(){
	
}

void checkAmbientLight(){
	ambientLightVal = analogRead(ambientLightPin);
	Serial.print("Ambient Light : ");
	Serial.println(ambientLightVal); 
}