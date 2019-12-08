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

  std::vector<int> weights;
  int w(int);

  void transform(coord_vector &);
  double compress(double);
  std::vector<double> slopes;
  double slope(double, double);
  std::vector<double> distances;

public:
  Controller();
  Controller(double, double, double, int, double, double);
  int correction(coord_vector);
};

#endif
