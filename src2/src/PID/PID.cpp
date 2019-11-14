#include "PID.h"

PID::PID()
{
  Kp = 10;
  Ki = 10;
  Kd = 10;
  E = 0;
  I = 0;

  for (int i = 0; i < 6; ++i)
    weights[i] = w(i);
}

PID::PID(double p, double i, double d)
{
  Kp = p;
  Ki = i;
  Kd = d;
  E = 0;
  I = 0;

  for (int i = 0; i < 6; ++i)
    weights[i] = w(i);

}

int PID::w(int n)
{
    return 6 - n;
}


int PID::pid(int *slopes)
{
  double E_prec=E;
  E = 0;

  int p = 0;
  for (int i = 0; i < 6; ++i)
  {
      E += weights[i]*slopes[i];
      p += weights[i];
  }
  
  E /= p;
  
  if(E == 0)
    E_prec = 0, I = 0;
  P = E * Kp;
  I += E * Ki;
  D = (E - E_prec) * Kd;

  return P + I + D;
}
