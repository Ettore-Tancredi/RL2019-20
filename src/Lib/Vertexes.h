#ifndef VERTEXES_H
#define VERTEXES_H

#include "Line.h"
#include "cv_types.h"
#include "Line_constants.h"
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>

coord medium(coord a, coord b)
{
    return coord((a.first + b.first) / 2, (a.second + b.second) / 2);
}

bool comp_j(const coord a, const coord b)
{
	return a.second < b.second;
}

bool comp_up(double n1, double n2, double error)
{
	return (n1 < n2 + (n2 * error));
}

bool comp_down(double n1, double n2, double error)
{
	return (n1 > n2 - (n2 * error));
}

bool comp(double n1, double n2, double error)
{
	return comp_up(n1, n2, error) && comp_down(n1, n2, error);
}

double dist_from_axis(coord px, int W)   // obviously, since we work with even image dimensions, we won't have a 0 error for any px value
{
	return double(px.second) - double(W / 2);
}

void left_side_count(Line &line, int visited[800][800], int H, int W, int lineW, double error)
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
		if (comp_down(i2 - i1, lineW, error))
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
void right_side_count(Line &line, int visited[800][800], int H, int W, int lineW, double error)
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
		if (comp_down(i2 - i1, lineW, error))
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

void upper_side_count(Line &line, int visited[800][800], int H, int W, int lineW, double error)
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
		if (comp_down(j2 - j1, lineW, error))
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

void lower_side_count(Line &line, int visited[800][800], int H, int W, int lineW, double error)
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
		if (comp_down(j2 - j1, lineW, error))
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
	double error = 0.2;
	right_side_count(line, visited, H, W, lineW, error);
	left_side_count(line, visited, H, W, lineW, error);
	upper_side_count(line, visited, H, W, lineW, error);
	lower_side_count(line, visited, H, W, lineW, error);
}

double euclidean_distance(coord p1, coord p2)
{
	double i = p1.first - p2.first;
	double j = p1.second - p2.second;
	return sqrt(i * i + j * j);
}

bool func(std::pair<coord_pair, double> a, std::pair<coord_pair, double> b)
{
	if (a.second < b.second)
		return true;
	else
		return false;
}

coord_pair_vector pair_vertexes(coord_vector vertexes, int H, int W)
{
	double error = 1;
	coord_pair_vector paired_vertexes;
	//we check for vertexes laying on the same side

	coord_vector temp;
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
		throw "More than two vertexes for side";
	else if (temp.size() == 2)
	{
		//mettere errore %
		if (comp(euclidean_distance(temp[0], temp[1]), AVERAGE_LINE_WIDTH, error))
		{
			paired_vertexes.push_back({temp[0], temp[1]});
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
		throw "More than two vertexes for side";
	else if (temp.size() == 2)
	{
		if (comp(euclidean_distance(temp[0], temp[1]), AVERAGE_LINE_WIDTH, error))
		{
			paired_vertexes.push_back({temp[0], temp[1]});
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
		throw "More than two vertexes for side";
	else if (temp.size() == 2)
	{
		if (comp(euclidean_distance(temp[0], temp[1]), AVERAGE_LINE_WIDTH, error))
		{
			paired_vertexes.push_back({temp[0], temp[1]});
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
		throw "More than two vertexes for side";
	else if (temp.size() == 2)
	{
		if (comp(euclidean_distance(temp[0], temp[1]), AVERAGE_LINE_WIDTH, error))
		{
			paired_vertexes.push_back({temp[0], temp[1]});
			vertexes.erase(vertexes.begin() + idx[1]);
			vertexes.erase(vertexes.begin() + idx[0]);
		}
	}
	temp.clear();
	idx.clear();

	//checking for non-paired vertexes which are at a right euclidean distance

	//generating all the possible pairs of vertexes with respective distance

	std::vector<std::pair<coord_pair, double>> candidate_pairs;
	for (int i = 0; i < vertexes.size(); ++i)
		for (int j = i + 1; j < vertexes.size(); ++j)
			candidate_pairs.push_back({{vertexes[i], vertexes[j]}, euclidean_distance(vertexes[i], vertexes[j])});

	std::sort(candidate_pairs.begin(), candidate_pairs.end(), func);

	int c = 0;

	for (int i = 0; i < candidate_pairs.size(); ++i)
		if (comp(candidate_pairs[i].second, AVERAGE_LINE_WIDTH, error))
		{
			paired_vertexes.push_back(candidate_pairs[i].first);
			++c;
		}

	if (c != vertexes.size() / 2)
		throw "presenza vertici spaiati";

	return paired_vertexes;
}

#endif