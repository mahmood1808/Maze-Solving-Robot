// ===== SENSORS & SIGNAL PROCESSING MODULE =====

// دالة قراءة الحساس الأساسية لحساب المسافة بالـ cm
int getDistance(int trig, int echoPin) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 25000UL);
  if (duration == 0) return 100;

  int dist = (int)(duration * 0.034 / 2.0);

  if (dist <= 0 || dist > 400) return 100;
  return dist;
}

// دالة الفلترة: تأخذ 3 قراءات وترتبهم وتختار القراءة الوسطى (Median)
int getFiltered(int trig, int echoPin) {
  int a = getDistance(trig, echoPin);
  delayMicroseconds(700);
  int b = getDistance(trig, echoPin);
  delayMicroseconds(700);
  int c = getDistance(trig, echoPin);

  if (a > b) swapInt(a, b);
  if (b > c) swapInt(b, c);
  if (a > b) swapInt(a, b);

  return b;
}

// دالة مساعدة لتبديل القيم أثناء الترتيب
void swapInt(int &x, int &y) {
  int t = x;
  x = y;
  y = t;
}
