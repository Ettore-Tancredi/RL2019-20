#include <opencv2/opencv.hpp>

#include <limits>

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
// #include "Lib/debugging.h"
#include "Constants/Line_constants.h"
#include "Constants/Parameters.h"
int color_set[256][256][256];

int main(int argc, char *argv[])
{

	setParameters(argc, argv);

	Image img(IMG_HEIGHT, IMG_WIDTH);
	img.load_data("color_data.txt");

	Line line;
	Rig rig(NUM_RIG_POINTS);

	Controller controller(KP, KI, KD, NUM_RIG_POINTS, IMG_WIDTH, IMG_HEIGHT);

	Log log("run_log.txt");

	Graphics graphics;

	if (MODE == SHOW)
		graphics.start("feed");

	bool camera_opened = true;
	Camera camera(camera_opened, 30, 400, 400);

	if (!camera_opened)
		std::cout << "Camera unavailable" << std::endl;
	else
	{
		bool silver_found = false;

		int img_number = 0;
		while (camera_opened && !silver_found && img_number < 87)
		{
			log.start_clock();
			/***************************************************************************************/

			//RESET STATE
			img.clear();
			line.clear();

			log.add_time_point();
			/***************************************************************************************/

			//TAKE PHOTO
			try
			{

				camera.fillFrame(img.handle(), ++img_number);
			}
			catch (const char *msg)
			{
				log.write(msg);
				break;
			}
			log.add_time_point();
			/***************************************************************************************/

			//IMAGE PROCESSING
			outline_line(img, line, log);
			outline_green_regions(img, line);
			count_vertexes(line, img.visited, img.height(), img.width(), AVERAGE_LINE_WIDTH);
			greenRegionsPosition(img, line);

			coord_pair_vector paired_vertexes;
			try
			{
				paired_vertexes = pair_vertexes(line.getVertexes(), img.height(), img.width());
			}
			catch (const char *msg)
			{
				std::cout << msg;
			}

			log.add_time_point();
			/***************************************************************************************/

			//ESTABLISH LINE TYPE
			switch (paired_vertexes.size())
			{
			case 1:
				line.setType(INTERRUPT);
				break;
			case 2:
				line.setType(STD_LINE);
				rig.make_rig(line, paired_vertexes);
				break;
			case 3:
				line.setType(T_INTERSECTION);
				break;
			case 4:
				line.setType(C_INTERSECTION);
				break;
			default:
				line.setType(UNKNOWN);
				break;
			}

			log.add_time_point();
			/***************************************************************************************/

			//MAKE CORRECTION
			int adjustment = std::numeric_limits<int>::max();
			int lt = line.getType();
			if (lt == UNKNOWN)
				; //fare qualcosa
			else
			{
				if (lt == INTERRUPT)
					; //avanti?
				if (lt == STD_LINE)
				{
					adjustment = controller.correction(rig.center_points);
					//correggere con i motori
				}
				else
				{

					if (line.greenPos[1][0])
						; //girare
					else if (line.greenPos[1][1])
						; //girare
					else
					{
						coord_vector line_ends;
						for (int i = 0; i < paired_vertexes.size(); ++i)
							line_ends.push_back(medium(paired_vertexes[i].first, paired_vertexes[i].second));

						sort(line_ends.begin(), line_ends.end(), comp_j);

						adjustment = controller.correction({line_ends.front(), line_ends.back()});
						//correggere con i motori
					}
				}
			}

			log.stop_clock();
			/***************************************************************************************/

			if (MODE != SILENT)
			{

				std::cout << "Image No. " << img_number << std::endl;
				log.print_current_execution_time();
				line.show_data();
				std::cout << "Error: ";
				if (adjustment == std::numeric_limits<int>::max())
					std::cout << "\\" << std::endl;
				else
					std::cout << adjustment << std::endl;
				std::cout << std::endl;

				if (MODE != NOSHOW)
				{
					cv::Mat processed_frame = img.handle();
					if (GRAPHICS == OUTLINE || GRAPHICS == COMPLETE)
						graphics.outline(processed_frame, img.visited, img.green_regions);
					if (GRAPHICS == RIG || GRAPHICS == COMPLETE)
					{
						if (lt == STD_LINE)
							graphics.apply_rig(processed_frame, rig);
						else
							graphics.make_hull(paired_vertexes, processed_frame);
					}
					if (GRAPHICS == ORDER)
						graphics.apply_order(processed_frame, line.getPixelsList());

					graphics.draw(processed_frame);
				}
			}

			if (DELAY != NODELAY)
			{
				if (DELAY == INF)
					cv::waitKey(0);
				else
				{
					if (cv::waitKey(DELAY) == 'p')
						cv::waitKey(0);
				}
			}
		}
		log.save();
	}

	return 0;
}
