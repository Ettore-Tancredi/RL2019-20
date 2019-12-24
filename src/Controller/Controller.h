#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>

#include "cv_types.h"

class Controller
{
private:
  double Kp, Ki, Kd;
  double P, I, D, E;
  double MAX_X_VALUE, MAX_Y_VALUE;

  void transform(coord_vector &);

  std::vector<int> weights;
  int w(int);

  double compress(double);
  int x_distance(int, int);

public:
  Controller();
  Controller(double, double, double, int, double, double);
  int correction(coord_vector);
};

#endif
