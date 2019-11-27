#include "Rig.h"

Rig::Rig(int points)
{
    num_points = points;
    left_points.resize(num_points);
    right_points.resize(num_points);
    center_points.resize(num_points);
}


void Rig::make_rig(Line &line)
{


}