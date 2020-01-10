#include "Braswell_comm.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>  // string function definitions
#include <unistd.h>  // UNIX standard function definitions
#include <fcntl.h>   // File control definitions
#include <errno.h>   // Error number definitions
#include <termios.h> // POSIX terminal control definitions

Serial::Serial(char *serial_port)
{
  USB = open(serial_port, O_RDWR | O_NONBLOCK | O_NDELAY);

  /* Error Handling */
  if (USB < 0)
  {
    std::cout << "Error " << errno << " opening "
              << serial_port
              << ": " << strerror(errno) << std::endl;
  }

  memset(&tty, 0, sizeof tty);

  /* Error Handling */
  if (tcgetattr(USB, &tty) != 0)
  {
    std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
  }

  /* Save old tty parameters */
  tty_old = tty;

  /* Set Baud Rate */
  cfsetospeed(&tty, (speed_t)B9600);
  cfsetispeed(&tty, (speed_t)B9600);

  /* Setting other Port Stuff */
  tty.c_cflag &= ~PARENB; // Make 8n1
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;

  tty.c_cflag &= ~CRTSCTS;       // no flow control
  tty.c_cc[VMIN] = 1;            // read doesn't block
  tty.c_cc[VTIME] = 5;           // 0.5 seconds read timeout
  tty.c_cflag |= CREAD | CLOCAL; // turn on READ & ignore ctrl lines

  /* Make raw */
  cfmakeraw(&tty);

  /* Flush Port, then applies attributes */
  tcflush(USB, TCIFLUSH);
  if (tcsetattr(USB, TCSANOW, &tty) != 0)
  {
    std::cout << "Error " << errno << " from tcsetattr" << std::endl;
  }
}

void Serial::write_int(int n)
{
  std::string str_num = std::to_string(n);
  char const *s = str_num.c_str();

  for (int i = 0, l = strlen(s); i < l; ++i)
    write(USB, &s[i], 1);

  char end;
  end = '\n';
  write(USB, &end, 1);
}

void Serial::writeNumber(int n)
{
  write_int(n);
  write_int(n);
}

void Serial::writeChar(char c)
{
  char character;
  character = c;
  write(USB, &character, 1);
  //   serial.writeByte(c);
}