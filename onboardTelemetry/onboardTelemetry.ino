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
File logfile;


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
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
  // put your main code here, to run repeatedly:

}
