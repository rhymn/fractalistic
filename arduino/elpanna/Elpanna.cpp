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


void Elpanna::setDesiredTemp(int desiredTemp){
	_desiredTemp = desiredTemp;
}


int Elpanna::getDesiredTemp(){
	return _desiredTemp;
}


void Elpanna::measure(){
	int num = 5;

	float measure[num];
	float sum;

	// Measure num times
	for(int i = 0; i<num; i++){
		measure[i] = Elpanna::getOhmFromThermistor();

		// Wait 0.01 sec
		delay(10);
	}

	// Calculate sum
	for(int i = 0; i<num; i++){
		sum += measure[i];
	}

	// Calculate average
	_res = sum / num;

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



