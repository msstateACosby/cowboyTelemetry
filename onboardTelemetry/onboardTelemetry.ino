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
Adafruit_ICM20948 icm;
uint16_t measurement_delay_us = 65535;

//global variables
RH_RF95 rf95(RFM95_CS, RFM95_INT);
File logfile;
int currentTime;
void sendData(const char* data, int datalen)
{
  digitalWrite(LEDPIN, HIGH);
  delay(10);
  digitalWrite(LEDPIN, LOW);
  // put your main code here, to run repeatedly:
  Serial.println("Transmitting");
  
  rf95.send((uint8_t *)data, datalen);
  rf95.waitPacketSent();
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (rf95.waitAvailableTimeout(1000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
      Serial.print("Got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);    
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
  else
  {
    Serial.println("No reply, is there a listener around?");
  }
  
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
  if (!icm.begin_I2C()) {
 
    Serial.println("Failed to find ICM20948 chip");
  }
  icm.setAccelRange(ICM20948_ACCEL_RANGE_16_G);
  icm.setGyroRange(ICM20948_GYRO_RANGE_2000_DPS);
  uint16_t accel_divisor = icm.getAccelRateDivisor();
  float accel_rate = 1125 / (1.0 + accel_divisor);
  uint8_t gyro_divisor = icm.getGyroRateDivisor();
  float gyro_rate = 1100 / (1.0 + gyro_divisor);
  icm.setMagDataRate(AK09916_MAG_DATARATE_10_HZ);
  
  rf95.setTxPower(23, false);

  
  
}

void loop() {
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t mag;
  sensors_event_t temp;
  icm.getEvent(&accel, &gyro, &temp, &mag);

  currentTime = millis();
  String data;
  
  //sprintf(data, "Accel X: %f, Accel Y: %f, Accel Z: %f", 2.0f, accel.acceleration.y, accel.acceleration.z);
  data = "Accel "+ String(currentTime) +" "+ String(accel.acceleration.x)
      + " " + String(accel.acceleration.y)
      + " " + String(accel.acceleration.z) + "\0";
  Serial.println(data.c_str());
  sendData(data.c_str(), data.length());

  data = "Gryo " + String(currentTime) + " " +String(gyro.gyro.x)
      + " " + String(gyro.gyro.y)
      + " " + String(gyro.gyro.z);
  Serial.println(data.c_str());
  sendData(data.c_str(), data.length());

  data = "Magne "+ String(currentTime) +" "+ String(mag.magnetic.x)
      + " " + String(mag.magnetic.y)
      + " " + String(mag.magnetic.z) + "\0";
  Serial.println(data.c_str());
  sendData(data.c_str(), data.length());

  data = "Temp " + String(currentTime) + " " +String(temp.temperature) + "\0";
  Serial.println(data.c_str());
  sendData(data.c_str(), data.length());
  
  
  
}
