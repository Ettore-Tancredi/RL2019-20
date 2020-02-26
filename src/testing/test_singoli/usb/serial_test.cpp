#include "Braswell_comm.h"
#include <iostream>
#include <string>

int main()
{
    char port[] = "/dev/ttyACM0";

    Serial serial_test(port, 9600);
    int n;
    char c;
    while (true)
    {
        std::cin >> n;
        serial_test.writeNum(n);
        std::cin >> c;
        serial_test.writeChar(c);
    }

    return 0;
}