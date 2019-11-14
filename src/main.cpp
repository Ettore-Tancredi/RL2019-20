#include <opencv2/opencv.hpp>

#include "types.h"
#include "rmath.h"

#include "Image/Image.h"
#include "Camera/Camera.h"
#include "Graphics/Graphics.h"
#include "Line/Line.h"
#include "Line/Rig.h"


int color_set[256][256][256];


void analyse(Image &img, Line &line)
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
			if (img.visited[img.height()- 1][x] == 0)
			{
				//INIZIO DFS
				std::stack<coord> stack;
				stack.push(std::make_pair(img.height() - 1, x));

				while (!stack.empty())
				{
					//std::cout << "OOOOOOO\n";
					if (img.visited[stack.top().first][stack.top().second] > 0)
						stack.pop();
					else
					{
						int i = stack.top().first;
						int j = stack.top().second;

					//	std::cout << i << " " << j << std::endl;

						for (int c = -1; c < 2; ++c)
							for (int t = -1; t < 2; ++t)
								if (img.is_inside(i + c, j + t) && !(c == 0 && t == 0))
								{
										int temp = img.matchesTarget(i + c, j + t);
										if ((temp == NORMAL_PIXEL || temp == CORNER_PIXEL) && (img.visited[i + c][j + t] == 0) && img.px_color(i+c, j+t) == BLACK)
										{
											stack.push(std::make_pair(i + c, j + t));

										}
								}

						line.barycentre.first += i;		
						line.barycentre.second += j;
						line.pixels_list.push_back(std::make_pair(i, j));
						++line.num_nodes;

						img.visited[i][j] = 1;
						if(img.matchesTarget(i, j) == CORNER_PIXEL)
							img.visited[i][j] = 2;
							
					}
				}
			}
		}	

	}

	for (int j = 0; j < img.width(); ++j)
	{
		if (img.visited[img.height()-1][j])
		{
			sides_touched[0] = true;
			break;
		}
	}
	for (int i = 0; i < img.height(); ++i)
	{
		if (img.visited[i][img.width()-1])
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


	//GREEN REGIONS

		std::pair<int, int> it;
		int biciccio = 4;
		while(!img.green_pixels.empty())
		{
			it = img.green_pixels.top();
			if(img.visited[it.first][it.second] != 0)
			{
				img.green_pixels.pop();
			}
			else
			{ 
				// DFS on green borders
				std::stack<coord> stack;
				stack.push(std::make_pair(it.first, it.second));
				std::pair<int, int> barycentre;
				int num_green_pixels = 0;

				while (!stack.empty())
				{
					if (img.visited[stack.top().first][stack.top().second] == 4)   //green pixel has already been explored
						stack.pop();
					else
					{
						int i = stack.top().first;
						int j = stack.top().second;

						for (int c = -1; c < 2; ++c)
							for (int t = -1; t < 2; ++t)
								if (img.is_inside(i + c, j + t) && !(c == 0 && t == 0))
								{
										bool temp = img.matchesGreenTarget(i + c, j + t);
										if (temp && img.visited[i + c][j + t] == 0)
										{
											stack.push(std::make_pair(i + c, j + t));	
										}
								}
						++num_green_pixels;
						barycentre.first += i;		
						barycentre.second += j;
						img.visited[i][j] = 4;
							
					}
				}
				barycentre.first = int(barycentre.first / num_green_pixels);
				barycentre.second = int(barycentre.second / num_green_pixels);
				if(num_green_pixels > 50)      //min dim of green region border (randomly chosen)
					img.green_regions.push_back(std::make_pair(barycentre.first, barycentre.second));
			}
			
		}
		
}



