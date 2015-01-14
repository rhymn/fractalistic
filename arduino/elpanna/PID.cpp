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
	
	_lastTime = -100000;

	_lastP = 0;
	_lastI = 0;
	_lastD = 0;
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

	// Run every second minute if set point hasn't changed
	if(setPoint == _lastSetPoint && timeD < 60){
		return _lastOutput;
	}
		
	// Beräkna felet
	error = setPoint - input;

	// Beräkna Proportionell del
	p = error;

	// Beräkna Integral
	// Addera aktuellt fel till summan för att få ytan under kurvan
	// iTerm = _ki * timeD * (error + iTerm);
	iTerm += timeD * 0.1 * error;
	
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

	_lastP = p * _kp;
	_lastI = i * _ki;
	_lastD = d * _kd;

	_lastSetPoint = setPoint;
	
	_lastTime = now;

	return output;
}


float PID::getLastP(){
	return _lastP;
}

float PID::getLastI(){
	return _lastI;
}

float PID::getLastD(){
	return _lastD;
}


long unsigned PID::getLastMeasureTime(){
	return _lastTime;
}
