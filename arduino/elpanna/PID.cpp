#include "Arduino.h"
#include "PID.h"

/**
 * En enkel PID-regulator
 *
 */


PID::PID(float kp, float ki, float kd){
	_kp = kp;
	_ki = ki;
	_kd = kd;
	
	_lastTime = millis();
}

void PID::setOutputMax(float max){
	_outMax = max;
}

void PID::setOutputMin(float min){
	_outMin = min;
}

float PID::getOutputMax(){
	return _outMax;
}

float PID::getOutputMin(){
	return _outMin;
}


float PID::compute(float input, float setPoint){

	// TODO:
	// float span = (_outputMax - _outputMin) / (_inputMax - _inputMin);

	float error;

	float p;
	float i;
	float d;
	float output = 0.0;
	
	long unsigned now = millis();
	long unsigned timeD = (now - _lastTime) / 1000; // Seconds since last computation

	// Run every second minute	
	if(timeD < 45){
		Serial.print("PID: No computation done");
		Serial.println();
		return _lastOutput;
	}
		
	// Beräkna felet
	error = setPoint - input;

	// Beräkna Proportionell del
	p = error;

	// Beräkna Integral
	// Addera aktuellt fel till summan för att få ytan under kurvan
	// iTerm = _ki * timeD * (error + iTerm);
	iTerm += error;
	
	if(iTerm > _outMax){
		iTerm = _outMax;
	}
	else if(iTerm < _outMin){
		iTerm = _outMin;
	}

	i = iTerm;
	
	// Beräkna Derivata dy/dx
	d = (input - _lastInput) / timeD;
	
	output = (p * _kp) + (i * _ki) - (d * _kd);

	if(output > _outMax){
		output = _outMax;
	}
	else if(output < _outMin){
		output = _outMin;
	}

	_lastInput = input;
	_lastError = error;
	_lastOutput = output;

	_lastP = p;
	_lastI = i;
	_lastD = d;
	
	_lastTime = now;

	Serial.print("PID: New value: ");
	Serial.print(output);
	Serial.println();

	Serial.print("PID: p=");
	Serial.print(p * _kp);
	Serial.print(" ");

	Serial.print("i=");
	Serial.print(i * _ki);
	Serial.print(" ");

	Serial.print("d=");
	Serial.print(d * _kd);

	Serial.println();

	return output;
}

long unsigned PID::getLastMeasureTime(){
	return _lastTime;
}
