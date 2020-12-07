#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <LiquidCrystal_I2C.h>

RF24 radio(8,9); // CE, CSN
//LiquidCrystal_I2C lcd(0x26, 16, 2);

const byte addresses[][6] = {"00001", "00002"};
boolean buttonState = 0;
int nrfMessage;
//char *nrfMessage;
bool nrfAlarm = 0;


#include "C:\Users\AingelCarbonell\Dropbox\MIT@SLU\HomeSecurity\V3\home-security-system\modules\ballSwitch.h"

void setup() {
    Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MIN);
    //lcd.begin();
    //lcd.backlight();
  initballSwitch();
}
void nrfSendMessage(){
  delay(5);
  radio.stopListening();
  Serial.print("Sending Message: ");
  Serial.println(nrfMessage);
  radio.write(&nrfMessage, sizeof(nrfMessage));
}

void loop() {
  //lcd.clear();
  //lcd.print("Awaiting message");
  Serial.println("................");
  
  checkballSwitch();
  if(nrfMessage > 0){
    nrfSendMessage();
  }

  if(nrfMessage >= 0){
    nrfSendMessage();
  }
  /*radio.startListening();
  if(!radio.available()){
    radio.read(&nrfMessage, sizeof(nrfMessage));
    if (nrfMessage != "") {
      //digitalWrite(led, HIGH);
      lcd.setCursor(0,1);
      lcd.print((char*)nrfMessage);
      Serial.print("Message Received: ");
      Serial.println((char*)nrfMessage);
    }
  }*/
  delay(500);
}
