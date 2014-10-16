#include <Elpanna.h>
#include <Heater.h>
#include <PID.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Network.h>
#include <configuration.h>
#include <plotly_streaming_ethernet.h>

#define nTraces 4
// View your tokens here: https://plot.ly/settings
// Supply as many tokens as data traces
// e.g. if you want to ploty A0 and A1 vs time, supply two tokens
char *tokens[nTraces] = {"oz3o1opezg", "01lgfkoprd", "nyxtajecjy", "3g4703fkh6"};

// arguments: username, api key, streaming token, filename
plotly graph("rhymn", "98371gb3z5", tokens, "Elpannan", nTraces);

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

const float Kp = 7, 
            Ki = 0.4, 
            Kd = 5;

const bool debug = false;

const unsigned long postingInterval = 60000; // 1 minute
unsigned long lastConnTime = 0;

Elpanna elpanna(60, 12, 13, A0);
Heater heater(one, two, three, four, five, six);
PID pid(Kp, Ki, Kd);

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 50);
IPAddress myDns(195, 67, 199, 27);

Network network(mac, ip, myDns, server, port);

// Arduino Setup
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
      heater.setEffect(i);
      delay(500);
    }

    Serial.println("OK");
  }

  network.begin();

  // graph.log_level = 4;
  
  // graph.timezone = "Europe/Stockholm";

  // Extend graphs already created
  // graph.fileopt = "extend";
  
  // graph.dry_run = true;
  
  // Initialize a streaming graph in your plotly account
  // graph.init();

  // Initialize plotly's streaming service
  // graph.openStream(); 
}


// Arduino Main Loop
void loop(){
  
  float output;
  int outputRes;
  
  elpanna.measure();
  int temp = elpanna.getTemp();
  float setPoint = float(elpanna.getDesiredTemp());
    
  output = pid.compute(temp, setPoint);
  
  // Convert to get resolution right
  outputRes = int((output + 10) * (9.0 / (pid.getOutputMax() - pid.getOutputMin())));
  
  heater.setEffect(outputRes);
  
  /*
  graph.plot(millis(), output, tokens[0]);
  graph.plot(millis(), outputRes, tokens[1]);
  graph.plot(millis(), temp, tokens[2]);
  graph.plot(millis(), setPoint, tokens[3]);  
  */
  
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


