#include "Line.h"


Line::Line()
{
    num_nodes = 0;
    barycentre.first = 0;
    barycentre.second = 0;
    num_corners = 0;
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)
            greenPos[i][j] = false;
}

void Line::clear()
{
    num_nodes = 0;
    barycentre.first = 0;
    barycentre.second = 0;
    num_corners = 0;
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)
            greenPos[i][j] = false;

    pixels_list.clear();
}
