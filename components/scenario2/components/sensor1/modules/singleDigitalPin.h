
// setup and check a sensor that uses a single digital pin as input

void initDigital(int dPin){
	pinMode(dPin,INPUT);
}

int checkDigital(int dPin){
	return digitalRead(dPin);
}