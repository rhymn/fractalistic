#include "Heater.h"
#include "PID.h"
#include "Temp.h"
#include "SPI.h"

/**
 * Fractalistic main
 *
 */

const int MINIMAL_EFFECT = 1;

const int OK_LED = 8;
const int ERR_LED = 9;

const int one = 6;
const int two = 7;
const int three = 4;
const int four = 5;
const int five = 2;
const int six = 3;

const bool debug = false;

int desiredTemp = 60;
int lastDesiredTemp = desiredTemp;

Temp temp(A0);
Heater heater(one, two, three, four, five, six);
PID pid(8, 0.2, 5);

float output;
int outputRes;
int currentTemp;

String mode;
String forecast;

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
  pinMode(ERR_LED, OUTPUT);
  pinMode(OK_LED, OUTPUT);

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


String parseJson(String jsonStr, String key){
  int kStart = jsonStr.indexOf(key);

  if(kStart == -1){
    return "";
  }

  int divider = jsonStr.indexOf(":", kStart + 1);
  int vStart = jsonStr.indexOf("\"", divider) + 1;

  int vEnd = jsonStr.indexOf("\"", vStart) + 1;

  String value = jsonStr.substring(vStart, vEnd - 1);

  return value;
}


// Arduino Main Loop
void loop(){
  boolean isJson = false;

  String jsonStr;

  output = 0;
  outputRes = 0;
  currentTemp = 0;
  
  temp.measure();
  currentTemp = temp.getTemp();
    
  output = pid.compute(currentTemp, float(desiredTemp));
  
  // Convert to get resolution right
  outputRes = int((output + 10) * (9.0 / (pid.getOutputMax() - pid.getOutputMin())));
  
  if(temp.isError()){
    digitalWrite(ERR_LED, HIGH);
    digitalWrite(OK_LED, LOW);

    heater.setEffect(MINIMAL_EFFECT);
  }
  
  else{
    digitalWrite(ERR_LED, LOW);
    digitalWrite(OK_LED, HIGH);

    heater.setEffect(outputRes);
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

    String jsonMode = parseJson(jsonStr, "mode");
    String jsonOutside = parseJson(jsonStr, "outside");

    if(jsonMode == "home"){
      mode = "home";
      desiredTemp = 60;
    }
    else if(jsonMode == "away"){
      mode = "away";
      desiredTemp = 30;
    }

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

    Serial.print("'lastRawTemp':");
    Serial.print(temp.getLastRawTemp());
    Serial.print(",");

    Serial.print("'lastRes':");
    Serial.print(temp.getLastRes());
    Serial.print(",");

    Serial.print("'mode':");
    Serial.print("'" + mode + "'");
    Serial.print(",");

    Serial.print("'outside':");
    Serial.print("'" + outside + "'");
    Serial.print(",");

    Serial.print("'lastP':");
    Serial.print(pid.getLastP());
    Serial.print(",");

    Serial.print("'lastI':");
    Serial.print(pid.getLastI());
    Serial.print(",");

    Serial.print("'lastD':");
    Serial.print(pid.getLastD());
    Serial.print(",");

    Serial.print("'measureTime':");
    Serial.print(pid.getLastMeasureTime());
    Serial.print(",");

    Serial.print("'output':");
    Serial.print(output);
    Serial.print("}");

    Serial.println();
  }

  // Rest if desired temp has not changed
  if(lastDesiredTemp == desiredTemp){
    delay(30000);
  }

  lastDesiredTemp = desiredTemp;
}


