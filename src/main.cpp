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
// #include "Lib/debugging.h" 

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

		int img_number = 0;
		while (camera_opened && !silver_found && img_number <= 51)
		{
			//if (img_number == 87)
			//	img_number = 0;
			log.start_clock();

			//IMAGE PROCESSING
			try
			{
				camera.fillFrame(img.passImage(), ++img_number);
			}
			catch (const char *msg)
			{
				log.write(msg);
				break;
			}

			img.clear();
			line.clear();
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

			switch (paired_vertexes.size())
			{
			case 1:
				line.setType(INTERRUPT);
				break;
			case 2:
				line.setType(STD_LINE);
				rig.make_rig(line, paired_vertexes);
				controller.correction(rig.center_points);
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

			int lt = line.getType();
			if (lt == 0)
				; //fare qualcosa
			if (lt >= 1)
			{
				//considera distanza estremità bassa - asse
				if (lt == 1)
					; //avanti?
				if (lt > 2)
					; //controlla verde
				else
					; //esegui correzione
			}

			log.stop_clock();

			//DEMO-DBG
			//graphics.draw(img.passImage());
			//cv::waitKey(0);
			cv::Mat processed_frame = img.copy();
			graphics.outline(processed_frame, img.visited, img.green_regions);
			//graphics.surface(processed_frame, img.visited, img);
			if (lt == STD_LINE)
			{
				graphics.apply_rig(processed_frame, rig);
				//graphics.apply_order(processed_frame, line.getPixelsList());
			}
			else
				graphics.make_hull(paired_vertexes, processed_frame);
	
			graphics.draw(processed_frame);
			std::cout << "Image No. " << img_number << std::endl;
			log.print_current_execution_time();
			line.show_data();
			if (cv::waitKey(200) == 'p')
				cv::waitKey(0);
		}
		log.save();
	}

	return 0;
}
