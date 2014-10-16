/*
  Heater.h - Library for ..
  Created may 2013.
  Released into the public domain.
*/

#ifndef Heater_h
#define Heater_h

#include "Arduino.h"

class Heater{
  public:
		Heater(int, int, int, int, int, int);
		void setEffect(int output);

	private:
		int _one;
		int _two;
		int _three;
		int _four;
		int _five;
		int _six;
};

#endif