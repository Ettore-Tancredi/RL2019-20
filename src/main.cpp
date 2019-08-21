#include <opencv2/opencv.hpp>
#include <iostream>
#include <stack>
#include <utility>

#include "Image/Image.h"
#include "Camera/Camera.h"
#include "Graphics/Graphics.h"
#include "Line/Line.h"

int sides[4] = {};

int color_set[256][256][256];

using coord = std::pair<int, int>;

//TENERE

void analyse(Image &img, Line &line)
{
	for (int i = 0; i < 4; ++i)
		sides[i] = false;

	std::cout << "BUMBA" <<std::endl;
	for (int x = 0; x < img.width(); ++x)
	{
		if (img.px_color(img.height() - 1, x) == BLACK)
		{
			if (img.visited[img.height()- 1][x] == 0)
			{
				std::stack<coord> stack;
				stack.push(std::make_pair(img.height() - 1, x));

				while (!stack.empty())
				{
					if (img.visited[stack.top().first][stack.top().second] > 0)
						stack.pop();
					else
					{
						int i = stack.top().first;
						int j = stack.top().second;

						for (int c = -1; c < 2; ++c)
							for (int t = -1; t < 2; ++t)
								if (img.is_inside(i + c, j + t) && !(c == 0 && t == 0))
								{
										int temp = img.matchesTarget(i + c, j + t);
										if ((temp == NORMAL_PIXEL || temp == CORNER_PIXEL) && (img.visited[i + c][j + t] == 0) && img.px_color(i+c, j+t) == BLACK)
										{
											stack.push(std::make_pair(i + c, j + t));
											line.barycentre.first += i;		//trasformazione di sistema coordinate fatta
											line.barycentre.second += j;
											++line.num_nodes;

											if (img.matchesTarget(i + c, j + t) == CORNER_PIXEL)
												++line.num_corners;

										}
								}
					}
				}
			}
		}

	}

	for (int j = 0; j < img.width(); ++j)
	{
		if (img.visited[img.height()-1][j])
		{
			sides[0] = true;
			break;
		}
	}
	for (int i = 0; i < img.height(); ++i)
	{
		if (img.visited[i][img.width()-1])
		{
			sides[1] = true;
			break;
		}
	}
	for (int j = 0; j < img.width(); ++j)
	{
		if (img.visited[0][j])
		{
			sides[2] = true;
			break;
		}
	}
	for (int i = 0; i < img.height(); ++i)
	{
		if (img.visited[i][0])
		{
			sides[3] = true;
			break;
		}
	}
}

int main()
{
	std::cout << "1" << std::endl;
	Image img(400, 400); //fps   H    W
    
	std::cout << "2" << std::endl;
	img.load_data();
	std::cout << "3" << std::endl;
  	

    Line line;
	Graphics graphics("ciccio");
	std::cout << "4" << std::endl;
	bool camera_opened = true;
    Camera camera(camera_opened, 30, 400, 400);
	std::cout << "5" << std::endl;
	
	if (!camera_opened)
		std::cout << "Merda" << std::endl;

    cv::Mat processed_frame;

	bool silver_found = false;
	std::cout << "6" << std::endl;
	int temp = 1;
    while(camera_opened && !silver_found)
    {
		std::cout << "7" << std::endl;

        camera.fillFrame(img.getImage(), ++temp);

        processed_frame = img.copy();  
        analyse(img, line);
        graphics.draw(img.getImage());
		cv::waitKey(0);
        graphics.process(processed_frame, img.visited);
        graphics.draw(processed_frame);

		cv::waitKey(0);
        
    }



    return 0;
}




