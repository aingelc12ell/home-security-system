
byte i2cRead(int address){
	byte bval ;
	long entry = millis();
	// Read one byte at a time
	Wire.requestFrom(address, 1); 
	// Wait 100 ms for data to stabilize
	while (Wire.available() == 0 && (millis() - entry) < 100)  Serial.println(".....Waiting");
	// Place data into byte
	if  (millis() - entry < 100) bval = Wire.read();
	return bval;
}