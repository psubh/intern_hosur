#define USE_AVG
const int sharpLEDPin = 7; 
const int sharpVoPin = A5;

#ifdef USE_AVG
#define N 100
static unsigned long VoRawTotal = 0;
static int VoRawCount = 0;
#endif
 
static float Voc = 0.6;

const float K = 0.5;
  
void printValue(String text, unsigned int value, bool isLast = false) {
  Serial.print(text);
  Serial.print("=");
  Serial.print(value);
  if (!isLast) {
    Serial.print("\n");
  }
}
void printFValue(String text, float value, String units, bool isLast = false) {
  Serial.print(text);
  Serial.print("=");
  Serial.print(value);
  Serial.print(units);
  if (!isLast) {
    Serial.print("\n");
  }
}
void setup() {
  pinMode(sharpLEDPin, OUTPUT);
  
  Serial.begin(9600);
  
  delay(2000);
  Serial.println("");
}
void loop() {  
  digitalWrite(sharpLEDPin, LOW);

  delayMicroseconds(280);

  int VoRaw = analogRead(sharpVoPin);
  digitalWrite(sharpLEDPin, HIGH);
  delayMicroseconds(9620);
  
  #ifdef PRINT_RAW_DATA
  printValue("VoRaw", VoRaw, true);
  Serial.println("");
  #endif
  
  float Vo = VoRaw;
  #ifdef USE_AVG
  VoRawTotal += VoRaw;
  VoRawCount++;
  if ( VoRawCount >= N ) {
    Vo = 1.0 * VoRawTotal / N;
    VoRawCount = 0;
    VoRawTotal = 0;
  } else {
    return;
  }
  #endif
  Vo = Vo / 1024.0 * 5.0;
  printFValue("Vo", Vo*1000.0, "mV");
  float dV = Vo - Voc;
  if ( dV < 0 ) {
    dV = 0;
    Voc = Vo;
  }
  float dustDensity = dV / K * 100.0;
  printFValue("DustDensity", dustDensity, "ug/m3", true);
  Serial.println("");
  
}
