## More Advanced McKibben Configurations

According to Google, due to the aforementioned "magical number" in braid-angle limit described in [Linear-Simple.md](Linear-Simple.md), the maximum contraction ratio of a McKibben amounts to approximately 36.3% strain.

With a lower budget and manufacturing limitations, I wanted to see if it was possible to obtain a greater strain attribute (more than 36.3%) for McKibbens, as the length of the current actuators are limited by the length of the forearm bones.

<img src="https://github.com/user-attachments/assets/0a4369a3-d8f3-4eae-bebf-b23aea6cd91d" width="30%" />

<img src="https://github.com/user-attachments/assets/3139ed34-9820-4abf-95e5-ccd954cde4fb" width="60%" />


Ideally, having the finger actuators to be able to place on the palm of the hand can separate biomechanical functions such as finger flexion from wrist flexion. Even though in a human body, the finger flexors do continue to run under the forearm flexors, it is difficult to implement in a design such as this; as finger flexion inevitably causes some wrist flexion, etc.

Of course, this can be mitigated in controls by coactivating wrist extensors each time the fingers are flexed, but as this doesn't seem to happen in humans, according to my force sensors.

For now, as a thought experiment, different macro configurations of McKibbens can be theorized to give a better strain profile, and perhaps more force production.

## 1. Active Woven Textiles

Suzumori and Hiramitsu provides a woven structure of thin McKibbens in which they term "active textile." This is difficult to describe in words, as a thin McKibben creates a snakelike pattern through a plane composed of woven strings; upon contraction of the single McKibben the woven fabric can deform not only axially, but warp in other directions as well.

<img src="https://github.com/user-attachments/assets/a5e86bb2-9e0e-4afe-a808-5124f87ef14c" width="40%" />
<img src="https://github.com/user-attachments/assets/31cb9ad0-ed63-4b85-856a-9d43e27c222f" width="54%"/>

Source: Hiramitsu, and Suzumori (2019). Experimental Evaluation of Textile Mechanisms Made of Artificial Muscles. https://ieeexplore.ieee.org/document/8722802

This is similar to what I recall seeing in Ozgun Kilic Afsar's electrofluidic muscles, an actuation process I'll go deep on trying to manufacture and recreate in the future:

<img src="https://github.com/user-attachments/assets/a0037013-74f2-4fd0-993d-d22772d108d0" width="80%"/>

Source: Ozgun Kilic Afsar: https://ozgun.io/

Although, it seems Afsar's woven fabric "strings" are also composed of thin McKibbens themselves, perhaps providing more force akin to more springs in parallel, and the snakelike tube routing through the parallel McKibbens are the electrohydrodynamic fiber pumps, or as I like to call them, "water railguns."

However, these configurations seem like an effective force multiplier or a actuation-direction-changer, as Hiramitsu's paper confirms a maximum contraction ratio of 7.1%.

## 2. Chain-Link Actuators

A very interesting build involving a chain-like configuration, with each chain loop being a "ring" composed of two linear McKibbens, which capitalizes on both axial strain and the bending characteristics of McKibbens. The chain can then be extended to several rings.

<img src="https://github.com/user-attachments/assets/2229403f-962c-42ef-9264-9a4ad37bee8f" width="50%" />

<img src="https://github.com/user-attachments/assets/772c02b9-1c2e-49a6-9766-d6661183c044" width="44%" />


Wood, R., and Bruder, D. (2021). The Chain-link Actuator: Exploiting the Bending Stiffness of McKibben Artificial Muscles to Achieve Larger Contraction Ratios
https://ntrs.nasa.gov/api/citations/20220008196/downloads/2021_JOURNAL_RAL_Dan_ChainLinkActuator.pdf


