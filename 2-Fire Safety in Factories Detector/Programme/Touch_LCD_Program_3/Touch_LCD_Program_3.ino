#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include "Adafruit_ILI9341.h"
#include <Arduino.h>
#include "URTouch.h" 

#define TFT_MISO 12
#define TFT_CLK 13
#define TFT_MOSI 11
#define TFT_DC 9
#define TFT_RST 8
#define TFT_CS 10
#define rain A0


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#define t_SCK 3              
#define t_CS 4                
#define t_MOSI 5              
#define t_MISO 6             
#define t_IRQ 7              

URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);

void setup()
{
  Serial.begin(9600);
  pinMode(rain,INPUT);
  tft.begin();

  tft.setRotation(0);
  tft.fillScreen(ILI9341_WHITE);
  tft.fillRect(10,10,220,340,ILI9341_PINK);
  tft.setCursor(12,12);
  tft.setTextSize(4);
  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
  tft.setTextWrap(true);
  tft.println("Factory Gas Level");
  //tft.drawLine(12,90,230,90,ILI9341_BLACK);
  
}
void loop()
{
int rain_drop=analogRead(rain);
Serial.println(rain_drop);
tft.setTextSize(4);
tft.setTextColor(ILI9341_WHITE,ILI9341_PINK);
tft.println(rain_drop);
delay(500);
}
