#include <ESP8266WiFi.h>
#include <Wire.h>                       
#include "SH1106Wire.h"
#define fan_speed 12

char ssid[] = "ESP-test";        
char pass[] = "genisup-lab"; 
IPAddress server(192,168,4,15);     
WiFiClient client;

SH1106Wire display(0x3c, SDA, SCL);
void setup() 
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); 
  Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); 
  Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); 
  Serial.println(WiFi.BSSIDstr());

   display.init();
 display.flipScreenVertically();
 display.setFont(ArialMT_Plain_24);
}
void loop() 
{
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  client.connect(server, 80);
  Serial.print("Byte sent to the AP: ");
  Serial.println(client.print("\r"));
  String answer = String(14);//client.readStringUntil('\r');
  Serial.println("From the AP: " + answer);
  display.drawString(50,10,"PM2.5:");
   display.drawString(100, 10,answer);
   display.display();
   if(answer>="0" && answer<="15")
   analogWrite(fan_speed,64);
   else if(answer>="16" && answer<="45")
   analogWrite(fan_speed,128);
   if(answer>="46" && answer<="100")
   analogWrite(fan_speed,192);
   else
   analogWrite(fan_speed,255);
  client.flush();
  client.stop();
  //delay(2000);
}
