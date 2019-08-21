#include <string>
#include "Graphics.h"


Graphics::Graphics(std::string name)
{
    windowName = name;
   // cv::namedWindow(windowName);

    Graphics::COLORS[WHITE_G].B = 0;
    Graphics::COLORS[WHITE_G].G = 255;
    Graphics::COLORS[WHITE_G].R = 255;

    Graphics::COLORS[BLACK_G].B = 0;
    Graphics::COLORS[BLACK_G].G = 0;
    Graphics::COLORS[BLACK_G].R = 255;

    Graphics::COLORS[GREEN_G].B = 255;
    Graphics::COLORS[GREEN_G].G = 0;
    Graphics::COLORS[GREEN_G].R = 0;
}

void Graphics::draw(cv::Mat &img)
{
    cv::imshow(windowName, img);
}

void Graphics::process(cv::Mat &img, int visited[800][800])
{
    const int H = img.rows;
    const int W = img.cols;

    int color;

    for(int i = 0; i < H; i += 5)
    {
        color = WHITE_G;
        for(int j = 0; j < W; ++j)
        {
            switch (visited[i][j])
            {
                case 0:
                    img.at<cv::Vec3b>(i, j).val[0] = COLORS[color].B;
                    img.at<cv::Vec3b>(i, j).val[1] = COLORS[color].G;
                    img.at<cv::Vec3b>(i, j).val[2] = COLORS[color].R;
                    break;
                case 1:
                    if(color != BLACK_G)
                    {
                        color = BLACK_G;
                        img.at<cv::Vec3b>(i, j).val[0] = COLORS[color].B;
                        img.at<cv::Vec3b>(i, j).val[1] = COLORS[color].G;
                        img.at<cv::Vec3b>(i, j).val[2] = COLORS[color].R;
                    }
                    else
                    {
                        color = WHITE_G;
                        img.at<cv::Vec3b>(i, j).val[0] = COLORS[BLACK_G].B;
                        img.at<cv::Vec3b>(i, j).val[1] = COLORS[BLACK_G].G;
                        img.at<cv::Vec3b>(i, j).val[2] = COLORS[BLACK_G].R;
                    }
                    break;
                default:
                    if(color != GREEN_G)
                    {
                        color = GREEN_G;
                        img.at<cv::Vec3b>(i, j).val[0] = COLORS[color].B;
                        img.at<cv::Vec3b>(i, j).val[1] = COLORS[color].G;
                        img.at<cv::Vec3b>(i, j).val[2] = COLORS[color].R;
                    }
                    else
                    {
                        color = WHITE_G;
                        img.at<cv::Vec3b>(i, j).val[0] = COLORS[GREEN_G].B;
                        img.at<cv::Vec3b>(i, j).val[1] = COLORS[GREEN_G].G;
                        img.at<cv::Vec3b>(i, j).val[2] = COLORS[GREEN_G].R;
                    }
                    break;
                    
            }
        }
    }

}