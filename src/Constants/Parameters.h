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

void setParameters(int argc, char *argv[]);

#endif
