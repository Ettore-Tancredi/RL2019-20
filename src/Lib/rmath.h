#include "types.h"


double euclid_dist(int i1, int j1, int i2, int j2)
{
	return sqrt(double((i1 - i2)*(i1 - i2) + (j1 -j2)*(j1 - j2)));
}


