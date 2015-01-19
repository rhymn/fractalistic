/*
  PID.h - Library for ..
  Created by David 27 may 2013.
  Released into the public domain.
*/

#ifndef PID_h
#define PID_h

class PID{
  public:
    PID(float kp, float ki, float kd);
    void setOutputMin(float);
    void setOutputMax(float);

    float getOutputMin();
    float getOutputMax();

    float compute(float input, float setPoint);

    float getLastP();
    float getLastI();
    float getLastD();

    long unsigned getLastMeasureTime();

   private:
    float _kp;
    float _ki;
    float _kd;

    float _input;
    float _output;
    float _setPoint;

    float _lastError;
    float _lastInput;
    float _lastOutput;
    float _lastSetPoint;

    long unsigned _lastTime;
    float iTerm;

    int _outMin;
    int _outMax;

    float _lastP, _lastI, _lastD;

};

#endif