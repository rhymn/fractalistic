#include "Arduino.h"
#include "Elpanna.h"

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


/**
 * Constructor
 *
 */
Elpanna::Elpanna(int desiredTemp, int okLED, int errLED, int thermistorPin){
	_desiredTemp = desiredTemp;

	_okLED = okLED;
	_errLED = errLED;
	_res = 0;
	_temp = 0;

	_isErr = false;

	_thermistorPin = thermistorPin;

}


int Elpanna::getDesiredTemp(){
	return _desiredTemp;
}


void Elpanna::measure(){
	_res = Elpanna::getOhmFromThermistor();
	_temp = Elpanna::getTempFromRes( _res );
	return;
}


int Elpanna::getTemp(){
	return _temp;
}


int Elpanna::getTempFromRes(float r){
	int temp;
	
	temp = (r - 815.8) / 7.95;
	
	// Make sure we don't get crazy output ..
	if(temp < 10){
		temp = 10;
	}
	
	if(temp > 90){
		temp = 90;
	}
	
	return temp;
}


float Elpanna::getOhmFromThermistor(){
  int sensorValue;

  float v;
  float r;
  float rMin = 800;
  float rMax = 1700;

  sensorValue = analogRead(_thermistorPin);

  v = sensorValue * (5.0 / 1023.0);

  // Calculate resistance
  r = 10000 * ((5/v)-1);

  if(r < rMin){
	_isErr = true;
  }

  else if(r > rMax){
	_isErr = true;
  }

  else{
	_isErr = false;
  }

  return r;
}

bool Elpanna::isError(){
	return _isErr;
}

void Elpanna::setEffect(int e, int one, int two, int three, int four, int five, int six){

	// Each effect step has a binary equivalent for digitalWrite
	// This will likely be different using real relays
	byte pattern[] = {B000000, B100000, B101000, B101010, B011010, B010110, B010101, B110101, B111101, B111111};

	digitalWrite(two, bitRead(pattern[e], 4)); digitalWrite(four, bitRead(pattern[e], 2)); digitalWrite(six, bitRead(pattern[e], 0));
	digitalWrite(one, bitRead(pattern[e], 5)); digitalWrite(three, bitRead(pattern[e], 3)); digitalWrite(five, bitRead(pattern[e], 1));
}

void Elpanna::printState(){
	Serial.print(_desiredTemp);
	Serial.print("; ");

	Serial.print(_res);
	Serial.print("; ");

	Serial.print(_temp);
	Serial.print("; ");

	return;
}






