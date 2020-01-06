#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <iostream> //debug purposes
#include <string>
#include <fstream>
#include <stack>
#include <opencv2/opencv.hpp>

#include "cv_types.h"

const int MAX_DIM = 800;

enum
{
    NORMAL_PIXEL = 1,
    VERTEX_PIXEL,
};

enum Colors
{
    WHITE = 0,
    BLACK,
    GREEN,
    SILVER,
};

class Image
{
private:
    int H, W;

    cv::Mat image;
    std::vector<char> regions;

public:
    Image(int, int); //ARG: HEIGHT, WIDTH

    int visited[MAX_DIM][MAX_DIM];
    std::stack<coord> green_pixels;
    coord_vector green_regions;

    int height();
    int width();
    bool bounds(int, int);
    cv::Mat &handle(); //note: if you want an actual copy of the image, call .clone() on the return value
    Colors px_color(int, int);

    void add_region(char);
    bool find_region(char);
    int count_regions(char);
    int num_regions();


    int matchesTarget(int, int);
    bool matchesGreenTarget(int, int);
    
    void clear();

    void load_data(std::string);
};

#endif