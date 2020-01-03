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
    NODELAY = 0,
    INF
};


extern int MODE;
extern int GRAPHICS;
extern int DELAY;
extern std::string SOURCE;

void setParameters(int argc, char *argv[]);

#endif
