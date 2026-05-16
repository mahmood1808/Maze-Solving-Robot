# Autonomous Maze-Solving Robot (Micromouse) 

An advanced Arduino-based autonomous robot designed to navigate and solve complex mazes efficiently. The robot utilizes a combination of **Ultrasonic sensors**, **PD control loops** for wall-following stability, and a **non-blocking state machine** to handle precise timed turns and intersection logic.

---

##  Key Technical Features

* **PD Feedback Loop (`Proportional-Derivative`):** Implements smooth parallel wall-following, continuously calculating errors and dynamic adjustments via $Kp$ and $Kd$ parameters to eliminate drifting.
* **Noise-Resilient Sensor Filtering:** Features a real-time **Median Filter (3-sample window)** to eliminate ultrasonic noise and outliers, ensuring highly accurate distance reading.
* **Non-Blocking Architecture:** Uses an asynchronous state-machine approach based on `millis()` rather than disruptive `delay()` functions, allowing concurrent sensor processing during movement execution.
* **Dynamic Turn Kick:** Incorporates a high-power initial PWM burst (`TURN_KICK_MS`) to overcome static friction, followed by a controlled deceleration for accurate 90° and 180° turns.
* **Intersection Debouncing:** Employs a continuous sampling counter (`rightOpenCounter`) to confirm true openings, avoiding false-positive triggers caused by slight wall irregularities.

---

##  Hardware Architecture

### Pin Configuration Mapping

| Module Component | Arduino Pin | Description |
| :--- | :---: | :--- |
| **Front Sensor (`Trig` / `Echo`)** | `D2` / `D3` | Detects walls directly ahead to trigger intersection turns. |
| **Right Sensor (`Trig` / `Echo`)** | `D4` / `D13` | Primary wall-following reference sensor. |
| **Left Sensor (`Trig` / `Echo`)** | `D6` / `D7` | Verification sensor for dead-ends and left turns. |
| **Motor Driver `IN1` / `IN2`** | `D8` / `D10` | H-Bridge Control: Right Motor Direction. |
| **Motor Driver `IN3` / `IN4`** | `D11` / `D12`| H-Bridge Control: Left Motor Direction. |
| **Motor Driver `enA` / `enB`** | `D9` / `D5` | **PWM Enabled Pins** for variable speed adjustments. |

---

##  System Logic & Control Flow

The codebase divides the robot's lifecycle into two primary runtime states managed inside `loop()`:

### 1. Wall Following Mode (`MODE_FOLLOW`)
The robot constantly attempts to follow the right wall at a fixed target distance ($7\text{ cm}$). The error is fed through the standard PD formula:

$$\text{Adjust} = (K_p \times \text{error}) + (K_d \times \Delta\text{error})$$

The adjustment is then mixed into the baseline speed to perform smooth differential steering.

### 2. Turning State Machine (`MODE_TURN`)
When an intersection or dead-end is encountered, the robot interrupts the loop safely to initiate a turn sequence:
* **Initial Burst:** `TURN_PWM_FAST (255)` for a quick response.
* **Sustained Rotation:** Transitions to `TURN_PWM_SLOW (190)` for structural stability.
* **Termination:** Once the target duration (`millis()`) is reached, it resets the error bounds and returns to tracking mode seamlessly.

---

##  Software Architecture

The code is highly modularized for easy testing and debugging:
* `getFiltered()`: Handles the 3-sample signal acquisition and median sorting mechanism.
* `followRightWall()`: Translates distance deviations into complementary differential PWM values.
* `driveTurn()`: Manipulates H-Bridge logic vectors to spin the chassis cleanly on its center axis.

---

##  How to Flash & Run

1. Open the project inside **PlatformIO** or **Visual Studio Code** (with the Arduino Extension).
2. Wire up the components according to the [Hardware Mapping](#-hardware-architecture) table above.
3. Make sure to choose your target board (e.g., **Arduino Uno / Mega**).
4. Compile and upload! Open your Serial Monitor at `115200 baud` to view real-time filtering data and path confirmation ticks.
5. ---

## NOVA Team
* Mostafa Mohamed
* Mahmood Samy
* Moamen Mohamed
* Mariam Mohamed
* Menna Ramadan
* Karim Habib
* Ahmed Mohamed
* Youssef Omar
* Malak Mourad

---
<p align="center">
  <b>Mansoura National University | AI Engineering</b>
</p>
