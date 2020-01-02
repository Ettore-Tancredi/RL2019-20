#include <string>
#include <sstream>
#include "Parameters.h"
int MODE;
int GRAPHICS;
int DELAY;
int SOURCE;
std::string GALLERY_PATH;

void setParameters(int argc, char *argv[])
{
    if (argc)
    {
        int index = 1;
        if (argv[index] == "SILENT")
        {
            MODE = SILENT;
        }
        else if (argv[index] == "NOSHOW")
        {
            MODE = NOSHOW;
        }
        else if (argv[index] == "SHOW")
        {
            MODE = SHOW;
            ++index;
            if (argv[index] == "OUTLINE")
                GRAPHICS = OUTLINE;
            else if (argv[index] == "SURFACE")
                GRAPHICS = SURFACE;
            else if (argv[index] == "RIG")
                GRAPHICS = RIG;
            else if (argv[index] == "COMPLETE")
                GRAPHICS = COMPLETE;
            else if (argv[index] == "ORDER")
                GRAPHICS = ORDER;
        }
        ++index;

        if (argv[index] == "NO_DELAY")
        {
            MODE = NO_DELAY;
        }
        else
        {
            std::stringstream convert(argv[index]); 
            convert >> DELAY;  
        }
        ++index;

        if (argv[index] == "CAMERA")
            SOURCE = CAMERA;
        else if (argv[index] == "GALLERY")
        {
            SOURCE = GALLERY;
            ++index;
             GALLERY_PATH = argv[index];
        }
    }
    else
    {
        MODE = SHOW;
        GRAPHICS = COMPLETE;
        DELAY = NO_DELAY;
        SOURCE = GALLERY;
        GALLERY_PATH = "../../runs/3-3-12_56";
    }
}

