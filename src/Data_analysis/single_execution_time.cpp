#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int NUM = 6;

double vals[NUM];


int main()
{
    double temp;
    ifstream in("run_log.txt");
    for (int j = 0; j < 52; ++j)
    {
        for (int i = 0; i < 5; ++i)
        {
            in >> temp;
            vals[i] += temp;
        }
    }

    for (int i = 0; i < NUM; ++i)
        vals[i] /= 52;
    ofstream out("single_execution.txt");
    for (int i = 0; i < NUM; ++i)
        out << vals[i] << "\n";
    out.close();
}
