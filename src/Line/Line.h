#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <utility>
#include <algorithm>
#include <stack>
#include <vector>

#include "cv_types.h"

class Line
{
    private:

    public:
        Line();
        void clear();
        
        std::pair<int, int> barycentre;
        int num_nodes;
        int num_corners;
        bool greenPos[2][2];

        coord_vector pixels_list;
        coord_vector vertexes;

        void show_data(); //DBG func
};

#endif 