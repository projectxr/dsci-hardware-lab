
#include "WiFi.h"
#include "AsyncUDP.h"

const char * ssid = "NetWork";
const char * password = "12345678";

#define pir 4
#define led 13
int value = 0;

AsyncUDP udp;

void setup()
{
    pinMode(pir, INPUT);
    pinMode(led, OUTPUT);
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) 
    {
        Serial.println("WiFi Failed");
        while(1) 
        {
            delay(1000);
            connectingLed();

        }
    }
    connectedLed();
    if(udp.connect(IPAddress(192,168,1,100), 1234)) 
    {
        Serial.println("UDP connected");
        UDPLed();
        udp.onPacket([](AsyncUDPPacket packet) 
        {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            //reply to the client
            packet.printf("Got %u bytes of data", packet.length());
        });
        //Send unicast
        udp.print("Hello Server!");
    }
}

void loop()
{
    value = digitalRead(pir);
    Serial.print("Value : ");
    Serial.println(value);
    if(value == 1)
    {
    delay(100);
    udp.broadcastTo("Motion", 1234);      //Send broadcast on port 1234
    digitalWrite(led, 1);

    }
    else
    {
    delay(100);
    udp.broadcastTo("No Motion", 1234);    //Send broadcast on port 1234
    digitalWrite(led, 0);
    }

}


//led patterns for project...........

void connectingLed()
{
  digitalWrite(led, 1);
  delay(100);
  digitalWrite(led, 0);
  delay(200);
}
void connectedLed()
{
  digitalWrite(led, 1);
  delay(2000);
  digitalWrite(led, 0);
}

void UDPLed()
{
  digitalWrite(led, 1);
  delay(1000);
  digitalWrite(led, 1);
  delay(500);
}
