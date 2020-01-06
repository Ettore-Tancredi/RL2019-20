#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int NUM = 10;

double vals[NUM] = {};


int main()
{
    double temp;
    ifstream in("run_log.txt");
    for (int j = 0; j <= 87; ++j)
    {
        in >> temp;
        for (int i = 0; i < NUM; ++i)
        {
            in >> temp;
           // std::cout << temp << " ";
            vals[i] += temp;
        }
      //  std::cout << endl;
    }

    for (int i = 0; i < NUM; ++i)
        vals[i] /= 87;
    ofstream out("single_execution.txt");
    for (int i = 0; i < NUM; ++i)
        out << vals[i] << "\n";
    out.close();
}
