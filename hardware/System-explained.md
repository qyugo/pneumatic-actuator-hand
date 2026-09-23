## Pneumatic + Electrical + Control System Explained

In this section, the pneumatic system is described as well as corresponding hardware.

<img src="https://github.com/user-attachments/assets/6c52b925-eda5-43a0-9bbf-006200f8da5c" width = "50%"/>

Since the tire compressor, relay, solenoid valves, and pressure transducer all run on 12V, the system will run from a 12V setting on a bench PSU.
Additionally, the COM pin on the Darlington transistor array will be connected to 12V.

The ESP32 can run on a 5V input and contains an onboard 3.3V regulator if needed further for the logic-side ADC/I2C components.

The push buttons, the IRLZ44N MOSFET, and the PWM relay will run on 3.3V.

<img src="https://github.com/user-attachments/assets/0b523fb0-b8bb-4afc-b990-f28a64022a3d" width = "50%"/>

### 1. Power Regulator: LM2596 12V-5V

The LM2596 is a cheap buck regulator that can be adjusted via its onboard screw terminal. Voltages may vary under load but this has seemed to hold up fine, as the only component requiring 5V is the ESP32.

<img src="https://github.com/user-attachments/assets/00c662ac-2ac1-4cc5-840d-f224cb211782" width = "50%" />

### 2. Pressure Transducer

A cheap pressure transducer with low Amazon ratings was obtained to enact a control loop around the estimated fill pressure of the McKibben actuators (from my test was about 8-10 psi). Therefore, it is placed on the accumulator tank, and used to turn on the tire compressor whenever the read pressure is <8, and turn off once >10.

Initially, the transducer had mislabeled wiring and an unstable pressure reading from its ADC. Therefore, calibrations were run with a test file (you can find these under code/testfiles-omit in this repo). Using a physical pressure gauge, values were compared and accurately zeroed for the transducer in code.

<img src="https://github.com/user-attachments/assets/3ecd6ee3-4bbe-4071-a46f-9c7bb24fae30" width="50%" />

A simple averaging algorithm was implemented for 16 samples taken 200 microseconds apart. Due to occasional noise spikes, the trigger for compressor-turn-on (feed more air in) is set after 5 consecutive readings below threshold.

<img src="https://github.com/user-attachments/assets/610697e7-106c-4848-a4b1-9f12f0736d8d" width = "50%" />
<img src="https://github.com/user-attachments/assets/c53b4a9c-561e-4acb-96b9-eb41f9881f1d" width = "30%"/>

### 3. Automotive Relay + Bang-Bang Control 

A 12V Bosch-style relay was used to turn the tire compressor on/off if required by the control loop. "Bang-bang" control describes a two-step on/off control mechanism, or an abrupt switching between two states.

<img src="https://github.com/user-attachments/assets/49650585-9318-46c0-93e9-19144d9ef432" width = "45%"/>
<img src="https://github.com/user-attachments/assets/a6434c05-4872-4878-a136-4fac18369dae" width = "45%"/>


This requires an N-channel MOSFET for the relay coil governed by a GPIO pin -> 220 ohm gate resistor, which dampens inrush current into the gate capacitance/prevents ringing.

The MOSFET drain goes to the low side relay coil, with the other side of the relay coil going to 12V. It is important in this type of control to include a flyback diode (+ towards 12V) to prevent spikes during MOSFET turn-off.

The source pin on the MOSFET goes to a any of the star-ground points across the system.

### 4. Solenoid Valves

12V 3-way, 2-port solenoid valves are used to turn each individual McKibben muscle "on." The muscle feeds from the system's air reservoir, expanded by the capacity of the 0.5L accumulator tank. The air gets directed along a valve manifold in which multiple solenoids can be attached, allowing for multiple degrees of muscle actuation.

<img src="https://github.com/user-attachments/assets/33c8dce9-9001-4104-b147-c244d0b5acbd" width = "38%"/>
<img src="https://github.com/user-attachments/assets/68edcc1b-c5b2-4f4c-88fb-510fa7d977d8" width = "40%"/>


When the valve is turned off, the third opening of the valve acts as an exhaust, which empties out air from the McKibben muscle.

This requires both the PCA9685 PWM relay and the ULN2805 Darlington transistor array. 

<img src="https://github.com/user-attachments/assets/7fe1898e-21b3-4189-800c-0b96e9ae66e2" width = "56%"/>

<img src="https://github.com/user-attachments/assets/cd9dc10b-2095-484f-a4b9-6cfb57fb1b8e" width = "32%"/>

The PCA9685 is a PWM generator with 16 channels that talks to the MCU over I2C. It theoretically should be able to do a degree of proportional control via PWM (for controlling slow rate/actuation speed), but I have yet to test this. 

The ULN2803A functions as the low-side switch for each of the solenoid valves, and therefore runs on 12V. The valve + connects to a PDB with 12V positives, while its negative pins route to the 8 potential channels on the ULN2803A's output side. The inputs to the transistor array will be the PCA9685 signals.

Therefore, one of each of these components allow for a maximum of 8 actuators, and an additional Darlington array will be required for more valves/muscles.

