# Pneumatic Actuator Hand Skeleton
Multiple McKibben actuated hand for soft robotics.

This is my Air-powered McKibben soft actuated hand, powered by an old tire compressor + solenoid valves + PCA9685 PWM driver + ULN2803A Darlington transistor array. It features a self-topping compressor-accumulator tank controlled via N-Ch MOSFET + 12V Bosch automotive relay + 12V pressure transducer for bang-bang control.

Actuator theory, hardware explanations, and code are contained in this repo.

<img src="https://github.com/user-attachments/assets/5a207d2d-2c13-499e-8be3-73d14f9c49a0" width = "23%" />

<img src="https://github.com/user-attachments/assets/78ad065e-18bc-4b37-a1e5-52d40b91c5c1" width="39%" />

<img src="https://github.com/user-attachments/assets/ac546473-9cba-4b01-8b95-8ca17f0b7091" width = "26%"/>

<img src="https://github.com/user-attachments/assets/0cbae239-98e9-40c2-a2ed-997f29d4822f" width = "28%"/>

<img src="https://github.com/user-attachments/assets/611d7b21-6fae-4d71-a732-8fb64ac947c7" width = "15.5%"/>

<img src="https://github.com/user-attachments/assets/587444e8-6166-4d75-936d-e795cc61c938" width = "15%"/>

<img src="https://github.com/user-attachments/assets/bd54b646-4084-4109-8b77-bff0291e9b10" width = "30%"/>

## Demo

https://github.com/user-attachments/assets/2843a26b-b9ff-487c-ac3d-21256a61831c

## Current Limitations

1. Thumb actuation in progress. I have 6 more open air channels for the thumb and other miscellaneous functions. However, a better design of a proper saddle-joint for the thumb base/CMC may be required for a V2.

2. Design is meant to mimic hand bones, ligaments, tendons, and muscles. The complexity is not always practical, rather proof of concept.

3. Current actuation is absolute open/close of cheap solenoid valves. Proportional control has not been tested yet.

4. Tire compressor is old and loud.
