#include "Image.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <stack>
#include <utility>

extern int color_set[256][256][256];

Image::Image(int h, int w)
{
  H = h;
  W = w;
}

int Image::height()
{
  return H;
}

int Image::width()
{
  return W;
}

cv::Mat &Image::handle()
{
  return image;
}

bool Image::bounds(int i, int j)
{
  return (i >= 0 && i < H && j >= 0 && j < W);
}

Colors Image::px_color(int i, int j)
{
  cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
  int B, G, R;

  B = pixel.val[0];
  G = pixel.val[1];
  R = pixel.val[2];

  if (color_set[R][G][B] == BLACK)
    return BLACK;
  else if (color_set[R][G][B] == WHITE)
    return WHITE;
  else if (color_set[R][G][B] == GREEN)
    return GREEN;
  else if (color_set[R][G][B] == SILVER)
    return SILVER;
}

void Image::add_region(char region)
{
  regions.push_back(region);
}

bool Image::find_region(char region_type)
{
  for (auto &i : regions)
  {
    if (i == region_type)
      return true;
  }
  return false;
}

int Image::count_regions(char region_type)
{
  int count = 0;
  for (auto &i : regions)
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

/*****************************************************************************************
 * INT MATCHES_TARGET(pixel coord)
 * 
 * returns LABEL of pixel based on the SATISFIED CRITERIA:
 *  - (NEIGHBOURING a BLACK OR WHITE pixel) AND (on the IMAGE BORDER) -> VERTEX_PIXEL
 *  - (NEIGHBOURING a BLACK OR WHITE pixel) OR (on the IMAGE BORDER) -> NORMAL_PIXEL  
 *  - if none are SATISFIED -> FALSE
 * 
 *  - if a NEIGHBOURING PIXEL is identified as having GREEN COLOR, it is added to 
 *    the list of GREEN_PIXELS
 * 
 * *************************************************************************************/
int Image::matchesTarget(int i, int j)
{
  bool isOnBorder = false;
  bool isNextToDifferent = false;

  for (int c = -1; c < 2; ++c)
    for (int t = -1; t < 2; ++t)
    {
      if (!bounds(i + c, j + t) && !(c == 0 && t == 0))
        isOnBorder = true;
      else if (px_color(i + c, j + t) == WHITE)
        isNextToDifferent = true;
      else if (px_color(i + c, j + t) == GREEN)
      {
        isNextToDifferent = true;
        green_pixels.push(coord(i + c, j + t));
      }
    }

  if (isOnBorder && isNextToDifferent)
    return VERTEX_PIXEL;
  if (isNextToDifferent || isOnBorder)
    return NORMAL_PIXEL;

  return false;
}

/*****************************************************************************************
 * BOOL MATCHES_GREEN_TARGET(pixel coord)
 * 
 * returns TRUE if the pixels matchs the ACCEPTABILITY CRITERIA:
 *  - (GREEN in COLOR) AND (NEIGHBOURING a BLACK OR WHITE pixel, OR on the IMAGE BORDER)  
 * 
 * *************************************************************************************/
bool Image::matchesGreenTarget(int i, int j)
{
  if (px_color(i, j) != GREEN)
    return false;
  for (int c = -1; c < 2; ++c)
    for (int t = -1; t < 2; ++t)
    {
      if (!bounds(i + c, j + t))
        return true;
      if (px_color(i + c, j + t) == BLACK)
        return true;
      if (px_color(i + c, j + t) == WHITE)
        return true;
    }
  return false;
}


void Image::clear()
{
  for (int i = 0; i < H; ++i)
    for (int j = 0; j < W; ++j)
      visited[i][j] = 0;

  regions.clear();
  std::stack<coord> clear;
  green_pixels.swap(clear);
  green_regions.clear();
}

/*************************************************************************************
 * VOID LOAD_DATA( STRING FILE_NAME )
 * 
 * -  assigns to each element of the RGB color space (C[i][j][k] with 0 <= i,j,k < 256)
      the label established during training
      
**************************************************************************************/
void Image::load_data(std::string file_name)
{
  std::ifstream datafile(file_name);
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