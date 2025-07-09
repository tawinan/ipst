# Basic Electronics and Arduino Curriculum

Here is a structured lesson plan for learning basic electronics with hands-on projects using Tinkercad.

## Lesson 1: Your First Circuit - Lighting an LED

*   **Concept:** Introduce the fundamental components of a circuit: a power source, a path, a load, and the concepts of Voltage, Current, and Resistance (Ohm's Law).
*   **Components:**
    *   Breadboard
    *   9V Battery
    *   LED (Light Emitting Diode)
    *   330Ω Resistor (to protect the LED)
*   **Tinkercad Breadboard Instructions:**
    1.  Drag a breadboard and a 9V battery onto the workspace.
    2.  Connect the red wire (+) from the battery to the red power rail (+) on the breadboard.
    3.  Connect the black wire (-) from the battery to the blue power rail (-) on the breadboard.
    4.  Place an LED on the breadboard. Note the anode (+) and cathode (-).
    5.  Place a 330Ω resistor on the breadboard. Connect one leg to the same row as the LED's anode.
    6.  Use a wire to connect the other leg of the resistor to the red power rail (+).
    7.  Use a wire to connect the LED's cathode to the blue power rail (-).
    8.  Click "Start Simulation". The LED should light up.

## Lesson 2: Using a Switch

*   **Concept:** Introduce the idea of controlling a circuit with a switch. Explain how a switch opens and closes a circuit.
*   **Components:**
    *   Components from Lesson 1
    *   Pushbutton
*   **Tinkercad Breadboard Instructions:**
    1.  Start with the circuit from Lesson 1.
    2.  Place a pushbutton on the breadboard, making sure it straddles the center gap.
    3.  Remove the wire connecting the resistor to the power rail.
    4.  Connect a wire from the red power rail (+) to one of the pushbutton's legs.
    5.  Connect the resistor's free leg to the pushbutton leg directly across the gap.
    6.  Click "Start Simulation". The LED will only light up when you press the button.

## Lesson 3: Variable Resistance with a Potentiometer

*   **Concept:** Introduce analog control. Explain how a potentiometer works as a variable resistor to control the amount of current flowing to the LED, thus changing its brightness.
*   **Components:**
    *   Components from Lesson 1 (use a 220Ω resistor)
    *   Potentiometer (10kΩ)
*   **Tinkercad Breadboard Instructions:**
    1.  Start with the basic LED circuit from Lesson 1 (using a 220Ω resistor).
    2.  Place a potentiometer on the breadboard.
    3.  Connect a wire from the red power rail (+) to Terminal 1 of the potentiometer.
    4.  Connect a wire from the blue power rail (-) to Terminal 2 of the potentiometer.
    5.  Remove the wire connecting the resistor to the power rail.
    6.  Connect the resistor's free leg to the potentiometer's center pin (the Wiper).
    7.  Click "Start Simulation". As you turn the potentiometer, the LED's brightness will change.
