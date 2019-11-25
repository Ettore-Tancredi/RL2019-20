#ifndef PID_H
#define PID_H

#include <vector>


class PID{
  private:
    double Kp, Ki, Kd;
    double P, I, D, E;
    std::vector<int>weights;
    int w(int);
    
  public:
    PID();
    PID(double, double, double, int);
    int pid(std::vector<int>);
};

#endif

