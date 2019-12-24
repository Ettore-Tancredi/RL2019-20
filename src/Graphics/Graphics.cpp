#include <string>
#include "Graphics.h"
#include "Image.h"
#include "Rig.h"
#include "cv_types.h"
#include <vector>

Graphics::Graphics(std::string name)
{
    windowName = name;
    cv::namedWindow(windowName);

    Graphics::COLORS[G_YELLOW].B = 0;
    Graphics::COLORS[G_YELLOW].G = 255;
    Graphics::COLORS[G_YELLOW].R = 255;

    Graphics::COLORS[G_RED].B = 0;
    Graphics::COLORS[G_RED].G = 0;
    Graphics::COLORS[G_RED].R = 255;

    Graphics::COLORS[G_BLUE].B = 255;
    Graphics::COLORS[G_BLUE].G = 0;
    Graphics::COLORS[G_BLUE].R = 0;

    Graphics::COLORS[G_GREEN].B = 51;
    Graphics::COLORS[G_GREEN].G = 255;
    Graphics::COLORS[G_GREEN].R = 0;

    Graphics::COLORS[G_CYAN].B = 255;
    Graphics::COLORS[G_CYAN].G = 255;
    Graphics::COLORS[G_CYAN].R = 0;
}

void Graphics::draw(cv::Mat &img)
{
    cv::imshow(windowName, img);
}

void Graphics::join_ends(cv::Mat &frame, coord a, coord b, int color = G_GREEN)
{
    cv::line(frame, cv::Point(a.second, a.first), cv::Point(b.second, b.first), cv::Scalar(COLORS[color].B, COLORS[color].G, COLORS[color].R));
}

void Graphics::surface(cv::Mat &img, int visited[800][800], Image &image)
{
    const int H = img.rows;
    const int W = img.cols;

    int color;

    for (int i = 0; i < H; i += 5)
    {
        color = G_YELLOW;
        for (int j = 0; j < W; ++j)
        {
            switch (visited[i][j])
            {
            case 0:
                img.at<cv::Vec3b>(i, j).val[0] = COLORS[color].B;
                img.at<cv::Vec3b>(i, j).val[1] = COLORS[color].G;
                img.at<cv::Vec3b>(i, j).val[2] = COLORS[color].R;
                break;
            case 1:
                if (color != G_RED)
                {
                    while (visited[i][j] == 1 || visited[i][j] == 3 && j < W)
                    {
                        img.at<cv::Vec3b>(i, j).val[0] = COLORS[G_RED].B;
                        img.at<cv::Vec3b>(i, j).val[1] = COLORS[G_RED].G;
                        img.at<cv::Vec3b>(i, j).val[2] = COLORS[G_RED].R;
                        ++j;
                    }

                    if (j < W && image.px_color(i, j) == BLACK)
                        color = G_RED;

                    --j;
                }
                else
                {
                    color = G_YELLOW;
                    while (visited[i][j] == 1 || visited[i][j] == 3 && j < W)
                    {
                        img.at<cv::Vec3b>(i, j).val[0] = COLORS[G_RED].B;
                        img.at<cv::Vec3b>(i, j).val[1] = COLORS[G_RED].G;
                        img.at<cv::Vec3b>(i, j).val[2] = COLORS[G_RED].R;
                        ++j;
                    }

                    if (j < W && image.px_color(i, j) == BLACK)
                        color = G_RED;

                    --j;
                }
                break;
            case 2:
                break;
            case 3:
                if (color != G_RED)
                {
                    while (visited[i][j] == 1 || visited[i][j] == 3 && j < W)
                    {
                        img.at<cv::Vec3b>(i, j).val[0] = COLORS[G_RED].B;
                        img.at<cv::Vec3b>(i, j).val[1] = COLORS[G_RED].G;
                        img.at<cv::Vec3b>(i, j).val[2] = COLORS[G_RED].R;
                        ++j;
                    }

                    if (j < W && image.px_color(i, j) == BLACK)
                        color = G_RED;

                    --j;
                }
                else
                {
                    color = G_YELLOW;
                    while (visited[i][j] == 1 || visited[i][j] == 3 && j < W)
                    {
                        img.at<cv::Vec3b>(i, j).val[0] = COLORS[G_RED].B;
                        img.at<cv::Vec3b>(i, j).val[1] = COLORS[G_RED].G;
                        img.at<cv::Vec3b>(i, j).val[2] = COLORS[G_RED].R;
                        ++j;
                    }

                    if (j < W && image.px_color(i, j) == BLACK)
                        color = G_RED;

                    --j;
                }
                break;
            default:
                if (color != G_BLUE)
                {
                    while (visited[i][j] > 3 && j < W)
                    {
                        img.at<cv::Vec3b>(i, j).val[0] = COLORS[G_BLUE].B;
                        img.at<cv::Vec3b>(i, j).val[1] = COLORS[G_BLUE].G;
                        img.at<cv::Vec3b>(i, j).val[2] = COLORS[G_BLUE].R;
                        ++j;
                    }

                    if (j < W && image.px_color(i, j) == GREEN)
                        color = GREEN;

                    --j;
                }
                else
                {
                    color = G_YELLOW;
                    while (visited[i][j] > 3 && j < W)
                    {
                        img.at<cv::Vec3b>(i, j).val[0] = COLORS[G_BLUE].B;
                        img.at<cv::Vec3b>(i, j).val[1] = COLORS[G_BLUE].G;
                        img.at<cv::Vec3b>(i, j).val[2] = COLORS[G_BLUE].R;
                        ++j;
                    }

                    if (j < W && image.px_color(i, j) == GREEN)
                        color = G_BLUE;

                    --j;
                }
                break;
            }
        }
    }
}

