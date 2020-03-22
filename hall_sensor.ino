const int switchpin=4;
int switchstate;
int sensorpin=2;
int mainsupply=8;
int buzzer=9;
void setup() {
  Serial.begin(9600);
  pinMode(switchpin,INPUT_PULLUP);
  pinMode(sensorpin,INPUT);
  pinMode(mainsupply,OUTPUT);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  switchstate=digitalRead(switchpin);
  if(switchstate==LOW)
  {
    int sensorvalue=digitalRead(sensorpin);
    if(sensorvalue==LOW)
    {
     digitalWrite(mainsupply,HIGH);
     delay(10000);
     digitalWrite(buzzer,HIGH);
     delay(1000);
     digitalWrite(buzzer,LOW);
    }
    if(sensorvalue==HIGH)
    {
     digitalWrite(mainsupply,LOW);
      
    }
  }

}
