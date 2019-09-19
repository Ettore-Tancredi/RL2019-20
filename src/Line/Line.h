#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <utility>
#include <algorithm>
#include <stack>
#include <vector>

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
        std::vector< std:pair<int, int> > corners;

};

#endif 