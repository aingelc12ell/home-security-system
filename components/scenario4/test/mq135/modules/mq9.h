
//#include <MQUnifiedsensor.h>


#define  RatioMQ9CleanAir (9.6) //RS / R0 = 60 ppm 

// MQ9(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
MQUnifiedsensor MQ9("Arduino UNO", 5, 10, MQ9pin, "MQ-9");

void initMQ9() {
 
  //Serial.begin(9600); //Init serial port

  MQ9.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ9.setA(1000.5); MQ9.setB(-2.186); // Configurate the ecuation values to get LPG concentration

  /*
    Exponential regression:
  GAS     | a      | b
  LPG     | 1000.5 | -2.186
  CH4     | 4269.6 | -2.648
  CO      | 599.65 | -2.244
  */
  
  MQ9.init(); 
  
  //Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ9.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += MQ9.calibrate(RatioMQ9CleanAir);
    Serial.print(".");
  }
  MQ9.setR0(calcR0/10);
  //Serial.println("  done!.");
  
  if(isinf(calcR0)) {Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0){Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply"); while(1);}
  /*****************************  MQ CAlibration ********************************************/ 
  //Serial.println("MQ-9");
  //Serial.println("|    LPG   |  CH4 |   CO  |");  
  //MQ9.serialDebug(true);
}

void checkMQ9() {
	Serial.println("|    LPG   |  CH4 |   CO  |");  
  MQ9.update(); // Update data, the arduino will be read the voltage on the analog pin
  //MQ9.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
  //MQ9.serialDebug(); // Will print the table on the serial port
  
  MQ9.setA(1000.5); MQ9.setB(-2.186); // Configurate the ecuation values to get LPG concentration
  float LPG = MQ9.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

  MQ9.setA(4269.6); MQ9.setB(-2.648); // Configurate the ecuation values to get LPG concentration
  float CH4 = MQ9.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

  MQ9.setA(599.65); MQ9.setB(-2.244); // Configurate the ecuation values to get LPG concentration
  float CO = MQ9.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup

  Serial.print("|    "); Serial.print(LPG);
  Serial.print("    |    "); Serial.print(CH4);
  Serial.print("    |    "); Serial.print(CO); 
  Serial.println("    |");
  
  delay(500); //Sampling frequency
}
