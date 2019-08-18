#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <iostream> //debug purposes
#include <string>
#include <fstream>

#include "Pixel.h"
#include "Line.h"


class Image
{
private:
    static const int H = 200;
    static const int W = 200;

    Pixel val[H][W];
    void filter(int, int);
    Colors mostFrequentNeightbour(int, int );
    std::vector<char>regions;

    std::vector<coord> green_pixels;

public:
    void copy(int mat[H][W][4]);
   // void load_training_data(std::string);
    int visited[H][W];
    int height();
    int width();
    bool is_inside(int, int);

    Colors px_color(int, int);
    bool isValid(int, int, int);

    int num_regions();
    bool find_region(char);
    int count_regions(char);
    void add_region(char);

    int num_G_pixels();
    void add_px(int, int);
    int green_regions;

    coord Gpx_coord(int);

    void get_debug_color(int, int, int &, int &, int &);
};
