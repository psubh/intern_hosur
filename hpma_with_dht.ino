//Project Maddie
//By Jonathan M. Self & GASP Birmingham, AL

#include <SoftwareSerial.h>
#include <DHT.h>
#include <hpma115S0.h>

SoftwareSerial portOne(2, 3);        //This is the bluetooth module -JS
SoftwareSerial portTwo(6, 7);        //This is the Honeywell Particulate Matter Sensor

#define DHTPIN 9
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

HPMA115S0 hpma115S0(portTwo);

int pin = 8;
int humi, cel, fah;

void setup() {
  Serial.begin(9600);
  portOne.begin(9600);
  portTwo.begin(9600);
  pinMode(8,INPUT);
  hpma115S0.Init();
  hpma115S0.EnableAutoSend();
  //hpma115S0.StartParticleMeasurement();
}

void loop() {
  unsigned int pm2_5, pm10;
  humi = dht.readHumidity();
  cel = dht.readTemperature();
  fah = ((cel * 9)/5) + 32;
  {
    Serial.print("PM 2.5: " + String(pm2_5) + " ug/m3" );
    Serial.print("PM 10: " + String(pm10) + " ug/m3" );
    Serial.print(fah);
    Serial.print(F("F "));
    Serial.print(cel);
    Serial.print(F("C "));
    Serial.print(humi);
    Serial.print(F("RH "));
    Serial.println("\n");
    
    portOne.print(pm2_5);
    portOne.println(F(";InsertSensorPackageName;HPMA115S0;Particulate Matter;PM;2.5 ug/m3;ug/m3;0;2500;5000;7500;10000\n")); //Likely need to change the bounds of our measurements. -Jon Self
    portOne.print(pm10);
    portOne.println(F(";InsertSensorPackageName;HPMA115S0;Particulate Matter;PM;2.5 ug/m3;ug/m3;0;2500;5000;7500;10000\n")); //Likely need to change the bounds of our measurements. -Jon Self
    portOne.print(fah);
    portOne.println(F(";InsertSensorPackageName;DHT22-F;Temperature;F;degrees Fahrenheit;F;0;25;50;75;100\n"));
    portOne.print(cel);
    portOne.print(F(";InsertSensorPackageName;DHT22-C;Temperature;C;degrees Celsius;C;0;10;20;30;40\n"));
    portOne.print(humi);
    portOne.println(F(";InsertSensorPackageName;DHT22-RH;Humidity;RH;percent;%;0;25;50;75;100\n"));
  }
}
