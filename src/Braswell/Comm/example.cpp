#include "Braswell_comm.h"
#include <iostream>
#include <string>

int main()
{
    char port[] = "/dev/ttyACM0";

    Serial mySerial(port);
    int n;
    while (true)
    {
        std::cin >> n;
        mySerial.write_int(n);
    }

    return 0;
}