
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
const char* ssid = "Genisup";
const char* password = "@subh9406";
 
ESP8266WebServer server(80);
 
void handleRoot() 
{
  server.send(200, "text/plain", "Its genisup lab demo of esp8266");
}
 
void setup(void){
  Serial.begin(9600);
  Serial.println("");
  WiFi.mode(WIFI_AP);           
  WiFi.softAP(ssid, password);
 
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
 
  server.on("/", handleRoot);
 
  server.begin();
  Serial.println("HTTP server started");
}
void loop(void){
  server.handleClient();
}
