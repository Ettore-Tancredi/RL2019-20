#include <opencv2/opencv.hpp>

#include "types.h"
#include "rmath.h"

#include "Image/Image.h"
#include "Camera/Camera.h"
#include "Graphics/Graphics.h"
#include "Line/Line.h"
#include "Line/Rig.h"



int main()
{	
	Image img(400, 400); //ARG: height width
	img.load_data("/home/luigi/source/repos/rl_2019-20/src/Data/color_data.txt");

  	Line line;
	Rig rig(10); //ARG: number of point for the skeleton
	Graphics graphics("feed"); //ARG: window name

	Benchmark benchmark("")
	
	bool camera_opened = true;
    Camera camera(camera_opened, 30, 400, 400);
	if (!camera_opened)   
		std::cout << "Camera unavailable" << std::endl;
	else
	{
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
	}
    


    return 0;
}
