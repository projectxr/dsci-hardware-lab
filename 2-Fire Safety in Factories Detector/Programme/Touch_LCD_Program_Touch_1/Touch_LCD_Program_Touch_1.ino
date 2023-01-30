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

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#define t_SCK 3              
#define t_CS 4                
#define t_MOSI 5              
#define t_MISO 6             
#define t_IRQ 7          


URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);

extern uint8_t BigFont[];

int x, y;


void setup()
{
pinMode(2,OUTPUT);
pinMode(A0,INPUT);
digitalWrite(2,LOW);
   tft.begin();
  tft.setRotation(45);
  tft.fillScreen(ILI9341_WHITE);
  
  tft.fillCircle(70,120,50,ILI9341_RED);
  tft.fillCircle(250,120,50,ILI9341_GREEN); 
/////Header
tft.fillRoundRect(0,0,320,58, 10,ILI9341_YELLOW);
  tft.setCursor(10,20);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK);
  tft.println("SAFETY UNIT CONTROL PANEL");

  tft.drawLine(160, 70, 160, 165, ILI9341_BLACK);

  tft.setCursor(210,40);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_PINK);
  tft.println("CONTROL ROOM 001");

  Serial.begin(9600);
  ts.InitTouch();
  ts.setPrecision(PREC_MEDIUM);
////////////Button Position Setup
  tft.setCursor(35,112);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("E-STOP");
  tft.setCursor(220,112);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("RESET");
////Creating Black Area
tft.fillRoundRect(0,180,320,58, 10,ILI9341_BLACK);
tft.fillRoundRect(175,188,140,40, 10,ILI9341_WHITE);

  tft.setCursor(5,200);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("LIVE GAS LEVEL");

  //tft.setFont(BigFont);
}
void loop()
{
  while (true)
  {
    if (ts.dataAvailable())
    {
      ts.read();
      x=ts.getX();
      y=ts.getY();
      Serial.print("Value of X \n");
      Serial.println(x);
      Serial.print("Value of Y \n");
      Serial.println(y);
     
      if(x>200 && x<=280)
      {
        digitalWrite(2,LOW);
      }
      if(x>30 && x<=120)
      {
        digitalWrite(2,HIGH);        
      }
    }
   int gas=analogRead(A0);
   if(gas>1021)
   {
  
   tft.setCursor(185,200);
   tft.setTextSize(2);
   tft.setTextColor(ILI9341_RED,ILI9341_WHITE);
   tft.println("HAZARDIOUS");
   }
   else
   {
   tft.setCursor(185,200);
   tft.setTextSize(2);
   tft.setTextColor(ILI9341_GREEN,ILI9341_WHITE);
   tft.println(" LEVEL OK ");
  
   }
   }



}