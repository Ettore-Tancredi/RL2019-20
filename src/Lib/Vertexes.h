#ifndef VERTEXES_H
#define VERTEXES_H

#include "Line.h"
#include "cv_types.h"
#include "Line_constants.h"
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>

void left_side_count(Line &line, int visited[800][800], int H, int W, int lineW)
{
	//LEFT
	int i1 = -1, i2 = -1;
	for (int i = 0; i < H; ++i)
		if (visited[i][0] == 2)
		{
			visited[i][0] = 3;
			i1 = i;
			break;
		}
	for (int i = H - 1; i >= 0; --i)
		if (visited[i][0] == 2)
		{
			visited[i][0] = 3;
			i2 = i;
			break;
		}

	if (i2 > 0 && i1 > 0)
	{
		if (i2 - i1 > lineW)
		{
			line.add_vertex(coord(i1, 0));
			line.add_vertex(coord(i2, 0));
		}
		else
		{
			if (std::max(i2, i1) <= H / 2)
			{
				line.add_vertex(coord(std::max(i2, i1), 0));
				visited[std::min(i2, i1)][0] = 1;
			}
			else
			{
				line.add_vertex(coord(std::min(i2, i1), 0));
				visited[std::max(i2, i1)][0] = 1;
			}
		}
	}
	else if (i2 > 0 || i1 > 0)
		line.add_vertex(coord(std::max(i2, i1), 0));

	for (int i = 0; i < H; ++i)
		if (visited[i][0] == 2)
			visited[i][0] = 1;
}
void right_side_count(Line &line, int visited[800][800], int H, int W, int lineW)
{
	int i1 = -1, i2 = -1;
	for (int i = 0; i < H; ++i)
		if (visited[i][W - 1] == 2)
		{
			visited[i][W - 1] = 3;
			i1 = i;
			break;
		}
	for (int i = H - 1; i >= 0; --i)
		if (visited[i][W - 1] == 2)
		{
			visited[i][W - 1] = 3;
			i2 = i;
			break;
		}

	if (i2 > 0 && i1 > 0)
	{
		if (i2 - i1 > lineW)
		{
			line.add_vertex(coord(i1, W - 1));
			line.add_vertex(coord(i2, W - 1));
		}
		else
		{
			if (std::max(i2, i1) <= H / 2)
			{
				line.add_vertex(coord(std::max(i2, i1), W - 1));
				visited[std::min(i2, i1)][W - 1] = 1;
			}
			else
			{
				line.add_vertex(coord(std::min(i2, i1), W - 1));
				visited[std::max(i2, i1)][W - 1] = 1;
			}
		}
	}
	else if (i2 > 0 || i1 > 0)
		line.add_vertex(coord(std::max(i2, i1), W - 1));

	for (int i = 0; i < H; ++i)
		if (visited[i][W - 1] == 2)
			visited[i][W - 1] = 1;
}

void upper_side_count(Line &line, int visited[800][800], int H, int W, int lineW)
{
	//UP
	int j1 = -1, j2 = -1;
	for (int j = 0; j < W; ++j)
		if (visited[0][j] == 2)
		{
			visited[0][j] = 3;
			j1 = j;
			break;
		}
	for (int j = W - 1; j >= 0; --j)
		if (visited[0][j] == 2)
		{
			visited[0][j] = 3;
			j2 = j;
			break;
		}

	if (j2 > 0 && j1 > 0)
	{
		if (j2 - j1 > lineW)
		{
			line.add_vertex(coord(0, j1));
			line.add_vertex(coord(0, j2));
		}
		else
		{
			if (std::max(j2, j1) <= W / 2)
			{
				line.add_vertex(coord(0, std::max(j2, j1)));
				visited[0][std::min(j2, j1)] = 1;
			}
			else
			{
				line.add_vertex(coord(0, std::min(j2, j1)));
				visited[0][std::max(j2, j1)] = 1;
			}
		}
	}
	else if (j2 > 0 || j1 > 0)
		line.add_vertex(coord(0, std::max(j2, j1)));

	for (int j = 0; j < W; ++j)
		if (visited[0][j] == 2)
			visited[0][j] = 1;
}

void lower_side_count(Line &line, int visited[800][800], int H, int W, int lineW)
{
	//DOWN
	int j1 = -1, j2 = -1;
	for (int j = 0; j < W; ++j)
		if (visited[H - 1][j] == 2)
		{
			visited[H - 1][j] = 3;
			j1 = j;
			break;
		}
	for (int j = W - 1; j >= 0; --j)
		if (visited[H - 1][j] == 2)
		{
			visited[H - 1][j] = 3;
			j2 = j;
			break;
		}

	if (j2 > 0 && j1 > 0)
	{
		if (j2 - j1 > lineW)
		{
			line.add_vertex(coord(H - 1, j1));
			line.add_vertex(coord(H - 1, j2));
		}
		else
		{
			if (std::max(j2, j1) <= W / 2)
			{
				line.add_vertex(coord(H - 1, std::max(j2, j1)));
				visited[H - 1][std::min(j2, j1)] = 1;
			}
			else
			{
				line.add_vertex(coord(H - 1, std::min(j2, j1)));
				visited[H - 1][std::max(j2, j1)] = 1;
			}
		}
	}
	else if (j2 > 0 || j1 > 0)
		line.add_vertex(coord(H - 1, std::max(j2, j1)));

	for (int j = 0; j < W; ++j)
		if (visited[H - 1][j] == 2)
			visited[H - 1][j] = 1;
}
void count_vertexes(Line &line, int visited[800][800], int H, int W, int lineW)
{
	right_side_count(line, visited, H, W, lineW);
	left_side_count(line, visited, H, W, lineW);
	upper_side_count(line, visited, H, W, lineW);
	lower_side_count(line, visited, H, W, lineW);
}

