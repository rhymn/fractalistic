
#include <Elpanna.h>
#include <PID.h>

/**
 * Ett enkelt reglerprogram för att styra en panna
 * - ett börvärde ska hållas så bra som möjligt
 *
 * Indata från en termometer på pannan (termistor)
 *
 * I framtiden även inne- och utetemperatur för att
 * få ännu bättre reglering
 *
 */

const int okLED = 12;
const int errLED = 13; 

// TODO: Bättre namn på dessa :)
const int one = 6;
const int two = 7;
const int three = 4;
const int four = 5;
const int five = 2;
const int six = 3;

const float Kp = 3, 
            Ki = 0.8, 
            Kd = 1;

Elpanna elpanna(60, 12, 13, A0);
PID pid(Kp, Ki, Kd);

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

  Serial.print("Startar styrprogram och testar effektlagen pa relaer...");

  // Kör igenom alla dioder och relän för att kolla så allt är rätt kopplat.
  int i;
  for(i = 1; i<11; i++){
    elpanna.setEffect(i, one, two, three, four, five, six);
    delay(750);
  }

  Serial.println("OK");

  // Print headers
  Serial.print("Kp, Ki, Kd: ");
  Serial.print(Kp); Serial.print(Ki); Serial.print(Kd);
  Serial.println();

  Serial.print("Tid; Output (0-200); Ref; R; T; lastInput; lastError; lastOutput; p; i; d;");
  Serial.println();

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

  delay(10000);
}


