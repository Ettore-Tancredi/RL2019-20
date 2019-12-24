#include "Rig.h"
#include "debugging.h"

coord medium(coord, coord);


Rig::Rig(int points)
{
    num_points = points;
    center_points.resize(num_points + 1);
}

bool comp_coord(coord a, coord b)
{
    if (a.first == b.first)
        return a.second > b.second;
    else
        return a.first > b.first;
}

bool comp_func(coord_pair a, coord_pair b)
{
    return (!comp_coord(medium(a.first, a.second), medium(b.first, b.second)));
}

void Rig::make_rig(Line &line, coord_pair_vector paired_vertexes)
{
    int pos[4];
    pos[0] = line.find_px(paired_vertexes[0].first);
    pos[1] = line.find_px(paired_vertexes[0].second);
    pos[2] = line.find_px(paired_vertexes[1].first);
    pos[3] = line.find_px(paired_vertexes[1].second);

    std::sort(pos, pos + 4);

    int right_side = abs(pos[2] - pos[1]);
    int left_side = line.num_pixels() - pos[3];

    int right_jump = right_side / num_points;
    int left_jump = left_side / num_points;
    for (int i = 0; i <= num_points; ++i)
    {
        int right_i = pos[1] + right_jump * i;
        int left_i = line.num_pixels() - left_jump * i - 1;
        coord avg = medium(line.get_px(right_i), line.get_px(left_i));
        center_points[i] = avg;
    }

}