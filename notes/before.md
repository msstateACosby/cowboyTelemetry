# Project Creation

While trying to come up with a payload project, a fairly "simple" idea was tossed around. Create a custom telemetry module, while radio connections and telemetry do exist on the rocket currently, they are not as easy to customize as preferred. Additonally, this system could potentially be used to eventually centralize computer processing aboard the rocket and better collate data. The telemetry system could also simulate acting as a flight computer, although this functionality would be limited as competition rules do not allow custom flight computers. However, the initial idea for the payload is simple. Create a radio system that could be used to perform two communication with the rocket and perform data streaming with various test data streams. The first phase is primarily to test functionality, not so much worried with the application yet.

In order to achieve this goal, parts were order that could implement a radio system and gather data to send across the stream. The following parts were ordered to meet this requirement:

- 2x Adafruit LoRa Radio FeatherWing RFM95W 900 MHz - This is the cornerstone of the project. These modules are unsprisingly radios. They were chosen for a few reasons. First, Adafruit offered them. This is maybe not a great reason to use a product, but Adafruit generally has pretty good support and good documentation. Second, the RFM95 is fairly high-powered radio compared to other options. It has a better range than the similar RF69, which will likely be necessary considering the system should ideally communicate at 30,000ft in the air. Third, it uses Adafruit's Feather system. Ideally, this system should keep the size of the electronics small and allow for straightforward assembly. One is used in the rocket, and another on the ground.

- 2x Adafruit Feather 328P - This board was chosen for two primary reasons. First, it uses Adafruit's Feather system, allowing it interface with the radio. Secondly, it uses the Atmega328P. This processor is theoretically nice because it uses the same processer as the Arduino does. This should bring the module to acting fairly similarly to a differently shaped Arduino. One is used in the rocket, and another on the ground.

- Adafruit 9-DOF Absolute Orientation IMU Fusion Breakout BNO055 - This is a fairly standard 9-DOF IMU that should provide good test data.

- TMP36 Analog Temperature sensor - Also serves as a good test sensor, this time using an anolog input that will also possibly provide code examples for interacting with an analog stream.

- Micro SD Card - A card to store the data on the rocket. This is not particularly required, but it would good to not lose data if radio systems fail. Additionally, this can be used to compare how much data was received vs how much data was generated. 

- Micro SD Breakout Board - A board to store the SD card.

Some programming was started before as well, but not much more than the most basic of concepts.