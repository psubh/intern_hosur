
  #include <Wire.h>
  #include <ESP8266WiFi.h>

  #define       TWI_FREQ  400000L
  
  char*         ssid;
  char*         password;
  IPAddress     Server(192,168,4,1);
  WiFiClient    Client;

  void setup() 
  {
    Wire.begin();
    
    Wire.setClock(TWI_FREQ);
        
    Serial.begin(115200); 

    WiFi.mode(WIFI_STA);
    WiFi.begin("genisup_lab"); 

    Serial.println("!--- Connecting To " + WiFi.SSID() + " ---!");

    CheckConnectivity();
    
    Serial.println("Connected To      : " + String(WiFi.SSID()));
    Serial.println("Signal Strenght   : " + String(WiFi.RSSI()) + " dBm");
    Serial.print  ("Server IP Address : ");
    Serial.println(Server);
    Serial.print  ("Device IP Address : ");
    Serial.println(WiFi.localIP());
    
    Request();
  }

  
  void loop()
  {

  
  }


  void CheckConnectivity()
  {
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
      }
      Serial.println("connected");
    }


  void Request()
  {
    Client.stop();

    if(Client.connect(Server, 9001))
    {
      Serial.println    ( "CONNECTED");
      Client.println ("CONNECTED");
    }
  }
