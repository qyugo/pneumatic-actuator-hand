---
title: Limitations
nav_order: 5
---

## Current Limitations

1. Thumb actuation in progress. I have 6 more open air channels for the thumb and other miscellaneous functions. However, a better design of a proper saddle-joint for the thumb base/CMC may be required for a V2.

2. Design is meant to mimic hand bones, ligaments, tendons, and muscles. The complexity is not always practical, rather proof of concept.

3. Current actuation is absolute open/close of cheap solenoid valves. Proportional control has not been tested yet.

4. Tire compressor is old and loud.
   
6. I have yet to write a more robust control method beyond just buttons, perhaps some tuning that overcomes inconsistencies in the custom ligaments/antagonists if proportional control is possible with these solenoid valves.

## McKibben Actuator Limitations

8. The nature of soft actuators is lower force output per unit when compared to an electromagnetic motor, as well as a much smaller range of motion. It is possible perhaps to use more advanced configurations to increase range of motion as well as McKibbens in parallel to multiply force output, but I have yet to test this.

9. Pneumatic or hydraulic soft actuator systems typically require a bulky reservoir (in the case of this project, a 0.5L air tank) which may add a lot of mass.

However, there was a solution developed by Ozgun Kilic Afsar, involving an electro-hydro-dynamic system using a charged fluid and a very high voltage to transfer fluids between agonist and antagonist McKibbens, without the need for an external reservoir. I'd very much like to explore this deeper when I have the time.
