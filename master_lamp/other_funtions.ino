void InitMoter(void) {
  digitalWrite(MOTER_B, LOW);
  digitalWrite(MOTER_F, LOW);
}

void MoterCtrl() {
  int pot_val = analogRead(POT);
  int SPEED = map(pot_val, 0, 1023, 60, 255 );
  int delay_time = 280000 / SPEED;
  if (delay_time > 20000) {
    delay_time = 20000;
  }
  Serial.print("pot_val = " + String(pot_val) + "\n");
  Serial.print("speed = " + String(SPEED) + "\n");
  analogWrite(MOTER_F, SPEED);
  analogWrite(MOTER_B, 0);
  delay(delay_time * 7);
  analogWrite(MOTER_F, 80);
  analogWrite(MOTER_B, 0);
  delay(19500);
  for (int a = 0; a < 20; a++) {
    delay(1);
    ColorPub('x', 0, 0, 0);
  }
  delay(500);
  analogWrite(MOTER_F, 0);
  analogWrite(MOTER_B, SPEED - 80);
  delay(delay_time * 7);
  analogWrite(MOTER_F, 80);
  analogWrite(MOTER_B, 0);
  delay(150);
}

void ColorPub(char _switch, int R, int G, int B) {
  if (R < 100)
    R = 0;
  if (R > 255)
    R = 255;
  if (G < 90)
    G = 0;
  if (G > 255)
    G = 255;
  if (B < 100)
    B = 0;
  if (B > 255)
    B = 255;

  BTSerial.print(String("<") + _switch + "," + String(R) + "," + String(G) + "," + String(B)  + String(">"));
}

void LedState(int mode) {
  //mode    0,   1,   2,   3,   4
  //on:off 0:1  1:4, 1:1, 4:1, 1:0

  if (state_indi < (110 - mode * 30)) {
    analogWrite(COLOR_LED, 0);
  }
  else {
    analogWrite(COLOR_LED, 200);
  }
  state_indi += 1;
  if (state_indi > 100) {
    state_indi = 0;
  }
}

void WindDetect () {
  wind = 0;
}


void SerialPrint() {
  Serial.print(countR, DEC); Serial.print(", ");
  Serial.print(countG, DEC); Serial.print(", ");
  Serial.println(countB, DEC);
}

