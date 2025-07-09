# Basic Electronics and Arduino Curriculum

Here is a structured lesson plan for learning basic electronics with hands-on projects using Tinkercad.

## Lesson 1: Your First Circuit - Lighting an LED

*   **Concept:** Introduce the fundamental components of a circuit: a power source, a path, a load, and the concepts of Voltage, Current, and Resistance (Ohm's Law).
*   **Components:**
    *   9V Battery
    *   LED (Light Emitting Diode)
    *   330Ω Resistor (to protect the LED)
*   **Tinkercad Circuit Design:**
    1.  Drag a 9V battery, an LED, and a resistor onto the workspace.
    2.  Connect the positive terminal of the battery to one leg of the resistor.
    3.  Connect the other leg of the resistor to the **anode** (the longer, bent leg) of the LED.
    4.  Connect the **cathode** (the shorter, straight leg) of the LED to the negative terminal of the battery.
    5.  Click "Start Simulation". The LED should light up.

## Lesson 2: Using a Switch

*   **Concept:** Introduce the idea of controlling a circuit with a switch. Explain how a switch opens and closes a circuit.
*   **Components:**
    *   9V Battery
    *   LED
    *   330Ω Resistor
    *   Pushbutton or Slide Switch
*   **Tinkercad Circuit Design:**
    1.  Build the same circuit as in Lesson 1.
    2.  Insert a pushbutton in the path between the resistor and the LED.
    3.  Click "Start Simulation". The LED will only light up when you press and hold the pushbutton.

## Lesson 3: Variable Resistance with a Potentiometer

*   **Concept:** Introduce analog control. Explain how a potentiometer works as a variable resistor to control the amount of current flowing to the LED, thus changing its brightness.
*   **Components:**
    *   9V Battery
    *   LED
    *   Potentiometer (e.g., 10kΩ)
    *   220Ω Resistor (for basic protection)
*   **Tinkercad Circuit Design:**
    1.  Connect the positive terminal of the battery to **Terminal 1** of the potentiometer.
    2.  Connect the **Wiper** (the middle terminal) of the potentiometer to the anode of the LED (through the 220Ω resistor).
    3.  Connect the cathode of the LED to the negative terminal of the battery.
    4.  Connect **Terminal 2** of the potentiometer also to the negative terminal.
    5.  Click "Start Simulation". As you turn the potentiometer knob, the LED's brightness will change.
