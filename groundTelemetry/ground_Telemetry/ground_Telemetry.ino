#include <SPI.h>
#include <RH_RF95.h>
#include <SD.h>
#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>


//pins of the program
#define RFM95_RST     11   // "A"
#define RFM95_CS      10   // "B"
#define RFM95_INT     6    // "D"
#define cardSelect    4

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

// OLED FeatherWing buttons map to different pins depending on board:
#if defined(ESP8266)
  #define BUTTON_A  0
  #define BUTTON_B 16
  #define BUTTON_C  2
#elif defined(ESP32) && !defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
  #define BUTTON_A 15
  #define BUTTON_B 32
  #define BUTTON_C 14
#elif defined(ARDUINO_STM32_FEATHER)
  #define BUTTON_A PA15
  #define BUTTON_B PC7
  #define BUTTON_C PC5
#elif defined(TEENSYDUINO)
  #define BUTTON_A  4
  #define BUTTON_B  3
  #define BUTTON_C  8
#elif defined(ARDUINO_NRF52832_FEATHER)
  #define BUTTON_A 31
  #define BUTTON_B 30
  #define BUTTON_C 27
#else // 32u4, M0, M4, nrf52840, esp32-s2 and 328p
  #define BUTTON_A  9
  #define BUTTON_B  6
  #define BUTTON_C  5
#endif

#define RF95_FREQ 915.0
#define LEDPIN 13

//global variables
RH_RF95 rf95(RFM95_CS, RFM95_INT);
char recieveChars[RH_RF95_MAX_MESSAGE_LEN];
File logfile;
unsigned long timer;
unsigned long currentTime;
String accelString;
String magString;
String gyroString;
String tempString;

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

bool check_for_SDcard(){
    if (!SD.begin(cardSelect))
  {
    Serial.println("Card init failed");
    return false;
  }
  else{
    return true;
  }
}

void check_for_radioModule(){
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

void store_dataSD(){
  if (
}


void screenPrint(){
  //start

  Serial.println("128x64 OLED Start");
  delay(250); // wait for the OLED to power up
  display.begin(0x3C, true); // Address 0x3C default

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setRotation(1);
  Serial.println("Button test");

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  // text display tests
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,0);
  
  display.display(); // actually display all of the above
  //finish

}

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  pinMode(13, OUTPUT);

  check_for_SDcard();

  check_for_radioModule();
  
  screenPrint();

  currentTime = millis();
}

void loop() {

  int len;
  if (returnvalue(&len)){
    String myString = String (recieveChars);
    Serial.print("Recieved: ");
    Serial.println(myString);

    if (myString.charAt(0) == 'M'){
      magString = String (myString);
    }
    if (myString.charAt(0) == 'G'){
      gyroString = String (myString);
    }
    if (myString.charAt(0) == 'A'){
      accelString = String (myString);
    }
    if (myString.charAt(0) == 'T'){
      tempString = String (myString);
    }
    store_dataSD();
  }
  unsigned long newTime = millis();
  timer += newTime - currentTime;
  currentTime = newTime;

  if (timer > 250){
    timer = 0;

   display.clearDisplay();
   
   display.setCursor(0,0);
   display.println(magString);
   display.println(accelString);
   display.println(gyroString);
   display.println(tempString);
   display.display();
   delay(5);
  }

  
}
