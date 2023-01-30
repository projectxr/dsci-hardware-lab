#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* Declaration of Input Pin****************************/

#define digitalpin D4
/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "RoboSpecies_Technologies_4g"             // Your SSID
#define WLAN_PASS       "Robo@1234"                               // Your Password

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "sanupiku"
#define AIO_KEY         "8916406efafe430bb9d216d0098db3e5"

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish sensor_1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/crash");

void MQTT_connect();

void setup() 
{
  Serial.begin(115200);
  //delay(10);
  pinMode(digitalpin, INPUT); 

  Serial.println(F("Adafruit MQTT Test"));

  // Connect to WiFi access point.
  Serial.println();
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

}

uint32_t x=0;

void loop()
{

  MQTT_connect();

  // Now we can publish stuff!
  Serial.print(F("\nSending Sensor's Value "));
  Serial.print("Sensor 1 ");
  Serial.println(digitalRead(digitalpin));
  Serial.print("...");

  int Value = digitalRead(digitalpin);
 
  if (! sensor_1.publish(Value))
  {
    Serial.println(F("Failed"));
  } 
  else
  {
    Serial.println(F("OK!"));
  }

  
  delay(2000);
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect()
{
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected())
  {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) 
  { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) 
       {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
