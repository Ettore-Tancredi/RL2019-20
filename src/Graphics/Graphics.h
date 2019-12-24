#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include "Image.h"
#include <vector>
#include <utility>
#include "Rig.h"

struct BGR
{
    int B;
    int G;
    int R;
};

enum Graphics_colors
{
    G_YELLOW = 0,
    G_RED,
    G_BLUE,
    G_GREEN,
    G_CYAN
};

class Graphics
{
private:
    std::string windowName;
    BGR COLORS[5];

    void join_ends(cv::Mat &, coord, coord, int);

public:
    Graphics(std::string);

    void draw(cv::Mat &);

    void outline(cv::Mat &, int[800][800], coord_vector &);
    void surface(cv::Mat &, int[800][800], Image &);
    void apply_rig(cv::Mat &, Rig);
    void make_hull(std::vector<std::pair<coord, coord>>, cv::Mat &);
    void apply_order(cv::Mat &, coord_vector);
};

#endif