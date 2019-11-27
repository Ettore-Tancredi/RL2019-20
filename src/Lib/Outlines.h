#ifndef OUTLINES_H
#define OUTLINES_H

#include "cv_types.h"
#include "Line_constants.h"
#include "Image.h"
#include "Line.h"

void outline_line(Image &img, Line &line)
{
	bool sides_touched[4] = {};

	img.clear();
	for (int i = 0; i < 4; ++i)
		sides_touched[i] = false;

	//BLACK LINE

	for (int x = 0; x < img.width(); ++x)
	{
		if (img.px_color(img.height() - 1, x) == BLACK)
		{
			if (img.visited[img.height() - 1][x] == 0)
			{
				//INIZIO DFS
				std::stack<coord> stack;
				stack.push(coord(img.height() - 1, x));

				while (!stack.empty())
				{
					int i = stack.top().first;
					int j = stack.top().second;

					if (img.visited[i][j] > 0)
						stack.pop();
					else
					{
						for (int c = -1; c < 2; ++c)
							for (int t = -1; t < 2; ++t)
								if (img.is_inside(i + c, j + t) && !(c == 0 && t == 0))
								{
									int temp = img.matchesTarget(i + c, j + t);
									if ((temp == NORMAL_PIXEL || temp == CORNER_PIXEL) && (img.visited[i + c][j + t] == 0) && img.px_color(i + c, j + t) == BLACK)
										stack.push(coord(i + c, j + t));
								}

						line.barycentre.first += i;
						line.barycentre.second += j;
						line.add_px(coord(i, j));

						img.visited[i][j] = 1;
						if (img.matchesTarget(i, j) == CORNER_PIXEL)
							img.visited[i][j] = 2;
					}
				}
			}
		}
	}

	for (int j = 0; j < img.width(); ++j)
	{
		if (img.visited[img.height() - 1][j])
		{
			sides_touched[0] = true;
			break;
		}
	}
	for (int i = 0; i < img.height(); ++i)
	{
		if (img.visited[i][img.width() - 1])
		{
			sides_touched[1] = true;
			break;
		}
	}
	for (int j = 0; j < img.width(); ++j)
	{
		if (img.visited[0][j])
		{
			sides_touched[2] = true;
			break;
		}
	}
	for (int i = 0; i < img.height(); ++i)
	{
		if (img.visited[i][0])
		{
			sides_touched[3] = true;
			break;
		}
	}
}
void outline_green_regions(Image &img, Line &line)
{
	coord it;
	while (!img.green_pixels.empty())
	{
		it = img.green_pixels.top();
		if (img.visited[it.first][it.second] != 0)
		{
			img.green_pixels.pop();
		}
		else
		{
			// DFS on green borders
			std::stack<coord> stack;
			stack.push(it);
			std::pair<int, int> barycentre;
			int num_green_pixels = 0;

			while (!stack.empty())
			{
				int i = stack.top().first;
				int j = stack.top().second;

				if (img.visited[i][j] == 4)
					stack.pop();
				else
				{

					for (int c = -1; c < 2; ++c)
						for (int t = -1; t < 2; ++t)
							if (img.is_inside(i + c, j + t) && !(c == 0 && t == 0))
							{
								bool temp = img.matchesGreenTarget(i + c, j + t);
								if (temp && img.visited[i + c][j + t] == 0)
									stack.push(coord(i + c, j + t));
							}
					++num_green_pixels;
					barycentre.first += i;
					barycentre.second += j;
					img.visited[i][j] = 4;
				}
			}
			barycentre.first = int(barycentre.first / num_green_pixels);
			barycentre.second = int(barycentre.second / num_green_pixels);
			if (num_green_pixels > MIN_GREEN_REGION_NODES)
				img.green_regions.push_back(coord(barycentre.first, barycentre.second));
		}
	}
}

void greenRegionsPosition(Image &img, Line &line)
{
	int i_g, j_g;
	bool up, left;
	int v_idx, o_idx;

	for (coord_vector::iterator it = img.green_regions.begin(); it != img.green_regions.end(); it++)
	{
		i_g = it->first;
		j_g = it->second;
		up = true;
		left = true;

		for (int i = 0; i < i_g; ++i)
			if (img.visited[i][j_g] == 1)
			{
				up = false;
				break;
			}

		for (int j = 0; j < j_g; ++j)
			if (img.visited[i_g][j] == 1)
			{
				left = false;
				break;
			}

		if (up)
			v_idx = 0;
		else
			v_idx = 1;

		if (left)
			o_idx = 0;
		else
			o_idx = 1;

		line.greenPos[v_idx][o_idx] = true;
	}
}


#endif