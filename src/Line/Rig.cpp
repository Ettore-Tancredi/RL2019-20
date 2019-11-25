#include "Rig.h"

Rig::Rig(int points)
{
    num_points = points;
    left_points.resize(num_points);
    right_points.resize(num_points);
    center_points.resize(num_points);
}

double euclid_distance(coord p1, coord p2)
{
    double i = p1.first * p2.first;
    double j = p1.first * p2.first;
    return sqrt(i+j);
}


void Rig::make_rig(Line &line)
{


}