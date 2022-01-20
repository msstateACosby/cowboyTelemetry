# Antenna / Radio Module 
While the antenna obviously isn't a piece of code to work on, it would still be a good idea to keep a written record of our thoughts.

## Questions
We have some questions for Dr. Green about antenna design listed here. Some background clarification will be listed below.
- How do we design a better antenna?
  - How much flexibility of design can we achieve with a fixed 915 Mhz frequency?
    - Can we make it longer / does that help?
    - Can we change the shape / does that help?
  - Can we make the rocket antenna somewhat directional (i.e not send signals into the middle of the rocket were that energy will just be lost)?
  - How much does having a directional ground antenna help?
  - Would it be possible and worthwile to amplify the signal?

- Other radio module options if nothing would work for this?

Essentially our problem is that our radio module product page only promises 2km under ideal conditions while we would like to achieve ideally probably something like 10k. They did say that has been achieved, but under very ideal conditions and directional antennas.

# Current Knowledge
It appears that we will not have much flexibility on our antenna, as the 915 MHz frequency is regulated and made to be low power so that licenses are not required. We could get a directional antenna for the ground, which should help. Dr. Green suggested an antenna, and we could potentially put 2 into a rocket to increase the power, but unless the rocket is designed for them, they might not work (both are longer than a  foot). 

I did find a formula for the data rate with is that the theoretical rate in bits per second R is roughly equal to F*log2(1+P/N) where F is the frequency, P is the power of the signal, and N is the noise in system at the frequence. No idea what expected noise is though.