# McKibben Actuator Theory and Construction

This project uses some unstandardized and archaic ways of constructing McKibben actuators, therefore the concept build may not contain fully uniform actuators.
This page may be updated for more configurations and McKibben types, for various strength and strain characteristics.

## 1. Basic McKibben Actuator
Latex 260 balloons were used for the inner tubing of the actuator, with a 1.5inch-diameter outer woven sleeve, used for wire harnessing.

The woven sleeve acts similar to that of a "Chinese finger trap," in that the sleeve becomes shorter when it's cross-sectional area increases.
Therefore, a balloon inflating inside the sleeve will convert a force via shortening of the actuator, mimicking the force-generation capabilities of human muscles.

<img src="https://github.com/user-attachments/assets/86eb7993-3c51-4ce8-85f5-dda7a1a209ff" width="50%">

### Working Principle

https://github.com/user-attachments/assets/880b9059-b5e3-422e-a9c6-61a39bed4400

Each actuator will have a characteristic strain percentage as well as force produced, relative to how much air pressure is applied.

## 2. Analytical Model - Chou and Hannaford

The Chou and Hannaford model produces a force, pressure, and braid angle relationship, assuming an ideal cylindrical actuator with no end tapering, no accounting for bladder thickness and elasticity, and $D_0$ being the diameter of the actuator at a braid angle $\theta = 90^\circ$:

$$
F = \frac{\pi D_0^2P}{4} * (3cos^2\theta - 1)
$$

Source: Chou & Hannaford. (1996) Measurement and modeling of McKibben pneumatic artificial muscles.

Even though this model does not utilize the length of the actuator L for determining strain parameters (for purposes of range of motion) of the muscles, the contraction ratio can be derived from change in braid angle:

$$
\epsilon = 1 - \frac{cos(\theta)}{cos\theta_0}
$$

The maximum contraction angle $\theta_{max}$ can be found by setting F = 0 and solving for $\theta$, which yields an angle of 54.7 degrees. This appears to be referred to as a "magic angle" in which maximum contraction is found in braided McKibbens.

The following is a strain-to-force graph of linear McKibbens of three starting thicknesses (0.05cm, 0.1cm, 0.15cm) across two tested pressures (0.54MN/m^2, 1.37MN/m^2):

<img src="https://github.com/user-attachments/assets/a40ee467-a660-4ae7-9d18-4164bd1cb8cc" width="50%"/>

(Bertrand Tondu, 2012)

As observed in this example, there is a certain strain ratio in which peak force is found, consistent across the McKibben actuators. Interestingly, a similar phenomenon can be found in **human muscles** in the _length-tension curve_. At a certain muscle length, a peak force is found due to sarcomere overlap:

<img src="https://github.com/user-attachments/assets/010ba20b-6248-4f09-b50c-eddcc3b2b6f0" width="50%"/>

## Some Strain Tests

Theoretically, the percentage of strain would be identical for a single McKibben actuator for any length, so absolute range of motion can be scaled with longer actuators. This was slightly verified across a few tested actuators, albeit without the most accurate testing conditions. It is worth noting that shorter actuators may have a smaller contraction ceiling due to the end connectors/tapers being a larger relative portion of the total actuator length.

Furthermore, the starting position of the actuator can have a braid angle of larger than 90 °, if working from a slightly stretched position, as the above formula accounts for a neutral starting point, where the braid angles are at a right angle. Therefore, experimental strain _distance_ can perhaps be more than what the formula gives.

Ultimately, under the Chou and Hannaford model, the strain ratio is simply reliant on the starting angle and the theoretical maximum contraction angle of 54.7, and then accounting for any forces that oppose contraction, as well as failure processes due to bladder or braid rupture. 

1/2" Sleeve:

<img src="https://github.com/user-attachments/assets/d182b4b0-0426-41e3-ad98-28bc4c927588" width="40%" />
<img src="https://github.com/user-attachments/assets/a41d54b8-ee15-4bd7-a2a9-08309671daed" width="40%"/>

1/4" Sleeve:

<img src="https://github.com/user-attachments/assets/b87498c4-7eef-4a18-a079-5b83bee875d0" width="38%"/>
<img src="https://github.com/user-attachments/assets/50694b3e-2e4f-4fff-b3d5-0a0b2f6739b2" width="40%"/>



