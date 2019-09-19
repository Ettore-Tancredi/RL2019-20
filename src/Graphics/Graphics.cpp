#include <string>
#include "Graphics.h"
#include "Image.h"
#include <vector>

Graphics::Graphics(std::string name)
{
    windowName = name;
    cv::namedWindow(windowName);

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

void Graphics::surface(cv::Mat &img, int visited[800][800], Image &image)
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
                        while(visited[i][j] == 1 || visited[i][j] == 3 && j < W)
                        {
                            img.at<cv::Vec3b>(i, j).val[0] = COLORS[BLACK_G].B;
                            img.at<cv::Vec3b>(i, j).val[1] = COLORS[BLACK_G].G;
                            img.at<cv::Vec3b>(i, j).val[2] = COLORS[BLACK_G].R;
                            ++j;
                        }

                        if(j < W && image.px_color(i, j) == BLACK)
                            color = BLACK_G;

                        --j;
                    }
                    else
                    {
                        color = WHITE_G;
                        while(visited[i][j] == 1 || visited[i][j] == 3 && j < W)
                        {
                            img.at<cv::Vec3b>(i, j).val[0] = COLORS[BLACK_G].B;
                            img.at<cv::Vec3b>(i, j).val[1] = COLORS[BLACK_G].G;
                            img.at<cv::Vec3b>(i, j).val[2] = COLORS[BLACK_G].R;
                            ++j;
                        }

                        if(j < W && image.px_color(i, j) == BLACK)
                            color = BLACK_G;

                        --j;
                    }
                    break;
                case 2:
                    break;
                case 3:
                    if(color != BLACK_G)
                    {
                        while(visited[i][j] == 1 || visited[i][j] == 3 && j < W)
                        {
                            img.at<cv::Vec3b>(i, j).val[0] = COLORS[BLACK_G].B;
                            img.at<cv::Vec3b>(i, j).val[1] = COLORS[BLACK_G].G;
                            img.at<cv::Vec3b>(i, j).val[2] = COLORS[BLACK_G].R;
                            ++j;
                        }

                        if(j < W && image.px_color(i, j) == BLACK)
                            color = BLACK_G;

                        --j;
                    }
                    else
                    {
                        color = WHITE_G;
                        while(visited[i][j] == 1 || visited[i][j] == 3 && j < W)
                        {
                            img.at<cv::Vec3b>(i, j).val[0] = COLORS[BLACK_G].B;
                            img.at<cv::Vec3b>(i, j).val[1] = COLORS[BLACK_G].G;
                            img.at<cv::Vec3b>(i, j).val[2] = COLORS[BLACK_G].R;
                            ++j;
                        }

                        if(j < W && image.px_color(i, j) == BLACK)
                            color = BLACK_G;

                        --j;
                    }
                    break;
                default:
                    if(color != GREEN_G)
                    {
                        while(visited[i][j] > 3 && j < W)
                        {
                            img.at<cv::Vec3b>(i, j).val[0] = COLORS[GREEN_G].B;
                            img.at<cv::Vec3b>(i, j).val[1] = COLORS[GREEN_G].G;
                            img.at<cv::Vec3b>(i, j).val[2] = COLORS[GREEN_G].R;
                            ++j;
                        }

                        if(j < W && image.px_color(i, j) == GREEN)
                            color = GREEN;

                        --j;
                    }
                    else
                    {
                        color = WHITE_G;
                        while(visited[i][j] > 3  && j < W)
                        {
                            img.at<cv::Vec3b>(i, j).val[0] = COLORS[GREEN_G].B;
                            img.at<cv::Vec3b>(i, j).val[1] = COLORS[GREEN_G].G;
                            img.at<cv::Vec3b>(i, j).val[2] = COLORS[GREEN_G].R;
                            ++j;
                        }

                        if(j < W && image.px_color(i, j) == GREEN)
                            color = GREEN_G;

                        --j;
                    }
                    break;
                    
            } 
        }
    }

}

void Graphics::outline(cv::Mat &img, int visited[800][800], std::vector<std::pair<int, int>  >&green)
{
    const int H = img.rows;
    const int W = img.cols;

    
    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            if (visited[i][j] == 1)
            {
                img.at<cv::Vec3b>(i, j).val[0] = COLORS[BLACK_G].B;
                img.at<cv::Vec3b>(i, j).val[1] = COLORS[BLACK_G].G;
                img.at<cv::Vec3b>(i, j).val[2] = COLORS[BLACK_G].R;
            }
            else if (visited[i][j] == 4)
            {
                img.at<cv::Vec3b>(i, j).val[0] = COLORS[GREEN_G].B;
                img.at<cv::Vec3b>(i, j).val[1] = COLORS[GREEN_G].G;
                img.at<cv::Vec3b>(i, j).val[2] = COLORS[GREEN_G].R;
            }
        }
    }

    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            if (visited[i][j] == 3)
            {
                img.at<cv::Vec3b>(i, j).val[0] = COLORS[WHITE_G].B;
                img.at<cv::Vec3b>(i, j).val[1] = COLORS[WHITE_G].G;
                img.at<cv::Vec3b>(i, j).val[2] = COLORS[WHITE_G].R;

                for (int c = -1; c < 2; ++c)
					for (int t = -1; t < 2; ++t)
                        {
                            if (i + c >= 0 && i + c < H && j + t >= 0 && j + t < W)
                            {
                                img.at<cv::Vec3b>(i+c, j+t).val[0] = COLORS[WHITE_G].B;
                                img.at<cv::Vec3b>(i+c, j+t).val[1] = COLORS[WHITE_G].G;
                                img.at<cv::Vec3b>(i+c, j+t).val[2] = COLORS[WHITE_G].R;
                            }
                        }
            }
        }
    }


    if (!green.empty())
    {
        for(auto i: green)
        {
            img.at<cv::Vec3b>(i.first, i.second).val[0] = COLORS[BLACK_G].B;
            img.at<cv::Vec3b>(i.first, i.second).val[1] = COLORS[BLACK_G].G;
            img.at<cv::Vec3b>(i.first, i.second).val[2] = COLORS[BLACK_G].R;

            for (int c = -1; c < 2; ++c)
				for (int t = -1; t < 2; ++t)
                {
                    if (i.first + c >= 0 && i.first + c < H && i.second + t >= 0 && i.second + t < W)
                    {
                        img.at<cv::Vec3b>(i.first+c, i.second+t).val[0] = COLORS[BLACK_G].B;
                        img.at<cv::Vec3b>(i.first+c, i.second+t).val[1] = COLORS[BLACK_G].G;
                        img.at<cv::Vec3b>(i.first+c, i.second+t).val[2] = COLORS[BLACK_G].R;
                    }
                }
        }
    }

}