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
    img.load_data("color_data.txt");

    Line line;
    Rig rig(NUM_RIG_POINTS);
    Controller controller(KP, KI, KD, NUM_RIG_POINTS, IMG_WIDTH, IMG_HEIGHT);

    Log log("run_log.txt");

    bool camera_opened = true;
    Camera camera(camera_opened, 30, 400, 400);

    for (int i = 0; i < 500; ++i)
    {
        if (!camera_opened)
            std::cout << "Camera unavailable" << std::endl;
        else
        {
            bool silver_found = false;

            int img_number = 0;
            while (camera_opened && !silver_found && img_number < 50)
            {

                log.start_clock(); //0
                /*******************************************************************************************************/

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

                log.add_time_point(); //1
                /*******************************************************************************************************/

                img.clear();
                line.clear();
                log.add_time_point(); //2
                /*******************************************************************************************************/

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
                log.add_time_point(); //3
                /*******************************************************************************************************/

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

                log.stop_clock(); //4
                /*******************************************************************************************************/
            }
            log.save_benchmark();
        }
    }

        return 0;
    }
