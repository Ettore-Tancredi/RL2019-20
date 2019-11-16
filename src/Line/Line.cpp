#include "Line.h"

Line::Line()
{
    num_nodes = 0;
    barycentre.first = 0;
    barycentre.second = 0;
    num_corners = 0;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            greenPos[i][j] = false;
}

void Line::clear()
{
    num_nodes = 0;
    barycentre.first = 0;
    barycentre.second = 0;
    num_corners = 0;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            greenPos[i][j] = false;

    pixels_list.clear();
}

void Line::show_data()
{
    std::cout << "Number of line pixels:  " << pixels_list.size() << std::endl;
    std::cout << "Number of vertixes:    " << num_corners << std::endl;

    std::cout << "Green regions location: \n";
    int num_G_regions = 0;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            std::cout << greenPos[i][j] << " ";
            num_G_regions += greenPos[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "Number of green regions: " << num_G_regions << std::endl;
    std::cout << std::endl;
}