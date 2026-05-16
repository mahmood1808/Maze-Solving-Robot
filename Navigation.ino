// ===== NAVIGATION & CONTROL LOOP MODULE =====

// تطبيق خوارزمية PD للتحكم في ثبات الروبوت بجانب الحائط الأيمن
void followRightWall(int r) {
  int error = targetDist - r;
  int dError = error - lastError;

  float adjust = (Kp * error) + (Kd * dError);

  int rightSpeed = (int)(baseSpeed + adjust);
  int leftSpeed  = (int)(baseSpeed - adjust);

  rightSpeed = constrain(rightSpeed, 0, 255);
  leftSpeed  = constrain(leftSpeed, 0, 255);

  moveRobot(rightSpeed, leftSpeed);

  lastError = error;
}

// دالة بدء الدوران وتحديد نوعه والوقت المطلوب
void startTurn(TurnKind kind, unsigned long duration) {
  currentTurn = kind;
  turnDuration = duration;
  turnStart = millis();
  mode = MODE_TURN;

  driveTurn(kind, TURN_PWM_FAST);
}

// دالة تحديث حالة الدوران بناءً على الوقت المنقضي (Non-blocking)
void updateTurn() {
  unsigned long elapsed = millis() - turnStart;

  if (elapsed >= turnDuration) {
    stopRobot();
    mode = MODE_FOLLOW;
    currentTurn = TURN_NONE;
    lastError = 0;
    rightOpenCounter = 0;
    return;
  }

  int pwm = (elapsed < TURN_KICK_MS) ? TURN_PWM_FAST : TURN_PWM_SLOW;
  driveTurn(currentTurn, pwm);
}
