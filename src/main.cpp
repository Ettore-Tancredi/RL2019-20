#include <opencv2/opencv.hpp>

#include "Lib/cv_types.h"

#include "Lib/Outlines.h"
#include "Lib/Vertexes.h"
#include "Image/Image.h"
#include "Camera/Camera.h"
#include "Graphics/Graphics.h"
#include "Line/Line.h"
#include "Line/Rig.h"
#include "Controller/Controller.h"
#include "Log/Log.h"

#include "Constants/Line_constants.h"

int color_set[256][256][256];

int main()
{

	Image img(IMG_HEIGHT, IMG_WIDTH);
	Line line;
	Rig rig(NUM_RIG_POINTS);
	Controller controller(KP, KI, KD, NUM_RIG_POINTS, IMG_WIDTH, IMG_HEIGHT);
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

		int img_number = 16; //->for debugging purposes
		while (camera_opened && !silver_found && img_number < 87)
		{

			log.start_clock();

			//IMAGE PROCESSING
			camera.fillFrame(img.passImage(), ++img_number);
			line.clear();
			outline_line(img, line);
			outline_green_regions(img, line);
			count_vertexes(line, img.visited, img.height(), img.width(), AVERAGE_LINE_WIDTH);
			greenRegionsPosition(img, line);
			std::vector< std::pair<coord, coord> > paired_vertexes = pair_vertexes(line.getVertexes(), img.height(), img.width());			//considerare prima quanti sono e come sono allineati, se la situazione è di linea semplice, allora
			//rig.make_rig(line);

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
			graphics.make_hull(paired_vertexes, processed_frame);
			graphics.draw(processed_frame);
			std::cout << "Image No. " << img_number << std::endl;
			log.print_current_execution_time();
			for (auto i: paired_vertexes)
				std::cout << "("<< i.first.first << ", " << i.first.second << ")   (" << i.second.first << ", " << i.second.second << ")\n";
			line.show_data();
			cv::waitKey(0);
		}
		log.save();
	}

	return 0;
}
