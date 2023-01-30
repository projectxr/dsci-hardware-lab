#include "WiFi.h"
#include "AsyncUDP.h"

int len;
// Set AP credentials
#define AP_SSID "NetWork"
#define AP_PASS "12345678"
 
IPAddress local_IP(192,168,4,1);
IPAddress remote_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

AsyncUDP udp;

#define buzz 15
#define led 13

void setup()
{
    pinMode(buzz, OUTPUT);
    pinMode(led, OUTPUT);
    Serial.begin(115200);
    Serial.println("Starting access point...");
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(AP_SSID, AP_PASS);

    if(udp.listen(1234)) 
    {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
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
            len = packet.length();
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            //reply to the client
            packet.printf("Got %u bytes of data", packet.length());
        });
    }
}

void loop()
{
    if(len == 6)
    {
      digitalWrite(led,1);
      digitalWrite(buzz,1);
      delay(200);
      digitalWrite(led,0);
      digitalWrite(buzz,0);
      delay(500);

    }
    else
    {
      digitalWrite(led,0);
      digitalWrite(buzz,0);
    }    
}
