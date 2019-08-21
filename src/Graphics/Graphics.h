#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

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
    GREEN_G
};


class Graphics
{
    private:
        std::string windowName;
        BGR COLORS[3];

    public:
        Graphics(std::string);
        
        void draw(cv::Mat&);

        void process(cv::Mat&, int[800][800]);
};






