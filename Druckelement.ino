#include <SPI.h>
int CE = 2;
int RCK = 3;
int SRCLR = 4;
int R = 5;
int T = 6;
int S = 7;
//Ausgabe:  |---------2-----------|----------1------------|------------0----------|
//Bit:      23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
//Contact    X  X 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18  M  M  M  M

uint8_t ausgabe[3]={0,0,0};
int digits = 12;
uint8_t zeile[digits][3]={0,0,0};

void setup() {
  Serial.begin(9600);

  pinMode(CE, OUTPUT);
  pinMode(RCK, OUTPUT);
  pinMode(SRCLR, OUTPUT);

  digitalWrite(CE, HIGH);
  digitalWrite(SRCLR, LOW);

  pinMode(R, INPUT_PULLUP);
  pinMode(T, INPUT_PULLUP);
  pinMode(S, INPUT_PULLUP);
  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
}
void waitFor(int sig){
  while(digitalRead(sig));
}
void motorAn(){
  ausgabe[0]|= B00001111;
  transferAusgabe();
}

void motorAus(){
  ausgabe[0]&= B11110000;
  transferAusgabe();
}
void transferAusgabe() {
    SPI.transfer(ausgabe[2]);
    SPI.transfer(ausgabe[1]);
    SPI.transfer(ausgabe[0]);
    store();
}
void store(){
  digitalWrite(RCK, HIGH);
  delay(1);
  digitalWrite(RCK, LOW);
}
void printZeile(String l){

  
}
// the loop function runs over and over again forever
void loop() {
  delay(1000);
  digitalWrite(SRCLR, HIGH);
  digitalWrite(CE, LOW);
  motorAn();
  delay(500);
  motorAus();
  digitalWrite(CE, HIGH);
  waitFor(S);
  Serial.println("");
  Serial.print("R:");
  Serial.print(digitalRead(R));
  Serial.print(" T:");
  Serial.print(digitalRead(T));
  Serial.print(" S:");
  Serial.println(digitalRead(S));

  //printAusgabe();
  delay(100000000);              // wait for a second
}


