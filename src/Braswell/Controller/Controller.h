#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>

#include "cv_types.h"

class Controller
{
private:
  double Kp, Ki, Kd;
  double P, I, D, E;
  int NUM_POINTS;
  double MAX_VALUE;

  void transform(coord_vector &);

  int w(int);

  double compress(double);
  double error(coord_vector);

public:
  Controller();
  Controller(double, double, double, int, double);
  int correction(coord_vector);
};

#endif
