#ifndef RIG_H
#define RIG_H

#include <iostream>
#include <utility>
#include <algorithm>
#include <stack>
#include <vector>
#include <limits>
#include <cmath>

#include "Line.h"
#include "cv_types.h"

class Rig
{

public:
    Rig(int);
    int num_points;
    coord_vector center_points;
    void make_rig(Line &, coord_pair_vector);
};

#endif