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
    coord_vector pixels_list;
    coord_vector vertexes;

public:
    Line();
    void clear();

    std::pair<int, int> barycentre;
    bool greenPos[2][2];

    int num_pixels();
    void add_px(coord);

    int num_vertexes();
    void add_vertex(coord);
    
    void show_data(); //DBG func
};

#endif