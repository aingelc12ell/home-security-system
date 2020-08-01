
bool setAlarm = LOW; // global check for alarm
bool systemUp = HIGH;

//------- PIN REGISTRY
// 3 - vibratePin   : IN  : 
// 4 - laserPin    : OUT : laser light
// 5 - uhEchoPin    : IN  : Ultrasonic echo pin
// 6 - uhTrigPin    : OUT : Ultrasonic trigger pin
// 7 - dht11Pin     : IN  : Digital Humidity and Temperature
// 9 - speakerPin   : OUT : Speaker alarm pin
// 11 - resetButton : IN  : set Alarm to OFF state
// 12 - greenLED    : OUT : green LED light
// 13 - redLED      : OUT : red LED light

// 25

// 45 - openReedPin : IN  : Magnetic switch
// 46 - codePins
// 47 - codePins
// 48 - codePins
// 49 - codePins
// 50 - codePins
// 51 - codePins
// 52 - codePins
// 53 - codePins

// A0 - ambientLightPin : ambient light sensor/ laser receiver
// A1 - tempPin     : temperature sensor
// A2 - flamePin    : Flam sensor

//------ NUMBER CODE REGISTRY
// 0
// 1 - switch
// 2 - dht Temp
// 3 - flame
// 4 - laser trip
// 6 - vibrate
// 7 - reed/magnet
// 8 - temperature
// 9 - untrasonic 


//------- MODULES : setA
#include "modules/codeLight.h"
#include "modules/resetSwitch.h"
#include "modules/lights.h"
#include "modules/speakerAlarm.h"
#include "modules/ultrasonic.h"
//#include "modules/ambientlight.h"
#include "modules/vibration.h"
#include "modules/openReedSwitch.h"
#include "modules/temperature.h"
#include "modules/flame.h"
#include "modules/laser.h"
//DHT
#include "libraries/dht.h"
#include "libraries/dht.cpp"
#include "modules/DHT11.h"



//------- EXECUTE ALARM : conditions are set in each function
void doAlarm(){
    doLights();
    doSpeaker();
    //send SMS
}

//------ WHAT TO CHECK : setB
void checkForAlarm(){
  checkUltraSonic();
  checkTempSensor();
  //checkAmbientLight();
  checkReedSwitch();
  checkVibration();
  checkFlame();
  checkDHT11();
  checkLaser();
  checkResetButton();
}

//------ SET UP ROUTINES
void setup() {
  Serial.begin(9600);
  initCodeLights();
  initResetButton();
  initLights();
  initSpeaker();
  initVibration();
  initUltraSonic();
  initTempSensor();
  initReedSwitch();
  initFlame();
  initLaser();
  initDHT11();
}

//------ KEEP CHECKING UNTIL ALARM
void loop() {
  checkForAlarm();
  if(systemUp == HIGH){
    doAlarm();
    doCodeLight();
  }
}
