# Pneumatic-Hand
Multiple McKibben actuated hand for soft robotics.

Air-powered McKibben soft actuators powered by tire compressor + solenoid valves + PCA9685 PWM driver + ULN2803A Darlington transistor array.
Self-topping accumulator tank and old 12V tire compressor using bang-bang control via N-Ch MOSFET + 12V Bosch automotive relay + 12V pressure transducer.

https://github.com/user-attachments/assets/2843a26b-b9ff-487c-ac3d-21256a61831c

Limitations
*Thumb actuation in progress. I have 6 more open air channels for the thumb and other miscellaneous functions.
*Design is meant to mimic hand bones, ligaments, tendons, and muscles. The complexity is not always practical, rather proof of concept.
*Current actuation is absolute open/close of cheap solenoid valves. Proportional control has not been tested yet.
*Tire compressor is old and loud.
