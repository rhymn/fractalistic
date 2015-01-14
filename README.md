# Fractalistic
Remote Heater Control

![](https://github.com/rhymn/fractalistic/blob/master/extra/fracd.jpg)

![](https://github.com/rhymn/fractalistic/blob/master/extra/fractalistic.png)

## Components

### Heater
400V (3 Phase) electric heater.

### Arduino Uno
PID Regulator controlling temperature with 6 relays in 9 steps

Communicates with the Raspberry Pi via usb serial
Software in C++

### Raspberry Pi
Proxy program handling settings and sends stats using web API every 30 minutes.

#### Raspbian

##### uploading to Arduino
"avrdude: stk500_getsync(): not in sync" this is most likely because the AutoResetOnSerial is enabled.
"avrdude: stk500_recv(): programmer is not responding" this is likely because you've choosen the wrong Serial port. My default ports for the RPi are stated in read.py

In Raspbian the Arduino shows up as /dev/ttyACM0

```
sudo make clean
sudo make
sudo make upload
sudo cat /dev/ttyACM0
```

##### Libraries
Arduino libraries goes into /usr/share/arduino/libraries/

##### Crontab
Run proxy script every n minutes

```
*/30 * * * * sudo python /home/david/fractalistic/python/proxy.py >/var/log/fractalistic 2> /var/log/fractalistic
```


### API and Web app
Displays current stats for the heater, user can interact and change mode between "home" and "away"

Node.js hosted at Heroku, Mongodb at Compose


## todo
* Temperature runtime adjustment (Done)
* Outside temperature measure
* Inside temperature measure
* Radiator / water pump control (on/off)
* Refactor arduino c++ code
* Finish and merge "tempClass" branch to master
* python script on the raspberry for simplifying compilation, deployment and debugging

## More
http://playground.arduino.cc/Main/DisablingAutoResetOnSerialConnection
