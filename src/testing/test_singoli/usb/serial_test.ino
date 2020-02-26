#include "Arduino_comm.h"

void setup()
{
    Serial.begin(9600);
    empty_buffer();
}

void loop()
{
    int n = read_num();
    Serial.writeln(n);
    char c = read_char();
    Serial.writeln(c);
}