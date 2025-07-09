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

## Lesson 4: Intro to Arduino & Your First Program: "Blink"

*   **Concept:** Introduce the Arduino microcontroller. Explain the difference between a simple circuit and a programmable one. Cover the basic structure of an Arduino program (`setup()` and `loop()`) and the "Hello, World!" of hardware: blinking an LED with code.
*   **Components:**
    *   Arduino UNO
    *   Breadboard
    *   LED
    *   220Ω Resistor
*   **Tinkercad Breadboard Instructions:**
    1.  Drag an Arduino UNO and a breadboard into the workspace.
    2.  Connect the **5V** pin on the Arduino to the red power rail (+) on the breadboard.
    3.  Connect the **GND** pin on the Arduino to the blue ground rail (-) on the breadboard.
    4.  Place an LED on the breadboard. Connect its cathode (-) to the blue ground rail.
    5.  Connect a 220Ω resistor from the LED's anode (+) to a free row on the breadboard.
    6.  Use a wire to connect that resistor row to **digital pin 13** on the Arduino.
*   **Code:** In Tinkercad, click the "Code" button, select "Text", and enter the following:
    ```cpp
    void setup() {
      // Set pin 13 to be an output
      pinMode(13, OUTPUT);
    }

    void loop() {
      // Turn the LED on (HIGH is the voltage level)
      digitalWrite(13, HIGH);
      delay(1000); // Wait for 1000 milliseconds (1 second)

      // Turn the LED off by making the voltage LOW
      digitalWrite(13, LOW);
      delay(1000); // Wait for 1 second
    }
    ```

## Lesson 5: Reading Input - The Pushbutton

*   **Concept:** Teach how to read a digital input (a button press). Introduce `digitalRead()` and the importance of a **pull-down resistor** to ensure the input pin reads LOW when the button isn't pressed.
*   **Components:**
    *   Circuit from Lesson 4
    *   Pushbutton
    *   10kΩ Resistor (the pull-down resistor)
*   **Tinkercad Breadboard Instructions:**
    1.  Start with the "Blink" circuit from Lesson 4.
    2.  Place a pushbutton on the breadboard (straddling the center gap).
    3.  Connect one leg of the button to the red power rail (+5V).
    4.  Connect the leg directly across the gap to **digital pin 2** on the Arduino.
    5.  Place the 10kΩ resistor from that same leg (the one connected to pin 2) to the blue ground rail (-). This "pulls" the pin to a LOW state.
*   **Code:**
    ```cpp
    const int buttonPin = 2;
    const int ledPin = 13;
    int buttonState = 0; // variable for reading the pushbutton status

    void setup() {
      pinMode(ledPin, OUTPUT);
      pinMode(buttonPin, INPUT);
    }

    void loop() {
      // read the state of the pushbutton value
      buttonState = digitalRead(buttonPin);

      // check if the pushbutton is pressed.
      // if it is, the buttonState is HIGH:
      if (buttonState == HIGH) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
    }
    ```
