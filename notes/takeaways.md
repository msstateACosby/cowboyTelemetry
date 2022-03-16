# Takeaways
This file simply details what was learned through this experience, hopefully giving future members of list of the most important knowledge that should be carried down. There are two sections, the first - Experimental Knowledge - pertains to things that were learned that directly related to knowledge gained through the existence of the project. The second - Process Knowledge - relates more to specific errors we found and how to overcome them.

# Experimental Knowledge
- Undirected Antennas without extra power at the 900Mhz frequency range are only somewhat effective at range, losing transmission ability at ground level around 1700ft apart. 
- We need to learn more about antennas.

# Process Knowledge
- It sounds obvious, but one can't mix 3.3V and 5V. Future users may have better luck with level converters, but a 5V source is still needed for those to work.
- Don't solder feathers directly together, unless maybe the project is very finalized and more permanent connections are desired. Use the stacking headers instead to connect them. They will press fit.
- Don't get a true AtMega 328p Arduino. They might be fine for some projects, but considering that SD cards easily eat about half the available memory on their own and are necessary in most projects they will likely be lacking. A good alternative is an M0 based board, as they have about 8 times the memory at little to no increase in cost.
