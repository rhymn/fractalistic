#include <Elpanna.h>
#include <PID.h>
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

// TODO: Better names
const int one = 6;
const int two = 7;
const int three = 4;
const int four = 5;
const int five = 2;
const int six = 3;

const float Kp = 5, 
            Ki = 0.5, 
            Kd = 0.5;

const bool debug = false;

const unsigned long postingInterval = 60000; // 1 minute
unsigned long lastConnTime = 0;

Elpanna elpanna(60, 12, 13, A0);
PID pid(Kp, Ki, Kd);

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 50);
IPAddress myDns(195, 67, 199, 27);

Network network(mac, ip, myDns, server, port);

void setup(){

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  pinMode(errLED, OUTPUT);
  pinMode(okLED, OUTPUT);

  pid.setOutputMin(0);
  pid.setOutputMax(200);
  
  Serial.begin(9600);

  Serial.println("Fractalistic starting");

  if (debug) {
    // Kör igenom alla dioder och relän för att kolla så allt är rätt kopplat.
    Serial.print("Testing relays ...");
  
    int i;

    for(i = 1; i<11; i++){
      elpanna.setEffect(i, one, two, three, four, five, six);
      delay(500);
    }

    Serial.println("OK");
  }

  // Print headers
  Serial.print("Tid; Output (0-200); Ref; R; T; lastInput; lastError; lastOutput; p; i; d;");
  Serial.println();

  network.begin();
}


void loop(){
  
  float output;
  int outputRes;
  
  elpanna.measure();
  int temp = elpanna.getTemp();
  float setPoint = float(elpanna.getDesiredTemp());
    
  output = pid.compute(temp, setPoint);
  
  // Convert to get resolution right
  outputRes = int((output + 10) * (9.0 / (pid.getOutputMax() - pid.getOutputMin())));
  
  elpanna.setEffect(outputRes, one, two, three, four, five, six);

  Serial.print("<log>");

  Serial.print(pid.getLastMeasureTime());
  Serial.print("; ");

  Serial.print(output);
  Serial.print("; ");

  elpanna.printState();
  pid.printState();
  
  Serial.print("</log>");
  Serial.println();

  
  if(elpanna.isError()){
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
      elpanna.setDesiredTemp(60);
      Serial.println("Setting temp to 60");
    }
    else if(mode == "away"){
      elpanna.setDesiredTemp(30);
      Serial.println("Setting temp to 30");
    }
    else{
      mode = "home";
    }

    delay(200);
    network.setstat(elpanna.getTemp(), mode, output, outputRes);

    lastConnTime = millis();
  }

  delay(10000);
}


