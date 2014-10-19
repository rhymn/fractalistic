#include <Heater.h>
#include <PID.h>
#include <Temp.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Network.h>
#include <configuration.h>

/**
 * Fractalistic main
 *
 */

const int okLED = 8;
const int errLED = 9;

const int one = 6;
const int two = 7;
const int three = 4;
const int four = 5;
const int five = 2;
const int six = 3;

const float Kp = 8, 
            Ki = 0.2, 
            Kd = 5;

const bool debug = false;

const unsigned long postingInterval = 15000; // 5 minutes
unsigned long lastConnTime = 0;
int desiredTemp = 60;


Temp temp(A0);
Heater heater(one, two, three, four, five, six);
PID pid(Kp, Ki, Kd);

// Variables in configuration.h
Network network(mac, ip, myDns, server, port);

// Arduino Setup
void setup(){

  // PinMode
  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(three, OUTPUT);
  pinMode(four, OUTPUT);
  pinMode(five, OUTPUT);
  pinMode(six, OUTPUT);
  pinMode(errLED, OUTPUT);
  pinMode(okLED, OUTPUT);

  // PID
  pid.setOutputMin(0);
  pid.setOutputMax(200);

  // Serial  
  // Serial.begin(9600);

  // Serial.println("Fractalistic starting");

  if (debug) {
    Serial.print("Testing relays ...");
  
    for(int i = 1; i<11; i++){
      heater.setEffect(i);
      delay(500);
    }

    Serial.println("OK");
  }

  network.begin();
}

void showError(bool error){
  if(error){
    digitalWrite(errLED, HIGH);
    digitalWrite(okLED, LOW);
  }
  
  else{
    digitalWrite(errLED, LOW);
    digitalWrite(okLED, HIGH);
  }
}

// Arduino Main Loop
void loop(){

  float output = 0;
  int outputRes = 0;
  int currentTemp = 0;
  float setPoint = 0;
  
  temp.measure();
  currentTemp = temp.getTemp();
  setPoint = float(desiredTemp);
    
  output = pid.compute(currentTemp, setPoint);
  
  // Convert to get resolution right
  outputRes = int((output + 10) * (9.0 / (pid.getOutputMax() - pid.getOutputMin())));
  
  heater.setEffect(outputRes);
  
  if(temp.isError()){
    digitalWrite(errLED, HIGH);
    digitalWrite(okLED, LOW);
  }
  
  else{
    digitalWrite(errLED, LOW);
    digitalWrite(okLED, HIGH);
  }

  network.manageConn();

  if(millis() - lastConnTime > postingInterval){

    String mode = Network::parseJson(network.getsettings(), "mode");

    if(mode == "home"){
      desiredTemp = 60;
      // Serial.println("Setting temp to 60");
    }
    else if(mode == "away"){
      desiredTemp = 30;
      // Serial.println("Setting temp to 30");
    }
    else{
      mode = "home";
    }

    network.setstat(currentTemp, mode, output, outputRes);

    lastConnTime = millis();
  }


  delay(2000);
}

