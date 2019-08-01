# ArduinoRFJammerDetector
 Simple Arduino project to detect RF jammers for a couple of bucks
 
Simple Script to 'detect' jammers, really just looks at the average analog in values from a cheap 433mhz RX component and then decides if its been held 'low' ( like a remote has been pressed ) for too many seconds.

# Wiring
 - Datapin of 433mhz RX -> analog 'inPin' ( default *analog* 2 )
 - Green LED -> 'greenLED' ( default 2 )
 - Red LED -> 'redLED' ( default 3)
 - Vibration Motor -> 'buzzPin' ( default 11 )

![example build](https://github.com/AndrewMohawk/RFJammerDetector/raw/master/example.jpg)

