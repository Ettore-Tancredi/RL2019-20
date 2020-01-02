#include <string>


#ifndef PARAMS_H
#define PARAMS_H

enum Mode_options
{
    SILENT = 0,
    NOSHOW,
    SHOW,
};

enum Graphics_options
{
    OUTLINE = 0,
    SURFACE,
    RIG,
    COMPLETE,
    ORDER
};

enum Delay_options
{
    NO_DELAY = 0,
};

enum Source_options
{
    CAMERA = 0,
    GALLERY
};

extern int MODE;
extern int GRAPHICS;
extern int DELAY;
extern int SOURCE;
extern std::string GALLERY_PATH;

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

#endif
