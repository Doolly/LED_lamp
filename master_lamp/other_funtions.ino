void InitMoter(void) {
  digitalWrite(MOTER_B, LOW);
  digitalWrite(MOTER_F, LOW);
}

void MoterCtrl() {
  int pot_val = analogRead(POT);
  int SPEED = map(pot_val, 0, 1023, 16, 255 );
  int delay_time = 280000 / SPEED;
  if (delay_time > 20000) {
    delay_time = 20000;
  }
  Serial.print("pot_val = " + String(pot_val) + "\n");
  Serial.print("speed = " + String(SPEED) + "\n");
  analogWrite(MOTER_F, SPEED);
  analogWrite(MOTER_B, 0);
  delay(delay_time * 6);
  analogWrite(MOTER_F, 0);
  analogWrite(MOTER_B, 0);
  delay(20000);
  analogWrite(MOTER_F, 0);
  analogWrite(MOTER_B, SPEED);
  delay(delay_time * 5.2);
  lamp_action = 0;
  BTSerial.print(lamp_action);
  BTSerial.print("f,");
  delay(150);
}

void ColorPub(int R, int G, int B, int action) {
  BTSerial.print(R);
  BTSerial.print("r,");
  delay(150);
  BTSerial.print(G);
  BTSerial.print("g,");
  delay(150);
  BTSerial.print(B);
  BTSerial.print("b,");
  delay(150);
  BTSerial.print(action);
  BTSerial.print("f,");
  delay(150);
}

void LedState(int mode) {
  //mode    0,   1,   2,   3,   4
  //on:off 0:1  1:4, 1:1, 4:1, 1:0

  if (state_indi < (110 - mode * 30)) {
    digitalWrite(COLOR_LED, LOW);
  }
  else {
    digitalWrite(COLOR_LED, HIGH);
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
  Serial.print(countB, DEC); Serial.print(", ");
  Serial.println(lamp_action);
}

