#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <utility>
#include <algorithm>
#include <stack>
#include <vector>

#include "cv_types.h"

enum LineType
{
    UNKNOWN = 0,
    INTERRUPT,
    STD_LINE,
    T_INTERSECTION,
    C_INTERSECTION
};

class Line
{
private:
    coord_vector pixels_list;
    std::map<coord, int> pixels_map;
    std::multimap<int, coord> pixels_multimap;

    coord_vector vertexes;

    int type;

public:
    Line();
    void clear();

    std::pair<int, int> barycentre;
    bool greenPos[2][2];

    int num_pixels();
    void add_px(coord);
    int find_px(coord);
    coord get_px(int);
    coord_vector getPixelsList();

    void new_px(coord, coord);
    int found_pixels();
    void sort_pixels();

    int num_vertexes();
    void add_vertex(coord);
    coord_vector getVertexes();

    void setType(int);
    int getType();

    void show_data(); //DBG func
};

#endif