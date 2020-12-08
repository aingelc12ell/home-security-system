
#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm  
#define MQ135R0 6.65

MQUnifiedsensor MQ135("Arduino UNO", 5, 10, MQ135pin, "MQ-135");

void calibrateMQ135(int cycles){
	float calcR0 = 0;
	Serial.println("Calibrating: ");
	
	for(int i = 1; i<=cycles; i ++)
	{
		MQ135.update(); // Update data, the arduino will be read the voltage on the analog pin
		calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
		Serial.print(".");
	}
	MQ135.setR0(calcR0/cycles);
	//MQ135.setR0(MQ135R0);
	Serial.print("R0 : ");
	Serial.println(calcR0/cycles);
	delay(2000);
}
void initMQ135() {
	//Set math model to calculate the PPM concentration and the value of constants
	MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b

	MQ135.init(); 

	MQ135.setR0(MQ135R0);
	//calibrateMQ135(100);
}

void checkMQ135(float *stats) {
	/*
	Exponential regression:
	GAS      | a      | b
	CO       | 605.18 | -3.937  
	Alcohol  | 77.255 | -3.18 
	CO2      | 110.47 | -2.862
	Tolueno  | 44.947 | -3.445
	NH4      | 102.2  | -2.473
	Acetona  | 34.668 | -3.369
	*/
	//Serial.println("MQ-135");
	//Serial.println("|    CO   |  Alcohol |   CO2  |  Tolueno  |  NH4  |  Acteona  |");

	MQ135.update(); // Update data, the arduino will be read the voltage on the analog pin

	MQ135.setA(605.18); MQ135.setB(-3.937); // Configurate the ecuation values to get CO concentration
	float CO = MQ135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

	//MQ135.setA(77.255); MQ135.setB(-3.18); // Configurate the ecuation values to get Alcohol concentration
	//float Alcohol = MQ135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

	MQ135.setA(110.47); MQ135.setB(-2.862); // Configurate the ecuation values to get CO2 concentration
	float CO2 = MQ135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

	//MQ135.setA(44.947); MQ135.setB(-3.445); // Configurate the ecuation values to get Tolueno concentration
	//float Tolueno = MQ135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

	MQ135.setA(102.2 ); MQ135.setB(-2.473); // Configurate the ecuation values to get NH4 concentration
	float NH4 = MQ135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

	//MQ135.setA(34.668); MQ135.setB(-3.369); // Configurate the ecuation values to get Acetona concentration
	//float Acetona = MQ135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

	stats[0]=CO;
	stats[1]=CO2+200;
	stats[2]=NH4;


//delay(500); //Sampling frequency
}