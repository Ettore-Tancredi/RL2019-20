#include <opencv2/opencv.hpp>

#include "types.h"
#include "rmath.h"

#include "Image/Image.h"
#include "Camera/Camera.h"
#include "Graphics/Graphics.h"
#include "Line/Line.h"
#include "Line/Rig.h"
#include "Log/Log.h"



int main()
{	
	Image img(400, 400); //ARG: height width
  	Line line;
	Rig rig(10); //ARG: number of points for the skeleton
	Log log("run_log.txt"); //ARG: file to save run data
	
	Graphics graphics("feed"); //ARG: window name

	img.load_data("/home/luigi/source/repos/rl_2019-20/src/Data/color_data.txt");
	
	bool camera_opened = true;
    Camera camera(camera_opened, 30, 400, 400);
	if (!camera_opened)   
		std::cout << "Camera unavailable" << std::endl;
	else
	{
		bool silver_found = false;
		
		int img_number = 1;
		while(camera_opened && !silver_found)
		{
			
			log.start_clock();

			//IMAGE PROCESSING
			camera.fillFrame(img.getImage(), ++img_number);		
			line.clear();  
			analyse(img, line);
			count_corners(line, img.visited, img.height(), img.width(), 20);		
			greenRegionsPosition(img, line);
		//	rig.make_rig(line.pixels_list, line.num_nodes);
			
			//CALCULATING ERROR
			//...
			
			log.stop_clock();
			
			
			//DEMO-DBG
			log.print_current_execution_time();
			line.show_data();
			graphics.draw(img.getImage());
			cv::waitKey(0);
			cv::Mat processed_frame = img.copy();
			graphics.outline(processed_frame, img.visited, img.green_regions);
		//	graphics.surface(processed_frame, img.visited, img);
		//	graphics.apply_rig(processed_frame, rig);
			graphics.draw(processed_frame);
			cv::waitKey(0);
		}
		log.save();
	}
    


    return 0;
}
