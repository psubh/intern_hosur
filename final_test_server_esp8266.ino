//#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
//#include <Wire.h>                       
//#include "SH1106Wire.h"
//
//const char* ssid = "subhash";       
//const char* password = "subhash1998";
//const char* Commands_Reply;               
//const char * host = "192.168.0.104";
//WiFiServer server(80);

bool my_status;
long PM25;
long PM10;

//SH1106Wire display(0x3c, SDA, SCL);

void setup() { 
  Serial.begin(9600);
  delay(8000);
   Serial.println("Stopping autosend...");
  my_status = stop_autosend();
  Serial.print("Stop autosend status is ");
  Serial.println(my_status, BIN);
  Serial.println(" ");
  delay(50);
 
   
  Serial.println("Starting measurements...");
  my_status = start_measurement(); 
  Serial.print("Start measurement status is ");
  Serial.println(my_status, BIN);
  Serial.println(" ");
  delay(50000);
  
//  display.init();
 //display.flipScreenVertically();
 //display.setFont(ArialMT_Plain_24);
 
//  Serial.println("");
//  Serial.println("Server-------------------------------");
//  Serial.print("Configuring access point");
//  WiFi.begin(ssid, password);
//
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//    Serial.println("");
//    Serial.println("WiFi connected");
//
//    server.begin();
//    Serial.println("Server started");
//
//    Serial.print("Use this URL to connect: ");
//    Serial.print("http://");
//    Serial.print(WiFi.localIP());
//    Serial.println("/");
//    Serial.println("-------------------------------------"); 
}

void loop() {
  //display.clear();
  //display.setTextAlignment(TEXT_ALIGN_CENTER);
  my_status = read_measurement(); 
  Serial.print("Read measurement status is ");
  Serial.println(my_status, BIN);
  Serial.print("PM2.5 value is ");
  Serial.println(PM25, DEC);

  //display.drawString(10,10,"PM2.5:");
  //String stringOne =  String(PM25); 
  //display.drawString(64, 10,stringOne);
  
  Serial.print("PM10 value is ");
  Serial.println(PM10, DEC);

    //display.drawString(10,40,"PM10:");
  //String stringTwo =  String(PM10); 
  //display.drawString(64, 40,stringTwo);
//  delay(100);
//  WiFiClient client = server.available();
//  if (!client) {
//    return;
//  }
//  Serial.println("Server-------------------------------");
//  Serial.println("New client");
//  Serial.print("From client = ");
//  while(!client.available()){
//    delay(1);
//  }
//   String req = client.readStringUntil('\r');
//   Serial.println(req);
//   client.flush();
//
//      Serial.print("Server send = ");
//      client.print(String("GET ") + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
//
//   client.flush();
//   Serial.println("Client disonnected");
//   Serial.println("-------------------------------------");
//   Serial.println("");
   //display.display();
}


bool start_measurement(void)
{
  byte start_measurement[] = {0x68, 0x01, 0x01, 0x96 };
  Serial.write(start_measurement, sizeof(start_measurement));
  while(Serial.available() < 2);
  uint8_t read1 = Serial.read();
  uint8_t read2 = Serial.read();
  if ((read1 == 0xA5) && (read2 == 0xA5)){
    return 1;
  }
  else if ((read1 == 0x96) && (read2 == 0x96))
  {
    return 0;
  }
  else return 0;
}
 
bool stop_measurement(void)
{
  byte stop_measurement[] = {0x68, 0x01, 0x02, 0x95 };
  Serial.write(stop_measurement, sizeof(stop_measurement));
  while(Serial.available() < 2);
  uint8_t read1 = Serial.read();
  uint8_t read2 = Serial.read();
  if ((read1 == 0xA5) && (read2 == 0xA5)){
    return 1;
  }
  else if ((read1 == 0x96) && (read2 == 0x96))
  {
    return 0;
  }
  else return 0;
}
 
bool read_measurement (void)
{
  byte read_particle[] = {0x68, 0x01, 0x04, 0x93 };
  Serial.write(read_particle, sizeof(read_particle));
  while(Serial.available() < 1);
  byte HEAD = Serial.read();
  while(Serial.available() < 1);
  byte LEN = Serial.read();
  if ((HEAD == 0x96) && (LEN == 0x96)){
    Serial.println("NACK");
    return 0;
  }
  else if ((HEAD == 0x40) && (LEN == 0x05))
  {
    while(Serial.available() < 1);
    byte COMD = Serial.read();
    while(Serial.available() < 1);
    byte DF1 = Serial.read(); 
    while(Serial.available() < 1);
    byte DF2 = Serial.read();     
    while(Serial.available() < 1);
    byte DF3 = Serial.read();   
    while(Serial.available() < 1);
    byte DF4 = Serial.read();     
    while(Serial.available() < 1);
    byte CS = Serial.read();      
    if (((0x10000 - HEAD - LEN - COMD - DF1 - DF2 - DF3 - DF4) % 0XFF) != CS){
      Serial.println("Checksum fail");
      return 0;
    }
    else
    {
      PM25 = DF1 * 256 + DF2;
      PM10 = DF3 * 256 + DF4;
      return 1;
    }
  }
}
 
bool stop_autosend(void)
{ 
  byte stop_autosend[] = {0x68, 0x01, 0x20, 0x77 };
  Serial.write(stop_autosend, sizeof(stop_autosend));
  while(Serial.available() < 2);
  uint8_t read1 = Serial.read();
  uint8_t read2 = Serial.read();
  if ((read1 == 0xA5) && (read2 == 0xA5)){
    return 1;
  }
  else if ((read1 == 0x96) && (read2 == 0x96))
  {
    return 0;
  }
  else return 0;
}
 
bool start_autosend(void)
{
  byte start_autosend[] = {0x68, 0x01, 0x40, 0x57 };
  Serial.write(start_autosend, sizeof(start_autosend));
  while(Serial.available() < 2);
  uint8_t read1 = Serial.read();
  uint8_t read2 = Serial.read();
  if ((read1 == 0xA5) && (read2 == 0xA5)){
    return 1;
  }
  else if ((read1 == 0x96) && (read2 == 0x96))
  {
    return 0;
  }
  else return 0;
}
 
void flush_Serial(void){
  uint8_t inchar;
  uint8_t count = 0;
  bool is_timeout = 0;
  unsigned long timeout = millis() + 100000;
  Serial.println ("Waiting for the first autosend.");
  while(Serial.available() < 1){
    if (millis() > timeout){
      Serial.println("Timeout");
      break;
    }
  }
  if (Serial.available() > 0){
    Serial.println ("Flushing buffer...");
    while(count < 32){
      inchar = Serial.read();
      count++;
      delay(10);
      Serial.print(inchar, HEX);
    }
    Serial.println("");
  }
}
