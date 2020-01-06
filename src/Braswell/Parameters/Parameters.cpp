#include <string>
#include <sstream>
#include <iostream>
#include "Parameters.h"

int MODE = SHOW;
int GRAPHICS = COMPLETE;
int DELAY = INF;
std::string SOURCE = "../../../runs/3-3-12_56/";

void setParameters(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::string arg, parameter, option;
        for (int i = 1; i < argc; ++i)
        {
            arg = argv[i];
            parameter = arg.substr(0, arg.find("="));
            option = arg.substr(arg.find("=") + 1, arg.length());

            if (parameter == "MODE")
            {
                if (option == "SILENT")
                {
                    MODE = SILENT;
                    DELAY = NODELAY;
                }
                else if (option == "NOSHOW")
                {
                    MODE = NOSHOW;
                    DELAY = NODELAY;
                }
                else if (option == "SHOW")
                    MODE = SHOW;
            }
            else if (parameter == "GRAPHICS")
            {
                if (option == "OUTLINE")
                    GRAPHICS = OUTLINE;
                else if (option == "SURFACE")
                    GRAPHICS = SURFACE;
                else if (option == "RIG")
                    GRAPHICS = RIG;
                else if (option == "COMPLETE")
                    GRAPHICS = COMPLETE;
                else if (option == "ORDER")
                    GRAPHICS = ORDER;
            }
            else if (parameter == "DELAY")
            {
                if (option == "NODELAY")
                    DELAY = NODELAY;
                else if (option == "INF")
                    DELAY = INF;
                else
                {
                    std::stringstream convert(option);
                    convert >> DELAY;
                }
            }
            else if (parameter == "SOURCE")
            {
                if (option == "CAMERA")
                    SOURCE = "CAMERA";
                else
                    SOURCE = option;
            }
        }
    }
}