double euclidean_distance(coord p1, coord p2)
{
	double i = p1.first - p2.first;
	double j = p1.second - p2.second;

	return sqrt(i * i + j * j);
}


bool func(std::pair< std::pair<coord, coord>, double> a, std::pair < std::pair<coord, coord>, double> b)
{
	if (a.second < b.second)
		return true;
	else
		return false;
}

std::vector< std::pair<coord, coord> > pair_vertexes(coord_vector vertexes, int H, int W)
{
	std::vector< std::pair<coord, coord> > paired_vertexes;
	//we check for vertexes laying on the same side

	std::vector<coord> temp;
	std::vector<int> idx;

	//top of the image (0, x)

	for (int i = 0; i < vertexes.size(); ++i)
	{
		if (vertexes[i].first == 0)
		{
			temp.push_back(vertexes[i]);
			idx.push_back(i);
		}
	}
	if (temp.size() > 2)
		std::cout << "More than two vertexes for side!!!" << std::endl;
	else if (temp.size() == 2)
	{
		if (euclidean_distance(temp[0], temp[1]) > AVERAGE_LINE_WIDTH - 30 && euclidean_distance(temp[0], temp[1]) < AVERAGE_LINE_WIDTH + 30)
		{
			paired_vertexes.push_back({ temp[0], temp[1] });
			vertexes.erase(vertexes.begin() + idx[1]);
			vertexes.erase(vertexes.begin() + idx[0]);
		}
	}
	temp.clear();
	idx.clear();

	//bottom of the image (H - 1, x)

	for (int i = 0; i < vertexes.size(); ++i)
	{
		if (vertexes[i].first == H - 1)
		{
			temp.push_back(vertexes[i]);
			idx.push_back(i);
		}
	}
	if (temp.size() > 2)
		std::cout << "More than two vertexes for side!!!" << std::endl;
	else if (temp.size() == 2)
	{
		if (euclidean_distance(temp[0], temp[1]) > AVERAGE_LINE_WIDTH - 30 && euclidean_distance(temp[0], temp[1]) < AVERAGE_LINE_WIDTH + 30)
		{
			paired_vertexes.push_back({ temp[0], temp[1] });
			vertexes.erase(vertexes.begin() + idx[1]);
			vertexes.erase(vertexes.begin() + idx[0]);
		}
	}
	temp.clear();
	idx.clear();

	//left side of the image (y, 0)

	for (int i = 0; i < vertexes.size(); ++i)
	{
		if (vertexes[i].second == 0)
		{
			temp.push_back(vertexes[i]);
			idx.push_back(i);
		}
	}
	if (temp.size() > 2)
		std::cout << "More than two vertexes for side!!!" << std::endl;
	else if (temp.size() == 2)
	{
		if (euclidean_distance(temp[0], temp[1]) > AVERAGE_LINE_WIDTH - 30 && euclidean_distance(temp[0], temp[1]) < AVERAGE_LINE_WIDTH + 30)
		{
			paired_vertexes.push_back({ temp[0], temp[1] });
			vertexes.erase(vertexes.begin() + idx[1]);
			vertexes.erase(vertexes.begin() + idx[0]);
		}
	}
	temp.clear();
	idx.clear();

	//right side of the image (y, W - 1)

	for (int i = 0; i < vertexes.size(); ++i)
	{
		if (vertexes[i].second == W - 1)
		{
			temp.push_back(vertexes[i]);
			idx.push_back(i);
		}
	}
	if (temp.size() > 2)
		std::cout << "More than two vertexes for side!!!" << std::endl;
	else if (temp.size() == 2)
	{
		if (euclidean_distance(temp[0], temp[1]) > AVERAGE_LINE_WIDTH - 30 && euclidean_distance(temp[0], temp[1]) < AVERAGE_LINE_WIDTH + 30)
		{
			paired_vertexes.push_back({ temp[0], temp[1] });
			vertexes.erase(vertexes.begin() + idx[1]);
			vertexes.erase(vertexes.begin() + idx[0]);
		}
	}
	temp.clear();
	idx.clear();


	//checking for non-paired vertexes which are at a right euclidean distance


	//generating all the possible pairs of vertexes with respective distance

	std::vector< std::pair< std::pair<coord, coord>, double> > candidate_pairs;
	for (int i = 0; i < vertexes.size(); ++i)
		for (int j = i + 1; j < vertexes.size(); ++j)
			candidate_pairs.push_back({ {vertexes[i], vertexes[j]}, euclidean_distance(vertexes[i], vertexes[j]) });

	std::sort(candidate_pairs.begin(), candidate_pairs.end(), func);

	int c = 0;

	for (int i = 0; i < candidate_pairs.size(); ++i)
		if (candidate_pairs[i].second > AVERAGE_LINE_WIDTH - 30 && candidate_pairs[i].second < AVERAGE_LINE_WIDTH + 30)
		{
			paired_vertexes.push_back(candidate_pairs[i].first);
			++c;
		}

	if (c != vertexes.size() / 2)
		std::cout << "Ci sta nu problema all'abbinamento della coppie." << std::endl;

	return paired_vertexes;

}


#endif