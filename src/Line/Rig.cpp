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
    if (paired_vertexes[0].first.first < paired_vertexes[1].first.first)
        std::swap(paired_vertexes[0], paired_vertexes[1]);

    if (paired_vertexes[0].first.second > paired_vertexes[0].second.second)
        std::swap(paired_vertexes[0].first, paired_vertexes[0].second);

    //sistemare con sides touched, ora funziona solo per lato sinistro
    if (paired_vertexes[1].first.second < paired_vertexes[1].second.second)
        std::swap(paired_vertexes[1].first, paired_vertexes[1].second);
    if (paired_vertexes[1].first.first > paired_vertexes[1].second.first)
        std::swap(paired_vertexes[1].first, paired_vertexes[1].second);

    // for (int i = 0; i < 2; ++i)
    //     debug::printCoordP(paired_vertexes[i], ' ');
    // std::cout << std::endl;

    int pos0 = line.find_px(paired_vertexes[0].first);
    int pos1 = line.find_px(paired_vertexes[0].second);
    int pos2 = line.find_px(paired_vertexes[1].first);
    int pos3 = line.find_px(paired_vertexes[1].second);

    // std:: cout << pos0 << " " << pos1 << " "<< pos2 << " "<< pos3 << " " << std::endl;

    int right_side =  abs(pos2 - pos1); 
    int left_side =  line.num_pixels() - pos3;    
    // std::cout << right_side   << " " << left_side;

    int right_jump = right_side / num_points;
    int left_jump = left_side / num_points;
    for (int i = 0; i < num_points; ++i)
    {
        int right_i = pos1 + right_jump * i;
       // int left_i = line.num_pixels() - left_jump * i;
         //coord avg = medium(line.get_px(right_i), line.get_px(left_i));
        center_points[i] = line.get_px(right_i)/*avg*/;
    }
}