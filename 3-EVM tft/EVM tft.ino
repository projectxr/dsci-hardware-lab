#include <Adafruit_GFX.h>
#include <SPI.h>
#include "Adafruit_ILI9341.h" 

#define TFT_MISO 12
#define TFT_LED 6
#define TFT_CLK 13
#define TFT_MOSI 11
#define TFT_DC 9
#define TFT_RST 8
#define TFT_CS 10

#define S1 5
#define S2 4
#define S3 3
#define result 2
#define buzz 7

int vote1=0;
int vote2=0;
int vote3=0;
int vote=0;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS,TFT_DC,TFT_MOSI,TFT_CLK,TFT_RST,TFT_MISO);

void setup()
{
Serial.begin(9600);

pinMode(TFT_LED,OUTPUT);
pinMode(S1, INPUT);
pinMode(S2,INPUT);
pinMode(S3,INPUT);
pinMode(result,INPUT);
pinMode(buzz,OUTPUT);

digitalWrite(TFT_LED,HIGH);
digitalWrite(S1, LOW);
digitalWrite(S2, LOW);
digitalWrite(S3, LOW);
digitalWrite(result, LOW);

tft.begin();
tft.setRotation(1);
//tft.setCursor(10,20);
tft.fillScreen(ILI9341_WHITE);
tft.setCursor(10,20);



tft.fillRoundRect(150, 20, 150, 40,5, ILI9341_BLACK);

tft.setCursor(152,32);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("Total Voting");
//tft.fillCircle(10, 10, 20, ILI9341_YELLOW);

tft.setCursor(10,20);
tft.fillRoundRect(10, 20, 100, 40, 5, ILI9341_YELLOW);

tft.setCursor(10,40);
tft.fillRoundRect(10, 80, 100, 40, 5, ILI9341_RED);

tft.setCursor(10,60);
tft.fillRoundRect(10, 140, 100, 40, 5, ILI9341_GREEN);

//tft.setCursor(100,250);
tft.drawRoundRect(130, 75, 180, 50, 5, ILI9341_BLUE);
tft.fillRect(0, 200, 400, 50, ILI9341_BLACK);

}
void loop()
{

tft.setCursor(150,90);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK,ILI9341_WHITE);
   tft.println(vote);
vote=vote1+vote2+vote3;

if(digitalRead(S1)==1)
{
  vote1++;
  delay(500);
  vote=vote1+vote2+vote3;
  tft.fillRoundRect(10, 20, 100, 40, 5, ILI9341_YELLOW);
  tft.setCursor(42,32);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK,ILI9341_YELLOW);
  tft.println("AAP");
  delay(1000);
  tft.fillRoundRect(10, 20, 100, 40, 5, ILI9341_YELLOW);

}


if(digitalRead(S2)==1)
{
  vote=vote1+vote2+vote3;
vote2++;
delay(500);
//Serial.print(vote2);
//Serial.println("BJP");
  tft.setCursor(42,92);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK,ILI9341_RED);
  tft.println("BJP");
  delay(1000);
  tft.fillRoundRect(10, 80, 100, 40, 5, ILI9341_RED);
  //tft.fillRoundRect(10, 80, 100, 40, 5, ILI9341_RED);
}

//while(digitalRead(S2)==1);

if(digitalRead(S3)==1)
{
vote3++;
delay(500);
vote=vote1+vote2+vote3;
//Serial.print(vote3);
//Serial.println("INC");
  tft.setCursor(42,152);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK, ILI9341_GREEN);
  tft.println("INC");
  delay(1000);
  tft.fillRoundRect(10, 140, 100, 40, 5, ILI9341_GREEN);
  //delay(500);
  //tft.fillRoundRect(10, 140, 100, 40, 5, ILI9341_GREEN);
}

if(digitalRead(result)==1)
{

vote=vote1+vote2+vote3;

if(vote>0)
{
if(vote1 > vote2 && vote1 > vote3)
{
//lcd.print("A is Winner");
//Serial.println("Winner is AAP");
  tft.setCursor(80,210);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("AAP is Winner");

  tft.setCursor(42,250);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE,ILI9341_YELLOW);
  tft.println(vote1);
}
else if((vote2 > vote1 && vote2 > vote3))
{
//Serial.println("Winner is BJP");
//lcd.print("B is Winner");
  tft.setCursor(80,210);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("BJP is Winner");

  tft.setCursor(42,92);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK,ILI9341_RED);
  tft.println(vote2);

}
else if((vote3 > vote1 && vote3 > vote2))
{
 // Serial.println("Winner is INC");
 
  tft.setCursor(90,210);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("INC is Winner");

  tft.setCursor(42,152);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK,ILI9341_GREEN);
  tft.println(vote3);

}
 
else
{
  tft.setCursor(130,350);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK);
  tft.println("No Result");
}
//vote1=0;vote2=0;vote3=0;vote=0;
}

else
{
  tft.setCursor(130,350);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK);
  tft.println("No Voting Done"); 
}

}

}
