#ifndef PID_H
#define PID_H

class PID{
  private:
    double Kp, Ki, Kd;
    double P, I, D, E;
    int weights[6];
    int w(int);
    
  public:
    PID();
    PID(double, double, double);
    int pid(int*);
};

#endif

