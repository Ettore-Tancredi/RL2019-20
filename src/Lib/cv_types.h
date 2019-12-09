#ifndef CV_TYPES
#define CV_TYPES

#include <utility>
#include <iostream>
#include <stack>
#include <utility>
#include <chrono>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using coord = std::pair<int, int>;
using coord_vector = std::vector<coord>;
using coord_pair = std::pair<coord, coord>;
using coord_pair_vector = std::vector<coord_pair>;

using map_it = std::map<coord, int>::iterator;
using multimap_it = std::multimap<int, coord>::iterator;


#endif