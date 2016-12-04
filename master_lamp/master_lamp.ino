#include <SoftwareSerial.h>

#define BT_RX 12
#define BT_TX 13
#define POT A0
#define PHOTO_INTER 8
#define MOTER_F 9
#define MOTER_B 10
#define s0 3
#define s1 4
#define s2 5
#define s3 6
#define out 2
#define COLOR_LED 11

SoftwareSerial BTSerial(BT_RX, BT_TX);
////////////////////color sensor////////////////////
int flag = 0;
byte counter = 0;
byte countR = 0, countG = 0, countB = 0;

int bt_baud = 9600;
int pot_val;
int moter_dir;
int mode;
int state_indi;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(bt_baud);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(MOTER_B, OUTPUT);
  pinMode(MOTER_F, OUTPUT);
  pinMode(PHOTO_INTER, INPUT);
  pinMode(COLOR_LED, OUTPUT);
  digitalWrite(COLOR_LED, LOW);
  TCS(); //timer2 for color sensor
  InitMoter();
}

//타이머들 우선순위랑 pwm 겹치는거 고려해야함 delay,millis -> timer0

void loop() {
  LedState(1);
  if () { //종이가 올라왔다는 조건
    LedState(4);
  }
  if () { //색을 감지했다는 조건
    ColorPub();
  }

  int wind = digitalRead(PHOTO_INTER);
  while (wind == 1) { //바람을 감지
    delay(500);
    LedState(0);
    MoterCtrl(2000);
    wind = 0;
  }

}
