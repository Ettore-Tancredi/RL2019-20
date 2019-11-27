#ifndef VERTEXES_H
#define VERTEXES_H

#include "Line.h"
#include "cv_types.h"

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

#endif