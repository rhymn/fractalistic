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

const unsigned long postingInterval = 1000 * 60 * 5; // 5 minutes
unsigned long lastConnTime = 0;
int desiredTemp = 60;


Temp temp(A0);
Heater heater(one, two, three, four, five, six);
PID pid(Kp, Ki, Kd);

// Variables in configuration.h
Network network(mac, ip, myDns, server, port);

float output;
int outputRes;
int currentTemp;

String mode;

// Arduino Setup
void setup(){

  mode = "home";

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

  // Set to zero when we start
  heater.setEffect(0);

  Serial.begin(9600);

  if (debug) {
    // Serial  

    Serial.println("Fractalistic starting");
    Serial.print("Testing relays ...");
  
    for(int i = 1; i<11; i++){
      heater.setEffect(i);
      delay(500);
    }

    Serial.println("OK");
  }

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

String parseJson(String jsonStr, String key){
  int kStart = jsonStr.indexOf(key);
  int divider = jsonStr.indexOf(":", kStart + 4);
  int vStart = jsonStr.indexOf("\"", divider) + 1;

  int vEnd = jsonStr.indexOf("\"", vStart) + 1;

  String value = jsonStr.substring(vStart, vEnd - 1);

  return value;
}


// Arduino Main Loop
void loop(){
  boolean isJson = false;
  String jsonStr = "";

  output = 0;
  outputRes = 0;
  currentTemp = 0;
  
  temp.measure();
  currentTemp = temp.getTemp();
    
  output = pid.compute(currentTemp, float(desiredTemp));
  
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


  if(Serial.available() > 0){
    while(Serial.available() > 0){
      char in = Serial.read();

      if(in == '{'){
        isJson = true;
      }

      if(isJson){
        jsonStr += in;
      }

      if(in == '}'){
        isJson = false;
      }
    }

    delay(200);

    mode = parseJson(jsonStr, "mode");

    if(mode == "home"){
      desiredTemp = 60;
      Serial.println("Setting temp to 60");
    }
    else if(mode == "away"){
      desiredTemp = 30;
      Serial.println("Setting temp to 30");
    }

    // Only send json-data after a received message

    Serial.print("{");
    Serial.print("'id':'main-log',");

    Serial.print("'debug':");
    Serial.print(debug);
    Serial.print(",");

    Serial.print("'err':");
    Serial.print(temp.isError());
    Serial.print(",");

    Serial.print("'temp':");
    Serial.print(currentTemp);
    Serial.print(",");

    Serial.print("'desiredTemp':");
    Serial.print(desiredTemp);
    Serial.print(",");

    Serial.print("'outputRes':");
    Serial.print(outputRes);
    Serial.print(",");

    Serial.print("'mode':");
    Serial.print("'" + mode + "'");
    Serial.print(",");

    Serial.print("'output':");
    Serial.print(output);
    Serial.print("}");

    Serial.println();

  }

  delay(10000);
}


