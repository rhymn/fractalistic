# fractalistic
A project for controlling a heater using Arduino over the Internet.

## uploading to Arduino
"avrdude: stk500_getsync(): not in sync" this is most likely because the AutoResetOnSerial is enabled.
"avrdude: stk500_recv(): programmer is not responding" this is likely because you've choosen the wrong Serial port. My default ports for the RPi are stated in read.py

### todo
1. Temperature runtime adjustment
2. Outside temperature measure
3. Inside temperature measure
4. Radiator / water pump control (on/off)

### Heater
400V (3 Phase) electric heater.

### Arduino Uno
PID Regulator controlling temperature with 6 relays in 9 steps
Client checks for changes in the API every n minutes.

### Arduino Ethernet Adapter
Interface with the Internet

### API and Webapp
A simple Node.js webapp hosted at Heroku, Mongodb at MongoHQ
