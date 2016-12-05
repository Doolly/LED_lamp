void InitMoter(void) {
  digitalWrite(MOTER_B, LOW);
  digitalWrite(MOTER_F, LOW);
}

void MoterCtrl(int distance) {
  int pot_val = analogRead(POT);
  int SPEED = map(pot_val, 0, 1023, 125, 255 );
  Serial.print("pot_val = " + String(pot_val) + "\n");
  analogWrite(MOTER_F, SPEED);
  analogWrite(MOTER_B, 0);
  delay(distance);
  analogWrite(MOTER_F, 0);
  analogWrite(MOTER_B, 0);
  delay(30000);
  analogWrite(MOTER_F, 0);
  analogWrite(MOTER_B, SPEED);
  delay(distance);
}

void ColorPub() {
  BTSerial.print(countR);
  BTSerial.print("r,");
  delay(150);
  BTSerial.print(countG);
  BTSerial.print("g,");
  delay(150);
  BTSerial.print(countB);
  BTSerial.print("b,");
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

void WindDetect (){
  wind = 0;
  
  }


