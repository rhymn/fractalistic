# Fractalistic
Remote Heater Control

![](https://github.com/rhymn/fractalistic/blob/master/extra/elpanna.jpg)

![](https://github.com/rhymn/fractalistic/blob/master/extra/fritzing.png)

## Heater
400V (3 Phase) electric heater.

## Arduino Uno
PID Regulator controlling temperature with 6 relays in 9 steps

Arduino client checks for changes and sends stats using the API every 5 minutes.

## Arduino Ethernet Adapter
Interface with the Internet

## API and Webapp
A simple Node.js webapp that can set temperature and display stats from the Arduino

hosted at Heroku, Mongodb at MongoHQ

## Raspbian

### uploading to Arduino
"avrdude: stk500_getsync(): not in sync" this is most likely because the AutoResetOnSerial is enabled.
"avrdude: stk500_recv(): programmer is not responding" this is likely because you've choosen the wrong Serial port. My default ports for the RPi are stated in read.py

In Raspbian the Arduino shows up as /dev/ttyACM0

```
sudo make clean
sudo make
sudo make upload
sudo cat /dev/ttyACM0
```

### Libraries
Arduino libraries goes into /usr/share/arduino/libraries/

#### Dhcp.h
To prevent unwanted behaviour an adjustment to Dhcp.h must be made. If no ethernet connection is available the timeout is too long (1 minute), this is adjusted to a few seconds with the following line:


Remember to do a

```
make clean
```


### todo
* Temperature runtime adjustment (Done)
* Outside temperature measure
* Inside temperature measure
* Radiator / water pump control (on/off)
* Refactor arduino c++ code
* Finish and merge "tempClass" branch to master
* python script on the raspberry for simplifying compilation, deployment and debugging

### More
http://playground.arduino.cc/Main/DisablingAutoResetOnSerialConnection
