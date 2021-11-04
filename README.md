# cowboyTelemetry
A custom telemetry system for the MSU rocketry team. There are two main parts of the program: the onboard microprocessor program onboardTelemetry and the viewer program.
# onboardTelemetry
Uses an arduino (or related) to grab data from sensors and possibly other components on the rocket and organize them to be used by the ground telemetry system.
The initial system will likely simply output to a file.

Software depencies:
- Arduino IDE

Hardware depencies:
- Arduino (Uno for now)

# reciever
A simple arduino device that is similar to the onboardTelemetry program but just takes the radio data and sends over serial to the computer

# viewer
A python program that takes data given by the onboardTelemetry (right now in the form of reading some files produced by the onboardTelemetry program).

Software depencies
- MatPlotLib
- Tkinter

#A few notes:
Prelimary data file design:
Two files:
First data type definitions.
Second contains data samples collected during flight.
They are similar in format
Data type files are like: 
\<TypeOfDataEntry\> \<Units\> \<entryA\> \<entryB\> \<entryC\> ...

While the data time series follows the format:
\<TypeOfDataEntry\> \<Time\> \<entryA\> \<entryB\> \<entryC\> ...

Note: the number of entries can be any nonzero amount as long as the each time series entry has the same amount of entries as the type definition

Current Plans:
Allow data type and values to be in the same file so that it is easier to dynamically load information

Add stats information

hello my name is emily

SUp im quin

