#ifndef RIG_H
#define RIG_H

#include <iostream>
#include <utility>
#include <algorithm>
#include <stack>
#include <vector>
#include <limits>
#include <cmath>

using coord = std::pair<int, int>;
using coord_vector = std::vector<coord>;

class Rig 
{
    public:
        Rig(int);

        int num_points;
        coord_vector left_points;
        coord_vector right_points;
        coord_vector center_points;
        void make_rig(coord_vector&, coord_vector&, int);
    
};

#endif