void Graphics::outline(cv::Mat &img, int visited[800][800], coord_vector &green)
{
    const int H = img.rows;
    const int W = img.cols;

    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            if (visited[i][j] == 1)
            {
                img.at<cv::Vec3b>(i, j).val[0] = COLORS[G_RED].B;
                img.at<cv::Vec3b>(i, j).val[1] = COLORS[G_RED].G;
                img.at<cv::Vec3b>(i, j).val[2] = COLORS[G_RED].R;
            }
            else if (visited[i][j] == 4)
            {
                img.at<cv::Vec3b>(i, j).val[0] = COLORS[G_BLUE].B;
                img.at<cv::Vec3b>(i, j).val[1] = COLORS[G_BLUE].G;
                img.at<cv::Vec3b>(i, j).val[2] = COLORS[G_BLUE].R;
            }
        }
    }

    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            if (visited[i][j] == 3)
            {
                img.at<cv::Vec3b>(i, j).val[0] = COLORS[G_YELLOW].B;
                img.at<cv::Vec3b>(i, j).val[1] = COLORS[G_YELLOW].G;
                img.at<cv::Vec3b>(i, j).val[2] = COLORS[G_YELLOW].R;

                for (int c = -1; c < 2; ++c)
                    for (int t = -1; t < 2; ++t)
                    {
                        if (i + c >= 0 && i + c < H && j + t >= 0 && j + t < W)
                        {
                            img.at<cv::Vec3b>(i + c, j + t).val[0] = COLORS[G_YELLOW].B;
                            img.at<cv::Vec3b>(i + c, j + t).val[1] = COLORS[G_YELLOW].G;
                            img.at<cv::Vec3b>(i + c, j + t).val[2] = COLORS[G_YELLOW].R;
                        }
                    }
            }
        }
    }

    if (!green.empty())
    {
        for (auto i : green)
        {
            img.at<cv::Vec3b>(i.first, i.second).val[0] = COLORS[G_RED].B;
            img.at<cv::Vec3b>(i.first, i.second).val[1] = COLORS[G_RED].G;
            img.at<cv::Vec3b>(i.first, i.second).val[2] = COLORS[G_RED].R;

            for (int c = -1; c < 2; ++c)
                for (int t = -1; t < 2; ++t)
                {
                    if (i.first + c >= 0 && i.first + c < H && i.second + t >= 0 && i.second + t < W)
                    {
                        img.at<cv::Vec3b>(i.first + c, i.second + t).val[0] = COLORS[G_RED].B;
                        img.at<cv::Vec3b>(i.first + c, i.second + t).val[1] = COLORS[G_RED].G;
                        img.at<cv::Vec3b>(i.first + c, i.second + t).val[2] = COLORS[G_RED].R;
                    }
                }
        }
    }
}


coord G_median(coord a, coord b)
{
    return coord((a.first + b.first) / 2, (a.second + b.second) / 2);
}

void Graphics::make_hull(std::vector<std::pair<coord, coord>> paired_vertexes, cv::Mat &frame)
{
    //tenere conto di vertici spaiati
    for (int i = 0; i < paired_vertexes.size(); ++i)
    {
        for (int j = 0; j < paired_vertexes.size(); ++j)
        {
            join_ends(frame, G_median(paired_vertexes[j].first, paired_vertexes[j].second), G_median(paired_vertexes[i].first, paired_vertexes[i].second));
        }
    }
}

void Graphics::apply_rig(cv::Mat &img, Rig rig)
{
    int H = img.rows;
    int W = img.cols;
    join_ends(img, coord(0, W / 2), coord(399, W/2), G_CYAN);
    for (int k = 0; k <= rig.num_points; ++k)
    {
        int i = rig.center_points[k].first;
        int j = rig.center_points[k].second;
        int diff = 0;
        if (k == rig.num_points)
            diff = 10;
        cv::putText(img, std::to_string(k), cv::Point(j, i + diff), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(COLORS[G_GREEN].B, COLORS[G_GREEN].G, COLORS[G_GREEN].R));
        if (k < rig.num_points)
            join_ends(img, rig.center_points[k], rig.center_points[k + 1]);
        join_ends(img, rig.center_points[k], {rig.center_points[k].first, W / 2});
        for (int c = -1; c < 2; ++c)
            for (int t = -1; t < 2; ++t)
            {
                if (i + c >= 0 && i + c < H && j + t >= 0 && j + t < W)
                {
                    img.at<cv::Vec3b>(i + c, j + t).val[0] = COLORS[G_GREEN].B;
                    img.at<cv::Vec3b>(i + c, j + t).val[1] = COLORS[G_GREEN].G;
                    img.at<cv::Vec3b>(i + c, j + t).val[2] = COLORS[G_GREEN].R;
                }
            }
    }
}

void Graphics::apply_order(cv::Mat &img, coord_vector pixels_list)
{
    for (int k = 0; k < pixels_list.size(); ++k)
    {
        if (k % 20 == 0)
        {
            int i = pixels_list[k].first;
            int j = pixels_list[k].second;
            if (i == 0)
                i += 10;
            cv::putText(img, std::to_string(k), cv::Point(j, i), cv::FONT_HERSHEY_SIMPLEX, 0.25, cv::Scalar(COLORS[G_GREEN].B, COLORS[G_GREEN].G, COLORS[G_GREEN].R));
        }
    }
}