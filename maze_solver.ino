// ===== MAIN CONFIGURATION & STATE MACHINE =====

// ===== SENSORS PINS =====
const int trigF = 2;  const int echoF = 3;
const int trigR = 4;  const int echoR = 13;
const int trigL = 6;  const int echoL = 7;

// ===== MOTOR DRIVER PINS =====
const int enA = 9;   const int in1 = 8;   const int in2 = 10;
const int enB = 5;   const int in3 = 11;  const int in4 = 12;

// ===== SPEED / CONTROL TUNING =====
int baseSpeed   = 145;
int searchSpeed = 125;
int targetDist = 7;
float Kp = 30.0;
float Kd = 15.0;

int frontLimit = 5;
int openThreshold = 22;
int wallPresentDist = 18;
int wallLostDist    = 24;

// ===== TURN TIMINGS =====
const unsigned long TURN_KICK_MS   = 90;
const unsigned long RIGHT_TURN_MS   = 600;
const unsigned long LEFT_TURN_MS    = 600;
const unsigned long UTURN_MS        = 1220;
const int TURN_PWM_FAST = 255;
const int TURN_PWM_SLOW = 190;

// ===== STATE MANAGEMENT =====
enum Mode { MODE_FOLLOW, MODE_TURN };
enum TurnKind { TURN_NONE, TURN_RIGHT_KIND, TURN_LEFT_KIND, TURN_UTURN_KIND };

Mode mode = MODE_FOLLOW;
TurnKind currentTurn = TURN_NONE;

unsigned long turnStart = 0;
unsigned long turnDuration = 0;
bool rightWallSeen = false;
int lastError = 0;
int rightOpenCounter = 0;

void setup() {
  Serial.begin(115200);

  pinMode(trigF, OUTPUT); pinMode(echoF, INPUT);
  pinMode(trigR, OUTPUT); pinMode(echoR, INPUT);
  pinMode(trigL, OUTPUT); pinMode(echoL, INPUT);

  pinMode(enA, OUTPUT); pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);

  stopRobot();
}

void loop() {
  if (mode == MODE_TURN) {
    updateTurn();
    return;
  }

  int f = getFiltered(trigF, echoF);
  int r = getFiltered(trigR, echoR);

  if (r <= wallPresentDist) rightWallSeen = true;
  else if (r >= wallLostDist) rightWallSeen = false;

  if (r >= openThreshold) {
    rightOpenCounter++;
  } else {
    rightOpenCounter = 0;
  }

  Serial.print("F:"); Serial.print(f);
  Serial.print(" R:"); Serial.print(r);
  Serial.print(" Counter:"); Serial.println(rightOpenCounter);

  if (f <= frontLimit) {
    stopRobot();
    int l = getFiltered(trigL, echoL);

    if (r >= openThreshold && r >= l) {
      startTurn(TURN_RIGHT_KIND, RIGHT_TURN_MS);
      return;
    }
    if (l >= openThreshold) {
      startTurn(TURN_LEFT_KIND, LEFT_TURN_MS);
      return;
    }
    startTurn(TURN_UTURN_KIND, UTURN_MS);
    return;
  }

  if (rightWallSeen && rightOpenCounter >= 2 && f < 15 && f > frontLimit) {
    startTurn(TURN_RIGHT_KIND, RIGHT_TURN_MS);
    return;
  }

  if (rightWallSeen) {
    followRightWall(r);
  } else {
    moveRobot(searchSpeed, searchSpeed);
  }
}
