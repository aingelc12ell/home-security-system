#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
/*
#include <LiquidCrystal_I2C.h>*/
char *lcdMessage[] = {
  "System Normal" //0
  ,"Fire Alarm" //1
  ,"A#2" //2
  ,"A#3" //3
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

const byte ethernetI2C = 25;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "homesecurity.accessph.net";
IPAddress ip(192, 168, 1, 177);
IPAddress myDns(192, 168, 1, 1);
EthernetClient client;
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement
int canSend = 0;
char *message;

//LiquidCrystal_I2C lcd(0x27, 16, 2);

void sendWebRequest(){
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80) && canSend == 1) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.print("GET /?aingel=");
	client.print(message);
	client.println(" HTTP/1.1");
    client.println("Host: homesecurity.accessph.net");
    client.println("Connection: close");
    client.println();
    Serial.println(message);
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}
void initEthernet(){
	// You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    //lcd.print("Eth config FAIL");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
      //lcd.print("Eth X connect");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
    //lcd.print(Ethernet.localIP());
  }
  if (client.connect(server, 80)) {
    Serial.println("Ready to receive and transmit");
    //lcd.print("Eth READY");
    //showLCD(0);
    canSend = 1;
  }
}
void sendEthernetSignal(int xx){
	int x = Wire.read();
    Serial.print("Signal Received : ");
    Serial.println(x);
	sprintf(message,"%s",lcdMessage[x]);
	sendWebRequest();
 //showLCD(x);
}
void initEthernetRelay(){
	initEthernet();
	Wire.begin(ethernetI2C);
	Wire.onReceive(sendEthernetSignal);
}

/////////////////////////////////////
/*
void initLCD(){
  lcd.begin();
  lcd.backlight();
  
}
void showLCD(int i){
  lcd.clear();
  lcd.print(i);
  lcd.setCursor (0,1);
  lcd.print(lcdMessage[i]);
  Serial.print(lcdMessage[i]);
}
*/
/////////////////////////////////////
void setup(){
  Serial.begin(9600);
  //initLCD();
  initEthernetRelay();
}

void loop(){
  
}
