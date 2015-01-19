#include "Arduino.h"
#include "Temp.h"

Temp::Temp(int thermistorPin){
	_res = 0;
	_temp = 0;
	_thermistorPin = thermistorPin;
}

void Temp::measure(){
	int num = 10;

	float measure[num];
	float sum;

	// Measure num times
	for(int i = 0; i<num; i++){
		measure[i] = Temp::getOhm();

		// Wait 0.01 sec
		delay(10);
	}

	// Calculate sum
	for(int i = 0; i<num; i++){
		sum += measure[i];
	}

	// Calculate average
	_res = sum / num;

	_temp = Temp::getTempFromRes( _res );
}


int Temp::getTemp(){
	return _temp;
}

float Temp::getLastRes(){
	return _lastRes;
}

int Temp::getLastRawTemp(){
	return _lastRawTemp;
}


int Temp::getTempFromRes(float r){
	float temp;
	
	temp = (r - 815.8) / 7.95;

	_lastRawTemp = temp;
	
	// Make sure we don't get crazy output ..
	if(temp < 10){
		temp = 10;
	}
	
	if(temp > 90){
		temp = 90;
	}
	
	return temp;
}


float Temp::getOhm(){
  int sensorValue;

  float v;
  float r;
  float rMin = 800;
  float rMax = 1700;

  sensorValue = analogRead(_thermistorPin);

  v = sensorValue * (5.0 / 1023.0);

  // Calculate resistance
  r = 10000 * ((5/v)-1);

  _lastRes = r;

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

bool Temp::isError(){
	return _isErr;
}
