#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h>

RF24 radio(8,9); // CE, CSN
LiquidCrystal_I2C lcd(0x26, 16, 2);

const byte addresses[][6] = {"00001", "00002"};
boolean buttonState = 0;
int nrfMessage;
//char *nrfMessage;
bool nrfAlarm = 0;
const char *lcdMessage[] = {
  "System Normal" //0
  ,"Fire Alarm" //1
  ,"Air Quality Alarm" //2
  ,"Ball switched" //3
  ,"A#4" //4
  ,"A#5" //5
  ,"A#6" //6
  ,"A#7" //7
  ,"Alarm # 8" //8
  ,"Alarm # 9" //9
  ,"Alarm # 10" //10
  ,"Alarm: Ultrasonic" //11
  ,"Alarm: Laser Tripwire" //12
  ,"Alarm: Reed Switch" // 13
  ,"Alarm # 14" // 14
  ,"Alarm # 15" //15
  ,"Alarm" //16
};

void setup() {
    Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
    lcd.begin();
    lcd.backlight();
}

void loop() {
  Serial.println("......");
  lcd.clear();
  lcd.print("Awaiting message");
  
  //int potValue = analogRead(A0);
  //int angleValue = map(potValue, 0, 1023, 0, 180);
  /*if(nrfAlarm == HIGH){
      delay(5);
      radio.stopListening();
      radio.write(&nrfMessage, sizeof(nrfMessage));
  }*/

  delay(5);
  radio.startListening();
  if(radio.available()){
    Serial.println("Radio on..");
    radio.read(&nrfMessage, sizeof(nrfMessage));
    if (nrfMessage >= 0) {
    //if(nrfMessage != ""){
      //digitalWrite(led, HIGH);
      lcd.setCursor(0,1);
      lcd.print(lcdMessage[nrfMessage]);
      //lcd.print(nrfMessage);
      Serial.print("Message Received: ");
      Serial.println(nrfMessage);
    }
  }
  delay(500);
}
