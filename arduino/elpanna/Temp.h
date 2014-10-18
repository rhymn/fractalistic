#ifndef Elpanna_h
#define Elpanna_h

#include "Arduino.h"

class Elpanna{
  public:
    Elpanna(int thermistorPin);
    int getTemp();
    void measure();

   private:
    int getTempFromRes(float r);
    float getOhmFromThermistor();

    int _thermistorPin;

    int _temp;
    float _res;
};

#endif