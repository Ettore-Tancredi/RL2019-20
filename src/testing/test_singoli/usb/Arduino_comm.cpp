#include "Arduino_comm.h"
#include "Arduino.h"

int read_num()
{
  int num = 0;
  char c = '0';
  do
  {
    while (!Serial.available()) {};
    num = num * 10 + c - '0';
    if (Serial.available())
      c = Serial.read();
  }
  while (c != '\n');

  return num;
}

char read_char()
{
  char c;
  while (!Serial.available()) {};
  c = Serial.read();
  return c;
}

void empty_buffer()
{
  char garbage;
  while (Serial.available())
    garbage = Serial.read();
}
