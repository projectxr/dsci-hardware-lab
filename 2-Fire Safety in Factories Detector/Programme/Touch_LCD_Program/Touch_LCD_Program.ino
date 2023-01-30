#include <Adafruit_GFX.h>
#include <SPI.h>
#include "Adafruit_ILI9341.h"
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

extern uint8_t BigFont[];

int x, y;
char stCurrent[20]="";
int stCurrentLen=0;
char stLast[20]="";

void setup()
{
  pinMode(rain,INPUT);
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(ILI9341_WHITE);
  tft.fillRoundRect(10,10,220,340,10,ILI9341_PINK);
  tft.setCursor(12,12);
  tft.setTextSize(4);
  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
  tft.println("Gas Hazard Level");
 
  //tft.setTextWrap(false);
 
  
}
void loop()
{
  
int gas=analogRead(rain);

if(gas>1020)
{
tft.setTextSize(3);
//tft.setCursor(12,90);
tft.setTextColor(ILI9341_WHITE,ILI9341_RED);
tft.println("Hazadous gas Detected \n");
//tft.drawString("Hazadous Gas Detected",20,100,2,ILI9341_BLACK);
delay(500);
}
else
{
//tft.setCursor(12,110);
tft.setTextSize(3);
tft.setTextColor(ILI9341_WHITE,ILI9341_GREEN);
tft.println("ALL LEVEL OK \n");
//tft.drawString("ALL LEVEL OK",20,100,2,ILI9341_BLACK);
delay(500);
}


}
