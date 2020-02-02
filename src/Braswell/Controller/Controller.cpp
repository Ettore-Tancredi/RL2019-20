#include <utility>

#include "Controller.h"
#include "Debugging.h"

Controller::Controller()
{
  Kp = 10;
  Ki = 10;
  Kd = 10;
  E = 0;
  I = 0;

  NUM_POINTS = 10;
  MAX_VALUE = 200;
}

Controller::Controller(double p, double i, double d, int num_points, double max_val)
{
  Kp = p;
  Ki = i;
  Kd = d;
  E = 0;
  I = 0;

  NUM_POINTS = num_points;
  MAX_VALUE = max_val;
}


int Controller::w(int i)
{
  return NUM_POINTS - i;
}

double Controller::compress(double n)
{
  return n / (MAX_VALUE);
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
    points[i].first -= MAX_VALUE;
    points[i].second = 2*MAX_VALUE - points[i].second;
  }
}

int Controller::x_distance(int x1, int x2)
{
  return x1 - x2;
}

double Controller::error(coord_vector points)
{
  transform(points);
  double e = 0;
  int p = 0;
  for (int i = 0; i < points.size(); ++i)
  {
    e += w(i) * compress(points[i].first);
    p += w(i);
  }

  e /= p;

  return e;
}

int Controller::correction(coord_vector points)
{
  double E_prec = E;

  E = error(points);

  if (E == 0)
    E_prec = 0, I = 0;
  P = E * Kp;
  I += E * Ki;
  D = (E - E_prec) * Kd;

  return P + I + D;
}