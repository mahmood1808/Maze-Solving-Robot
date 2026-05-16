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
## Hardware Components & Tools

| Component | Model / Specification | Quantity | Purpose |
| :--- | :--- | :--- | :--- |
| **Microcontroller** | Arduino Uno (or Nano/ESP32) | 1 | Main processing unit |
| **Ultrasonic Sensors** | HC-SR04 | 3 | Distance measurement (Front, Right, Left) |
| **Motor Driver** | L298N Dual H-Bridge | 1 | Controls DC motors speed and direction |
| **DC Gear Motors** | 5V-9V Yellow Smart Car Motors | 2 | Robot locomotion |
| **Power Source** | 2x 18650 Li-ion Batteries (7.4V) | 1 | High-current power supply |
| **Chassis** | 2-Wheel Acrylic/3D Printed Chassis | 1 | Robot body structure |
| **Caster Wheel** | Mini Omnidirectional Wheel | 1 | Balance and smooth steering |
| **Breadboard & Wires** | Mini Breadboard & Jumper Wires | 1 | Circuit prototyping and connections |
---
## Circuit Schematic & Wiring Guide

### 1. Ultrasonic Sensors Connections
| Sensor | Arduino Pin (Trig) | Arduino Pin (Echo) | VCC / GND |
| :--- | :--- | :--- | :--- |
| **Front Sensor** | `Pin 2` | `Pin 3` | 5V / GND |
| **Right Sensor** | `Pin 4` | `Pin 13` | 5V / GND |
| **Left Sensor** | `Pin 6` | `Pin 7` | 5V / GND |

### 2. L298N Motor Driver Connections
| Driver Pin | Arduino Pin | Function |
| :--- | :--- | :--- |
| **enA** | `Pin 9` (PWM) | Right Motor Speed Control |
| **in1** | `Pin 8` | Right Motor Direction 1 |
| **in2** | `Pin 10` | Right Motor Direction 2 |
| **enB** | `Pin 5` (PWM) | Left Motor Speed Control |
| **in3** | `Pin 11` | Left Motor Direction 1 |
| **in4** | `Pin 12` | Left Motor Direction 2 |

⚠️ *Important Note on Power:* Connect the *GND* of the Arduino to the *GND* of the L298N motor driver and the battery pack (Common Ground) to avoid erratic motor behavior or sensor reset loops.

-----

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
2. Wire up the components according to the Hardware Mapping table above.
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
