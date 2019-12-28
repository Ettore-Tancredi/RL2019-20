#include <utility>

#include "Controller.h"
#include "debugging.h"

Controller::Controller()
{
  Kp = 10;
  Ki = 10;
  Kd = 10;
  E = 0;
  I = 0;

  MAX_X_VALUE = 400;
  MAX_Y_VALUE = 400;

  weights.resize(11);
  for (int i = 0; i < weights.size(); ++i)
    weights[i] = w(i);
}

Controller::Controller(double p, double i, double d, int num_points, double max_x_val, double max_y_val)
{
  Kp = p;
  Ki = i;
  Kd = d;
  E = 0;
  I = 0;

  weights.resize(num_points+1);
  for (int i = 0; i < weights.size(); ++i)
    weights[i] = w(i);

  MAX_X_VALUE = max_x_val;
  MAX_Y_VALUE = max_y_val;
}

int Controller::w(int n)
{
  return weights.size() - n;
}

double Controller::compress(double n)
{
  return n / (MAX_X_VALUE / 2);
}

/*****************************************************************************************
 * VOID TRANSFORM(COORD_VECTOR)
 * 
 *  - converts from the matrix coordinate system (0, 0) in the upper left corner,
 *    to the error coordinate system (0, 0) in the center of the lower side
  
 * *************************************************************************************/
void Controller::transform(coord_vector &points)
{
  for (int i = 0; i < points.size(); ++i)
  {
    std::swap(points[i].first, points[i].second);
    points[i].first -= MAX_X_VALUE / 2;
    points[i].second = MAX_Y_VALUE - points[i].second;
  }
}

int Controller::x_distance(int x1, int x2)
{
  return x1 - x2;
}


int Controller::correction(coord_vector points)
{
  transform(points);

  double E_prec = E;
  E = 0;

  int p = 0;
  for (int i = 0; i < points.size(); ++i)
  {
    E += weights[i] * compress(x_distance(points[i].first, 0));
    p += weights[i];
  }

  E /= p;

  if (E == 0)
    E_prec = 0, I = 0;
  P = E * Kp;
  I += E * Ki;
  D = (E - E_prec) * Kd;

  return P + I + D;
}
