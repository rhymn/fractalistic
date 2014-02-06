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
    int getTemp();
    void measure();
    void printState();
    bool isError();
    void setEffect(int output, int, int, int, int, int, int);

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