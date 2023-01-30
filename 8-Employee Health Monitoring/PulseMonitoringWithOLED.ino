#define USE_ARDUINO_INTERRUPTS true 
#include <U8glib.h>
#include <PulseSensorPlayground.h>


U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);
#define pulsePin A0
#define green 2
#define red   3
#define pulsePin A0 

PulseSensorPlayground pulseSensor; 

int samples[128]; 
int currentSample = 0; 

void setup() 
{
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  Serial.begin(9600); 
  u8g.begin();
  u8g.setFont(u8g_font_unifont);
  pulseSensor.analogInput(pulsePin); 
  pulseSensor.begin(); 
}

void loop() 
{
  int BPM = pulseSensor.getBeatsPerMinute(); 
  Serial.println(BPM);
    samples[currentSample] = BPM;
    currentSample = (currentSample + 1) % 128;
    u8g.firstPage();
    do {
      u8g.setPrintPos(5,60);
      u8g.print("Heart Rate: ");
      u8g.print(BPM);
      for (int i = 0; i < 120; i++) 
      {
        u8g.drawPixel(i, 40 - (samples[i]/10));
      }
    } while(u8g.nextPage());
    if (BPM>60 && BPM <=100) 
    {
    digitalWrite(green, 1);
    Serial.println("Normal !");
    }
    else
    {
     digitalWrite(green, 0);
     digitalWrite(red, 1);
     Serial.println("AbNormal !");
    }
}