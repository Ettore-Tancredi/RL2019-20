#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <utility>
#include <algorithm>

class Line
{
    private:

    public:
        Line();
        
        std::pair<int, int> barycentre;
        int num_nodes;
        int num_corners;

};

#endif 