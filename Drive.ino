// ===== MOTION & DRIVE MODULE =====

// دالة تحريك الروبوت للأمام بسرعات مختلفة للمحركين
void moveRobot(int sR, int sL) {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);

  analogWrite(enA, constrain(sR, 0, 255));
  analogWrite(enB, constrain(sL, 0, 255));
}

// دالة إيقاف الروبوت تماماً
void stopRobot() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

// دالة تحديد اتجاه الدوران ومستوى الطاقة (PWM) للمحركات
void driveTurn(TurnKind kind, int pwm) {
  if (kind == TURN_RIGHT_KIND || kind == TURN_UTURN_KIND) {
    digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  } else {
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
  }

  analogWrite(enA, pwm);
  analogWrite(enB, pwm);
}
