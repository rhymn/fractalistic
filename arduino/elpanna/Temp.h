#ifndef Temp_h
#define Temp_h

#include "Arduino.h"

class Temp{
  public:
    Temp(int thermistorPin);
    int getTemp();
    void measure();
    bool isError();

   private:
    int getTempFromRes(float r);
    float getOhmFromThermistor();

    int _thermistorPin;

    int _temp;
    float _res;

    bool _isErr;
};

#endif