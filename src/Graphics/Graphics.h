#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
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


enum 
{
    WHITE_G = 0,
    BLACK_G,
    GREEN_G,
    BLUE_G
};


class Graphics
{
    private:
        std::string windowName;
        BGR COLORS[4];

    public:
        Graphics(std::string);
        
        void draw(cv::Mat&);

        void outline(cv::Mat&, int[800][800], std::vector<std::pair<int, int> >&);
        void surface(cv::Mat&, int[800][800], Image&);
        void apply_rig(cv::Mat&, Rig);

};






