# fractalistic
A polyglot project for controlling a heater using Arduino and Raspberry Pi over the Internet.

## uploading to Arduino
"avrdude: stk500_getsync(): not in sync" this is most likely because the AutoResetOnSerial is enabled.
"avrdude: stk500_recv(): programmer is not responding" this is likely because you've choosen the wrong Serial port. My default ports for the RPi are stated in read.py

### todo
1. Temperature runtime adjustment
2. Outside temperature measure
3. Insida temperature measure
4. Radiator / water pump control (on/off)


### Heater
#### Arduino

### Middleware
Python on a Raspberry Pi

### Webapp
Node.js with Express and Jade hosted at Heroku