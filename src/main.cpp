#include <opencv2/opencv.hpp>

#include "cv_types.h"

#include "Image/Image.h"
#include "Camera/Camera.h"
#include "Graphics/Graphics.h"
#include "Line/Line.h"
#include "Line/Rig.h"
#include "Log/Log.h"

//GLOBAL CONSTANTS
const int IMG_HEIGHT = 400;
const int IMG_WIDTH = 400;
const int AVERAGE_LINE_WIDTH = 70;
const int NUM_RIG_POINTS = 10;

int color_set[256][256][256];

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

				if (img.visited[i][j] == 4) //green pixel has already been explored
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
			if (num_green_pixels > 50) //min dim of green region border (randomly chosen)	--> sostituire numero magico con costante definita in alto
				img.green_regions.push_back(coord(barycentre.first, barycentre.second));
		}
	}
}

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

int main()
{
	Image img(IMG_HEIGHT, IMG_WIDTH);
	Line line;
	Rig rig(NUM_RIG_POINTS);
	Log log("run_log.txt");

	Graphics graphics("feed"); //ARG: window name

	img.load_data("color_data.txt");

	bool camera_opened = true;
	Camera camera(camera_opened, 30, 400, 400);
	if (!camera_opened)
		std::cout << "Camera unavailable" << std::endl;
	else
	{
		bool silver_found = false;

		int img_number = 1;
		while (camera_opened && !silver_found)
		{

			log.start_clock();

			//IMAGE PROCESSING
			camera.fillFrame(img.passImage(), img_number++);
			line.clear();
			outline_line(img, line);
			outline_green_regions(img, line);
			count_vertexes(line, img.visited, img.height(), img.width(), AVERAGE_LINE_WIDTH);
			greenRegionsPosition(img, line);
			
			//considerare prima quanti sono e come sono allineati, se la situazione è di linea semplice, allora
			rig.make_rig(line);

			//CALCULATING ERROR
			//... aggiungere tutta la roba, prende rig in input

			log.stop_clock();

			//DEMO-DBG
			graphics.draw(img.passImage());
			cv::waitKey(0);
			cv::Mat processed_frame = img.copy();
			graphics.outline(processed_frame, img.visited, img.green_regions);
			//graphics.surface(processed_frame, img.visited, img);
			//	graphics.apply_rig(processed_frame, rig);
			graphics.draw(processed_frame);
			std::cout << "Image No. " << img_number << std::endl;
			log.print_current_execution_time();
			line.show_data();
			cv::waitKey(0);
		}
		log.save(); //notato che per alcune ci mette inspiegabilmente il doppio ad analizzare, vedere qual' è la parte che rallenta, magari prendendo il tempo in più istanti.
	}

	return 0;
}
