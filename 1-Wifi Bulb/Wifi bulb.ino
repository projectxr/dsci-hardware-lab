// Goggle Home Created By ***Circuit

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define Relay1 0

#define WLAN_SSID       "Circuit"              // Your SSID
#define WLAN_PASS       "Anurag@123"          // Your password

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER    "io.adafruit.com"                         //Adafruit Server
#define AIO_SERVERPORT 1883                   
#define AIO_USERNAME  "circuitexe"                            // Username
#define AIO_KEY       "aio_qwxi456Q3J0ejU0oaUajOOqRQtjB"     // Auth Key

//WIFI CLIENT

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay1"); 

void MQTT_connect();

void setup() 
{ 
  Serial.begin(9600);
  // For WiFi Bulb............
  pinMode(Relay1, OUTPUT);
  digitalWrite(Relay1, 0);

  //......................
  //16, 2 digital pins are ...........connected with inbuilt leds..
  pinMode(16, OUTPUT);
  pinMode(2, OUTPUT);
   
  // Connect to WiFi access point...
  
  Serial.println(); 
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());

  ledBlink_1(); // Shows WiFi Connected

  mqtt.subscribe(&Light1);

}

void loop() 
{
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) 
  {
    if (subscription == &Light1) 
    {
      Serial.print(F("Got: "));
      Serial.println((char *)Light1.lastread);
      int Light1_State = atoi((char *)Light1.lastread);
      digitalWrite(Relay1, Light1_State); 
    }

  } 
}

void MQTT_connect() 
{
  int8_t ret;
  if (mqtt.connected()) 
  {
    return;
  }

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) 
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000); 
    retries--;
    if (retries == 0) 
    {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");

  ledBlink_2(); // This shows mqtt is connected 
}

//******************************************************
void ledBlink_1()
{
  digitalWrite(16, 1);
  delay(500);
  digitalWrite(16, 0);
  delay(500);
  digitalWrite(16, 1);
  delay(500);
  digitalWrite(16, 0);
  delay(500);    
    
}

void ledBlink_2()
{
  digitalWrite(2, 1);
  delay(500);
  digitalWrite(2, 0);
  delay(500);
  digitalWrite(2, 1);
  delay(500);
  digitalWrite(2, 0);
  delay(500);      
}