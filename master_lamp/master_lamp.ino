#include <SoftwareSerial.h>

#define BT_RX 6
#define BT_TX 6
#define s0 3
#define s1 4
#define s2 5
#define s3 6
#define out 2

SoftwareSerial BTSerial(BT_RX, BT_TX);
////////////////////color sensor////////////////////
int flag = 0;
byte counter = 0;
byte countR = 0, countG = 0, countB = 0;


void setup() {
  Serial.begin(115200);
  BTSerial.begin(9600);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  TCS();
}

void loop() {
  
}
