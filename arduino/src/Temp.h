#ifndef Temp_h
#define Temp_h

#include "Arduino.h"

class Temp{
  public:
    Temp(int thermistorPin);
    int getTemp();
    void measure();
    bool isError();

    float getLastRes();
    int getLastRawTemp();

   private:
    int getTempFromRes(float r);
    float getOhm();

    int _thermistorPin;

    int _temp;
    int _lastRawTemp;

    float _res;
    float _lastRes;

    bool _isErr;
};

#endif