/*void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == cv::EVENT_LBUTTONDOWN )
     {
        img.get_debug_color(y, x);
     }
}*/

 void count_corners(Line &line, int visited[800][800], int H, int W, int lineW)
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
	for (int i = H-1; i >= 0 ; --i)
		if (visited[i][0] == 2)
		{
			visited[i][0] = 3;
			i2 = i;
			break;
		}
	
	if (i2 > 0 && i1 > 0 && i2 - i1 > lineW)
	{
		line.num_corners +=2;
	}
	else if (i2 > 0 || i1 > 0)
		++line.num_corners;

	for (int i = 0; i < H; ++i)
		if (visited[i][0] == 2)
			visited[i][0] = 1;
	
	//RIGHT
	i1 = -1, i2 = -1;
	for (int i = 0; i < H; ++i)
		if (visited[i][W-1] == 2)
		{
			visited[i][W-1] = 3;
			i1 = i;
			break;
		}
	for (int i = H-1; i >= 0 ; --i)
		if (visited[i][W-1] == 2)
		{
			visited[i][W-1] = 3;
			i2 = i;
			break;
		}
	
	if (i2 > 0 && i1 > 0 && i2 - i1 > lineW)
	{
		line.num_corners +=2;
	}
	else if (i2 > 0 || i1 > 0)
		++line.num_corners;

	for (int i = 0; i < H; ++i)
		if (visited[i][W-1] == 2)
			visited[i][W-1] = 1;

	//UP
	int j1 = -1, j2 = -1;
	for (int j = 0; j < W; ++j)
		if (visited[0][j] == 2)
		{
			visited[0][j] = 3;
			j1 = j;
			break;
		}
	for (int j = W-1; j >= 0; --j)
		if (visited[0][j] == 2)
		{
			visited[0][j] = 3;
			j2 = j;
			break;
		}
	
	if (j2 > 0 && j1 > 0 && j2 - j1 > lineW)
	{
		line.num_corners +=2;
	}
	else if (j2 > 0 || j1 > 0)
		++line.num_corners;

	for (int j = 0; j < W; ++j)
		if (visited[0][j] == 2)
			visited[0][j] = 1;

	//DOWN
	j1 = -1, j2 = -1;
	for (int j = 0; j < W; ++j)
		if (visited[H-1][j] == 2)
		{
			visited[H-1][j] = 3;
			j1 = j;
			break;
		}
	for (int j = W-1; j >= 0; --j)
		if (visited[H-1][j] == 2)
		{
			visited[H-1][j] = 3;
			j2 = j;
			break;
		}
	
	if (j2 > 0 && j1 > 0 && j2 - j1 > lineW)
	{
		line.num_corners +=2;
	}
	else if (j2 > 0 || j1 > 0)
	{
		++line.num_corners;
	}
		

	for (int j = 0; j < W; ++j)
		if (visited[H-1][j] == 2)
			visited[H-1][j] = 1;
			
}



void greenRegionsPosition(Image &img, Line &line)
{
	int i_g, j_g;
	bool up, left;
	int v_idx, o_idx;

	for(coord_vector::iterator it = img.green_regions.begin(); it != img.green_regions.end(); it++)
	{
		i_g = it->first;
		j_g = it->second;
		up = true;
		left = true;

		for(int i = 0; i < i_g; ++i)
			if(img.visited[i][j_g] == 1)
			{
				up = false;
				break;
			}

		for(int j = 0; j < j_g; ++j)
			if(img.visited[i_g][j] == 1)
			{
				left = false;
				break;
			}

		if(up)
			v_idx = 0;
		else
			v_idx = 1;

		if(left)
			o_idx = 0;
		else
			o_idx = 1;

		line.greenPos[v_idx][o_idx] = true;
			
	}
}

int main()
{	
	Image img(400, 400); //ARG: height width
	img.load_data("/home/luigi/source/repos/rl_2019-20/src/Data/color_data.txt");

  	Line line;
	Rig rig(10); //ARG: number of point for the skeleton
	Graphics graphics("feed"); //ARG: window name

	
	bool camera_opened = true;
    Camera camera(camera_opened, 30, 400, 400);
	if (!camera_opened)   
		std::cout << "Camera unavailable" << std::endl;



    cv::Mat processed_frame;

	bool silver_found = false;
	
	int img_number = 1;
	int arr[2];
    while(camera_opened && !silver_found)
    {
	//	cv::setMouseCallback("ciccio", CallBackFunc, arr);

		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		
        camera.fillFrame(img.getImage(), ++img_number);		

		line.clear();  
        analyse(img, line);
		count_corners(line, img.visited, img.height(), img.width(), 20);
		rig.make_rig(line.pixels_list, line.num_nodes);

		// for (int i = 0; i < rig.num_points; ++i)
		// 	std::cout << rig.right_points[i].first << " " << rig.right_points[i].second << "\n";

		std::cout << line.num_nodes/(2*rig.num_points) << std::endl;

		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
		std::cout << "It took me " << time_span.count() << " seconds."  << std::endl;

		processed_frame = img.copy();
        graphics.draw(img.getImage());
		cv::waitKey(0);

		
		std::cout << "Numero di nodi neri:  " << line.num_nodes << std::endl;
		std::cout << "Numero di vertici:    " << line.num_corners << std::endl;
		std::cout << "Numero regioni verdi: " << img.green_regions.size() << std::endl;
		for (auto i : img.green_regions)
			std::cout << "barycentre " << i.first << i.second << std::endl;

		greenRegionsPosition(img, line);

		for(int i = 0; i < 2; ++i)
		{
			for(int j = 0; j < 2; ++j)
				std::cout << line.greenPos[i][j] << " ";

			std::cout << std::endl;
		}

		


		
        graphics.outline(processed_frame, img.visited, img.green_regions);
	//	graphics.surface(processed_frame, img.visited, img);
		graphics.apply_rig(processed_frame, rig);
        graphics.draw(processed_frame);

		cv::waitKey(0);
		
        
    }


    return 0;
}
