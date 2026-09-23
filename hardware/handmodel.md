# Hand Model + Skeleton

## 1. Bone Geometry

Rather than create perhaps some simpler structures (particularly for the thumb), I wanted to design a hand model that references each of the hand bones in the human body.

In this case, I wanted to mimic the geometry of each joint and the structure of the bones, since it appears that nature has done progressive iterations of FEA analysis on our bone structure over the years.

<img src="https://github.com/user-attachments/assets/5a207d2d-2c13-499e-8be3-73d14f9c49a0" width = "39%" />
<img src="https://github.com/user-attachments/assets/ac546473-9cba-4b01-8b95-8ca17f0b7091" width = "45%"/>

I mainly wanted to construct a more biomimetic model so I could learn more about the hand bones and joints, since I personally was dealing with pain in my carpometacapral (CMC) joint on my thumb side, my triangular fibrocartilage complex (TFCC) on my pinky-side, and a ganglion cyst at the base of my index carpal bone from my training.

In the months since building this model, I have personally rehabilitated these joints by strengthening all the muscles around these joints to a very extreme degree.

## 2. Joint Geometry

There are also very interesting joint capsule geometries across the hand, mainly the saddle/sellar joint in the thumb base, which proved to be a challenge to construct and control.

<img src="https://github.com/user-attachments/assets/414c57af-7e24-4783-91f3-4d34961617eb" width = "45%"/>
<img src="https://github.com/user-attachments/assets/40272db6-db36-4022-9fbd-5458af7c7d37" width = "43%"/>

A small simplification that I made is I put hinge joints at the base of the phalanges, instead of ball-and-socket. Therefore, this V1 model will be incapable of finger abduction/adduction.

However, I did attempt to make a saddle joint for the thumb and trochoid/ellipsoidal joint for the wrist.

<img src="https://github.com/user-attachments/assets/3c369ea5-7a31-4def-a3ed-f6442036f412" width = "40%"/>

<img src="https://github.com/user-attachments/assets/13a9faf0-a081-47b7-a58f-0b812a13b9ea" width = "50%"/>

## 3. Joint Stabilizers + Antagonists

During construction, I also wanted to replicate the joint stabilizers instead of using bearings. In a more industrial setting, bearings would perhaps keep the system more consistent and easier to control, but I wanted to play around with some knot-tying and hand-wrapping of joint stabilizers.

Collateral ligaments connect bone-to-bone. Unlike muscles, ligaments are incredibly stiff, with a Young's modulus of approximately 1.0-1.2 GPa compared to the 0-600kPa (nonlinear) stiffness behavior of muscles.

For ligaments, I used high-strength fishing line to thread and tie with a fishing knot. Something else to consider is that I didn't plan for antagonist muscles (muscles that extend the finger, only ones that flex it), so I tied a thin elastic band around the finger to allow for antagonist spring-like behavior when the flexion muscle is off, and also doubling as additional protection for the joints/ligaments in case they slip.

<img src="https://github.com/user-attachments/assets/5fecc6b8-66d2-449a-b60d-2344f7611647" width = "54%"/>

<img src="https://github.com/user-attachments/assets/07630795-dc18-40a2-bec0-12a795270ebd" width = "38%"/>

<img src="https://github.com/user-attachments/assets/24cc0670-28e4-4297-87ef-fb483d545da8" width = "80%"/>

Antagonist "spring" demo:

https://github.com/user-attachments/assets/14df10ae-32fb-4018-bb55-03f4eb86eb4b









