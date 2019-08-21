#include <vector>
#include <iostream> //debug purposes
#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>  

#ifndef IMAGE_H
#define IMAGE_H


const int MAX_DIM = 800;


enum
{
    NORMAL_PIXEL = 1,
    CORNER_PIXEL,
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
    std::vector<char>regions;

public:
    Image(int, int);

    int visited[MAX_DIM][MAX_DIM];

    void clear();
    
    int height();
    int width();
    Colors px_color(int, int);
    cv::Mat& getImage();
    cv::Mat copy();


    int num_regions();
    int count_regions_of_type(char);
    void add_region(char);
    bool find_region(char);


    int matchesTarget(int, int);
    bool is_inside(int, int);

    void get_debug_color(int, int, int &, int &, int &);

    void load_data();
};


#endif