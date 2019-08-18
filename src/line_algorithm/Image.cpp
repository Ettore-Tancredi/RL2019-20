#include "Image.h"
#include <opencv2/opencv.hpp> 

Image::Image(int h, int w)
{
  H = h;
  W = w;
}

coord Image::Gpx_coord(int i)
{
  return green_pixels[i];
}


void Image::get_debug_color(int i, int j, int &t1, int &t2, int &t3)
{
  cv::Vec3b pixel = val.at<Vec3b>(i, j); 
  t1 = pixel.val[0];
  t2 = pixel.val[1];
  t3 = pixel.val[2];
}

void Image::clear()
{
  for(int i = 0; i < H; ++i)
    for(int j = 0; j < W; ++j)
      visited[i][j] = 0;

  regions.clear();
  green_pixels.clear();
  green_regions = 0;
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

int Image::count_regions(char region_type)
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

Colors Image::mostFrequentNeightbour(int i, int j)
{
  int i_adj[] = {0, 1, 1, 1, 0, -1, -1, -1};
  int j_adj[] = {1, 1, 0, -1, -1, -1, 0, 1};

  Colors temp;
  int new_i, new_j;
  int whites = 0, blacks = 0, greens = 0, silvers = 0;

  for(int c = 0; c < 8; c++)
  {
    new_i = i + i_adj[c];
    new_j = j + j_adj[c];
    if(0 <= new_i && new_i < H && 0 <= new_j && new_j < W)
    {
      temp = val.px_color(new_i, new_j);
      switch(temp)
      {
        case WHITE:
          ++whites;
        case BLACK:
          ++blacks;
        case GREEN:
          ++greens;
        case SILVER:
          ++silvers;
        default:
          ++whites;     // onde evitare casini inimmaginabili nel caso di 2 UNKNOWN vicini, ci limitiamo a restituire il valore più probabile
      }
    }
  }

  int massValue = 0;
  temp = WHITE;

  if(whites >= massValue)
  {
    massValue = whites;
    temp = WHITE;
  }
  if(blacks >= massValue)
  {
    massValue = blacks;
    temp = BLACK;
  }
  if(greens >= massValue)
  {
    massValue = greens;
    temp = GREEN;
  }
  if(silvers >= massValue)
  {
    massValue = silvers;
    temp = SILVER;
  }

  return temp;
}

Colors Image::px_color(int i, int j)
{
    cv::Vec3b pixel = val.at<Vec3b>(i, j);
    int R, G, B;

    R = pixel.val[0];
    G = pixel.val[1];
    B = pixel.val[2];

    if (dataset[R][G][B] == BLACK)
      return BLACK;
    else if (dataset[R][G][B] == WHITE)
      return WHITE;
    else if(dataset[R][G][B] == GREEN)
      return GREEN;
    else if(dtataset[R][G][B] == SILVER)
      return SILVER;

}

int Image::width()
{
    return W;
}
int Image::height()
{
    return H;
}

int Image::num_G_pixels()
{
  return green_pixels.size();
}

void Image::add_px(int i, int j)
{
  green_pixels.push_back(std::pair<int, int>(i, j));
}

void Image::add_region(char region)
{
  regions.push_back(region);
}

bool Image::is_inside(int i, int j)
{
  return (i >= 0 && i < H && j >= 0 && j < W);
}

bool Image::isValid(int i, int j, int target)
{
    bool flag = false;

		for (int c = -1; c < 2; ++c)
			for (int t = -1; t < 2; ++t)
				if (is_inside(i + c, j + t) && !(c == 0 && t == 0))
        {
          if (target == BLACK && (px_color(i+c, j+t) == GREEN || px_color(i+c, j+t) == WHITE || (i == 0 || i == H - 1 || j == 0 || j == W - 1)))
            flag |= true;
          else if (target == WHITE && (px_color(i+c, j+t) == BLACK || px_color(i+c, j+t) == GREEN|| (i == 0 || i == H - 1 || j == 0 || j == W - 1)))
            flag|= true;
          else if (target == GREEN && (px_color(i+c, j+t) == BLACK || px_color(i+c, j+t) == WHITE || (i == 0 || i == H - 1 || j == 0 || j == W - 1)))
            flag|= true;  
        }

		return flag;
}


#endif
