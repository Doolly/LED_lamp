#include <SoftwareSerial.h>

#define BT_RX 12
#define BT_TX 13
#define POT A0
#define PHOTO_INTER 3
#define MOTER_F 9
#define MOTER_B 10
#define s0 8
#define s1 4
#define s2 11
#define s3 6
#define out 2
#define COLOR_LED 5

SoftwareSerial BTSerial(BT_RX, BT_TX);
////////////////////color sensor////////////////////
int flag = 0;
int counter = 0;
int countR = 0, countG = 0, countB = 0;

int bt_baud = 9600;
int pot_val;
int moter_dir;
int mode;
int state_indi;
int lamp_action;
volatile int wind = 1;
unsigned long current_time;
unsigned long previous_time;
const long detecting_time = 3000;

void TCS();
void WindDetect();
void InitMoter(void);
void LedState(int mode);
void ColorPub(int R, int G, int B, int action);
void MoterCtrl();
void SerialPrint();

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
  attachInterrupt(1, WindDetect, FALLING);
  InitMoter();
}

void loop() {
  LedState(1);
  InitMoter();

  Serial.print("waiting for color     ");
  SerialPrint();
  lamp_action = 0;
//  BTSerial.print(lamp_action);
//  BTSerial.print("f,");

  if (countR + countG + countB > 130) { //종이가 올라왔다는 조건
    LedState(4);
    Serial.println("color detected ");

    current_time = millis();
    previous_time = current_time;
    while (current_time - previous_time < detecting_time) {
      current_time = millis();
    }
    lamp_action = 1;
    ColorPub(countR, countG, countB, lamp_action);
    ColorPub(countR, countG, countB, lamp_action);
    Serial.println("color publish through BT  ");
    Serial.println("  ");
    SerialPrint();

    while (wind == 0) { //바람을 감지
      Serial.println("~~~~~~~~~wind detected~~~~~~~~~");
      delay(500);
      LedState(0);
      MoterCtrl();
      wind = 1;
    }
  }

}
