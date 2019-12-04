#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <iostream>
#include <utility>
#include "cv_types.h"


/***********************************************************
  THIS FILE CONTAINS GENERAL PURPOSE DEBUGGING FUNCTIONS:
    - PRINT COORD (A, B)
    - PRINT PAIR OF COORD (A, B) (C, D)



************************************************************/

namespace debug
{
    void printCoord(coord a)
    {
        std::cout << "(" << a.first << ", " << a.second << ")";
    }

    void printCoordP(std::pair<coord, coord> a)
    {
        std::cout << "(" << a.first.first << ", " << a.first.second << ")   (" << a.second.first << ", " << a.second.second << ")";
    }
    
}


				





#endif