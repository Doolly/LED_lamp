void TCS() {
  flag = 0;
  digitalWrite(s1, HIGH);
  digitalWrite(s0, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  attachInterrupt(0, ISR_INTO, CHANGE);
  timer2_init();
}

void ISR_INTO() {
  counter++;
}

void timer2_init(void) {
  TCCR2A = 0x00;
  TCCR2B = 0x07; //the clock frequency source 1024 points
  TCNT2 = 100;   //10 ms overflow again
  TIMSK2 = 0x01; //allow interrupt
}

ISR(TIMER2_OVF_vect) { //the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
  TCNT2 = 100;
  flag++;
  if (flag == 1) {
    countR = counter;
   // Serial.print(countR, DEC); Serial.print(", ");
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
  }
  else if (flag == 2) {
    countG = counter;
   // Serial.print(countG, DEC); Serial.print(", ");
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
  }
  else if (flag == 3) {
    countB = counter;
   // Serial.println(countB, DEC);  
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
  }
  else if (flag == 4) {
    flag = 0;
  }
  counter = 0; 
}
