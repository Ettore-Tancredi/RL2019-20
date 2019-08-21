#include "Image.h"
#include <opencv2/opencv.hpp> 
#include <iostream>
#include <fstream>

extern int color_set[256][256][256];

Image::Image(int h, int w)
{
  H = h;
  W = w;
  std::cout << "porca puttana" << std::endl;
}

cv::Mat Image::copy()
{
  return image;
}

cv::Mat& Image::getImage()
{
  return image;
}

int Image::width()
{
    return W;
}

int Image::height()
{
    return H;
}

void Image::clear()
{
  for(int i = 0; i < H; ++i)
    for(int j = 0; j < W; ++j)
      visited[i][j] = 0;

  regions.clear();
}


void Image::add_region(char region)
{
  regions.push_back(region);
}

bool Image::find_region(char region_type)
{
    for (auto &i: regions)
    {
        if (i == region_type)
            return true;
    }
    return false;
}

int Image::count_regions_of_type(char region_type)
{
    int count = 0;
    for (auto &i: regions)
    {
        if (i == region_type)
            ++count;
    }
    return count;
}

int Image::num_regions()
{
    return regions.size();
}


Colors Image::px_color(int i, int j)
{
    cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
    int B, G, R;

    B = pixel.val[0];
    G = pixel.val[1];
    R = pixel.val[2];

    if (color_set[B][G][R] == BLACK)
      return BLACK;
    else if (color_set[R][G][B] == WHITE)
      return WHITE;
    else if(color_set[R][G][B] == GREEN)
      return GREEN;
    else if(color_set[R][G][B] == SILVER)
      return SILVER;
}

bool Image::is_inside(int i, int j)
{
  return (i >= 0 && i < H && j >= 0 && j < W);
}


void Image::get_debug_color(int i, int j, int &t1, int &t2, int &t3)
{
  cv::Vec3b pixel = image.at<cv::Vec3b>(i, j); 
  t1 = pixel.val[0];
  t2 = pixel.val[1];
  t3 = pixel.val[2];
}


int Image::matchesTarget(int i, int j)
{
  bool isOnBorder = false;
  bool isNextToWhite = false;

  for (int c = -1; c < 2; ++c)
		for (int t = -1; t < 2; ++t)
      if(!is_inside(i + c, j + t) && !(c == 0 && t == 0))
        isOnBorder = true;
      else if(px_color(i + c, j + t) == WHITE)
        isNextToWhite = true;

  if(isOnBorder && isNextToWhite)
    return CORNER_PIXEL;
  if(isNextToWhite || isOnBorder)
    return NORMAL_PIXEL;
    
  return false;
}

void Image::load_data()
{
  std::ifstream datafile("Data/color_data.txt");
  for (int i = 0; i < 256; ++i)
  {
    for (int j = 0; j < 256; ++j)
    {
      for (int k = 0; k < 256; ++k)
        datafile >> color_set[i][j][k];
    }
  }
  datafile.close();
}