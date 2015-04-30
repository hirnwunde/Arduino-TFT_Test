 
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// These are the pins used for the UNO
// for Due/Mega/Leonardo use the hardware SPI pins (which are different)
#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 10
#define _dc 9
#define _rst 8

// Using software SPI is really not suggested, its incredibly slow
//Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _mosi, _sclk, _rst, _miso);
// Use hardware SPI
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);

String inputString = "";


void setup() {

  Serial.begin(9600);
  while (!Serial);
  Serial.println("# = Serial | * = LCD");
  tft.begin();
  tft.fillScreen(ILI9340_BLACK);
  tft.setCursor(10,10);
  tft.setTextColor(ILI9340_WHITE);
  tft.setTextSize(3);
}

void loop() {
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    tft.fillScreen(ILI9340_BLACK);
    tft.setCursor(0,0);
    // read all the available characters
    while (Serial.available() > 0) {
      
      // display each character to the LCD
      char inChar = (char)Serial.read();
      
      
      if (inChar == '*') {
         tft.println(inputString);
         inputString= "";
      }
      
      if (inChar == '#') {
         Serial.println(inputString);
         inputString= "";
      }
      
      if (inChar != '#' or inChar != '*') {
         inputString += inChar;
       }
      
      
      //tft.write(Serial.read());
    }
  }
  
}
