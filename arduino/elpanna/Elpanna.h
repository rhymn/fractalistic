/*
  Elpanna.h - Library for ..
  Created may 2013.
  Released into the public domain.
*/

#ifndef Elpanna_h
#define Elpanna_h

#include "Arduino.h"

class Elpanna{
  public:
    Elpanna(int desiredTemp, int okLED, int errLED, int thermistorPin);
    int getDesiredTemp();
    void setDesiredTemp(int desiredTemp);
    int getTemp();
    void measure();
    bool isError();

   private:
    int getTempFromRes(float r);
    float getOhmFromThermistor();

    int _desiredTemp;

    int _errLED;
    int _okLED;

    int _thermistorPin;

    int _temp;
    float _res;

    bool _isErr;

    int _kp;
    int _ki;
    int _kd;

    float _lastError;
    float _lastInput;
    long unsigned _lastTime;
};

#endif