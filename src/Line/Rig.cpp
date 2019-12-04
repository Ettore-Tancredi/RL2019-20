#include "Rig.h"

#include "debugging.h"

Rig::Rig(int points)
{
    num_points = points;
    center_points.resize(num_points);
}

bool comp_coord(coord a, coord b)
{
    if (a.first == b.first)
        return a.second > b.second;
    else 
        return a.first > b.first;
}

coord medium(coord a, coord b)
{
    return {(a.first + b.first)/2, (a.second + b.second)/2};
}

bool comp_func(coord_pair a, coord_pair b)
{
    return (!comp_coord(medium(a.first, a.second), medium(b.first, b.second)));
}

void Rig::make_rig(Line &line, coord_pair_vector paired_vertexes)
{
    for (int i = 0; i < paired_vertexes.size(); ++i)
    {
        if (comp_coord(paired_vertexes[i].first, paired_vertexes[i].second))
            std::swap(paired_vertexes[i].first, paired_vertexes[i].second);
    }
    if (comp_func(paired_vertexes[0], paired_vertexes[1]))
            std::swap(paired_vertexes[0], paired_vertexes[1]);

    int pos0 = line.find_px(paired_vertexes[0].second);
    int pos1 = line.find_px(paired_vertexes[1].second);
    int pos2 = line.find_px(paired_vertexes[1].first);
    int pos3 = line.find_px(paired_vertexes[0].first);
    int right_side =  pos1 - pos0; 
    int left_side =  pos3 - pos2;
    int right_jump = right_side / num_points;
    int left_jump = left_side / num_points;
    for (int i = 0; i < num_points; ++i)
    {
        int right_i = pos0 + right_jump * i;
        int left_i = pos2 + left_jump * i;
        coord avg = medium(line.get_px(right_i), line.get_px(left_i));
        center_points.push_back(avg);
    }

}