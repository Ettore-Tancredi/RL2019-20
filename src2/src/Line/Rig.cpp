#include "Rig.h"


Rig::Rig(int points)
{
    num_points = points;
    left_points.resize(num_points);
    right_points.resize(num_points);
    center_points.resize(num_points);
}

double distance(coord p1, coord p2)
{
    double i = pow(p1.first + p2.first, 2);
    double j = pow(p1.first + p2.first, 2);
    return sqrt(i+j);
}


void Rig::make_rig(coord_vector &pixels_list,  coord_vector &corners_list, int num_nodes)
{
    double min_distance = std::numeric_limits<double>::max();
    int index_min;  

    for(int i = 1; i < corners_list.size(); ++i)
    {
        if (distance(corners_list[0], corners_list[i]) < min_distance)
        {
            min_distance = distance(corners_list[0], corners_list[i]);
            index_min = i;
        }
    }

    std::vector<std::pair<coord, coord> > CP_pair;
    CP_pair.push_back(std::pair<coord, coord>(corners_list[0], corners_list[index_min]));
    corners_list.erase(corners_list.begin()+index_min);
    corners_list.erase(corners_list.begin());
    CP_pair.push_back(std::pair<coord, coord>(corners_list[0], corners_list[1]));







}