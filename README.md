# cowboyTelemetry
A custom telemetry system for the MSU rocketry team. There are two main parts of the program: the onboard microprocessor program onboardTelemetry and the viewer program.
# onboardTelemetry
Uses an arduino (or related) to grab data from sensors and possibly other components on the rocket and organize them to be used by the ground telemetry system.
The initial system will likely simply output to a file.

Software depencies:
- Arduino IDE

Hardware depencies:
- Arduino (Uno for now)


# viewer
A python program that takes data given by the onboardTelemetry (right now in the form of reading some files produced by the onboardTelemetry program).

Software depencies
- MatPlotLib
- Tkinter

#A few notes:
Prelimary data file design:
Two files:
First contains flight metadata.
Second contains data samples collected during flight.
Both adhere to this format per line
\<TypeOfDataEntry\> \<entryA\> \<entryB\> \<entryC\> ...

It is up to the viewer to correctly interpret the files as the amount of entries could vary between different types (but probably not between the two files)


