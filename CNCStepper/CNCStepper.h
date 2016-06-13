#ifndef CNCStepper_H_
#define CNCStepper_H_

#include "Arduino.h"

class Motor
{
  int pin1, pin2, pin3, pin4;   
  long previous_time, current_time;
  int speed, finished, repetition, steps_cycle, count_cycle, motor_off, cycle, rest, sequencer, delimiter;
  public:
  Motor(int p1, int p2,int p3, int p4)
  {
    pin1=p1;
    pin2=p2;
    pin3=p3;
    pin4=p4;
    pinMode(pin1, OUTPUT);     
    pinMode(pin2,OUTPUT);  
    pinMode(pin3, OUTPUT);     
    pinMode(pin4,OUTPUT);  
    previous_time=0;
    current_time=0;
    speed=0;
    repetition=0;
    steps_cycle=0;
    finished=0;
    count_cycle=0;
    motor_off=0;
    cycle=0;
    sequencer=-1;
    rest=0;
    delimiter=0;
  }
  void move(int steps);
  void setSpeed(int _speed);
  int off();
  private: 
  void sequence(int n);
 };
#endif 