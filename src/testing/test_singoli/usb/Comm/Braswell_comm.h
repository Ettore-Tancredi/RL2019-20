#ifndef BRASWELL_COMM_H
#define BRASWELL_COMM_H

#include <string>
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions




class Serial
{
    private:
    struct termios tty;
    struct termios tty_old;
    int USB;

    public:
    Serial(char*, int);
    void writeChar(char);
    void writeNum(int n);
};

#endif