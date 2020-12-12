
//Include the library
#include <MQUnifiedsensor.h>

MQUnifiedsensor MQ2("Arduino UNO", 5, 10, MQ2pin, "MQ-2");
#define         RatioMQ2CleanAir        (9.83) //RS / R0 = 9.83 ppm 

void calibrateMQ2(int cycles){
	/*****************************  MQ CAlibration ********************************************/ 
  // Explanation: 
  // In this routine the sensor will measure the resistance of the sensor supposing before was pre-heated
  // and now is on clean air (Calibration conditions), and it will setup R0 value.
  // We recomend execute this routine only on setup or on the laboratory and save on the eeprom of your arduino
  // This routine not need to execute to every restart, you can load your R0 if you know the value
  // Acknowledgements: https://jayconsystems.com/blog/understanding-a-gas-sensor
  //Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for(int i = 1; i<=cycles; i ++)
  {
    MQ2.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += MQ2.calibrate(RatioMQ2CleanAir);
    //Serial.print(".");
  }
  MQ2.setR0(calcR0/cycles);
  Serial.print("R0 : ");
  Serial.println(calcR0/cycles);
  
  if(isinf(calcR0)) {Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0){Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply"); while(1);}
  /*****************************  MQ CAlibration ********************************************/ 
  
}

void initMQ2() {
  //Init the serial port communication - to debug the library
  Serial.begin(9600); //Init serial port

  //Set math model to calculate the PPM concentration and the value of constants
  MQ2.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ2.setA(574.25); MQ2.setB(-2.222); // Configurate the ecuation values to get LPG concentration
  /*
    Exponential regression:
    Gas    | a      | b
    H2     | 987.99 | -2.162
    LPG    | 574.25 | -2.222
    CO     | 36974  | -3.109
    Alcohol| 3616.1 | -2.675
    Propane| 658.71 | -2.168
  */
  MQ2.init(); 
  /* 
    //If the RL value is different from 10K please assign your RL value with the following method:
    MQ2.setRL(10);
  */
  
  //MQ2.setR0(mq2R0);
  calibrateMQ2(20);
  Serial.println("|    CO   |  LPG |   Prop  |");  
}

void checkMQ2(float *stats) {
  MQ2.update(); // Update data, the arduino will be read the voltage on the analog pin
  
  MQ2.setA(574.25); MQ2.setB(-2.222);
  float LPG = MQ2.readSensor();
  
  MQ2.setA(36974); MQ2.setB(-3.109);
  float CO = MQ2.readSensor();
  
  MQ2.setA(658.71); MQ2.setB(-2.168);
  float Propane = MQ2.readSensor();
  
  stats[0] = CO;
  stats[1] = LPG;
  stats[2] = Propane;
  

  Serial.print("|    "); Serial.print(CO);
  Serial.print("    |    "); Serial.print(LPG);
  Serial.print("    |    "); Serial.print(Propane); 
  Serial.println("    |");
  
  //MQ2.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
  //MQ2.serialDebug(); // Will print the table on the serial port
  //delay(500); //Sampling frequency
}
