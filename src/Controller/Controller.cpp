#include <utility>

#include "Controller.h"

Controller::Controller()
{
  Kp = 10;
  Ki = 10;
  Kd = 10;
  E = 0;
  I = 0;

  MAX_X_VALUE = 400;
  MAX_Y_VALUE = 400;

  weights.resize(10);
  for (int i = 0; i < weights.size(); ++i)
    weights[i] = w(i);

  slopes.resize(10);
  distances.resize(10);
}

Controller::Controller(double p, double i, double d, int num_points, double max_x_val, double max_y_val)
{
  Kp = p;
  Ki = i;
  Kd = d;
  E = 0;
  I = 0;

  weights.resize(num_points);
  for (int i = 0; i < weights.size(); ++i)
    weights[i] = w(i);

  slopes.resize(num_points);
  distances.resize(num_points);

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

double Controller::slope(double d_x, double d_y)
{
  if (d_y == 0)
    return 1;
  else
    return d_x / d_y;
}

void Controller::transform(coord_vector &points)
{
  for (int i = 0; i < points.size(); ++i)
  {
    std::swap(points[i].first, points[i].second);
    points[i].first -= MAX_X_VALUE / 2;
    points[i].second = MAX_Y_VALUE - points[i].second;
  }
}

int Controller::correction(coord_vector points)
{
  transform(points);
  for (int i = 0; i < points.size() - 1; ++i)
    slopes[i] = slope(points[i + 1].first - points[i].first, points[i + 1].second - points[i].second);
  for (int i = 0; i < points.size() - 1; ++i)
    distances[i] = (points[i + 1].first + points[i].first) / 2;

  double E_prec = E;
  E = 0;

  int p = 0;
  for (int i = 0; i < slopes.size(); ++i)
  {
    E += weights[i] * (slopes[i] + distances[i]);
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
