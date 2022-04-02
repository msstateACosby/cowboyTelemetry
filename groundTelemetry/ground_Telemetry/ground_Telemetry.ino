#include <SPI.h>
#include <RH_RF95.h>
#include <SD.h>
#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


//pins of the program
#define RFM95_RST     11   // "A"
#define RFM95_CS      10   // "B"
#define RFM95_INT     6    // "D"
#define cardSelect    4


#define RF95_FREQ 915.0
#define LEDPIN 13

//global variables
RH_RF95 rf95(RFM95_CS, RFM95_INT);
char recieveChars[RH_RF95_MAX_MESSAGE_LEN];
File logfile;

bool returnvalue(int *returnLen){
  
  if(rf95.available()){
    
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len))
    {
      digitalWrite(LEDPIN, HIGH);
      //RH_RF95::printBuffer("Received: ", buf, len);
      //Serial.print("Got: ");
      //Serial.println((char*)buf);
       //Serial.print("RSSI: ");
      //Serial.println(rf95.lastRssi(), DEC);

      // Send a reply
      uint8_t data[] = "And hello back to you";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      //Serial.println("Sent a reply");
      digitalWrite(LEDPIN, LOW);
      memcpy(recieveChars, buf, sizeof(char) * RH_RF95_MAX_MESSAGE_LEN);
      *returnLen = len;
      return true;
      }
    else
    {
       Serial.println("Receive failed");
    }
  }
  return false;
}
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  pinMode(13, OUTPUT);
  
  if (!SD.begin(cardSelect))
  {
    Serial.println("Card init failed");
  }
 
  while (!rf95.init()) 
  {
      Serial.println("LoRa radio init failed");
      while (1);
  }

  if (!rf95.setFrequency(RF95_FREQ)) {
      Serial.println("setFrequency failed");
      while (1);
  }
  rf95.setTxPower(23, false);
}

void loop() {
  
  int len;
  if (returnvalue( &len))
  {
   Serial.print("Recieved: ");
   Serial.println(recieveChars);
   
  }
 
}
