#include "Debugging.h"

void printCoord(coord a, char end)
{
    std::cout << "(" << a.first << ", " << a.second << ")" << end;
}

void printCoordP(std::pair<coord, coord> a, char end)
{
    std::cout << "[(" << a.first.first << ", " << a.first.second << ") (" << a.second.first << ", " << a.second.second << ")]" << end;
}