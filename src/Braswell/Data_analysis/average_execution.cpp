#include <iostream>
#include <fstream>
#include <string>

using namespace  std;

double vals[52] = {};
double min_vals[52];
double max_vals[52] = {};
int main()
{
    double temp;
    for (int i = 0; i < 52; ++i)
        min_vals[i]= 200;

    for (int i = 1; i <= 500; ++i)
    {
        ifstream in("run_log" + to_string(i) + ".txt");
        for (int j = 0; j < 52; ++j)
        {
            in >> temp;
            //temp *= 1000;
            vals[j] += temp;
            min_vals[j] = min(min_vals[j], temp);
            max_vals[j] = max(max_vals[j], temp);
        }   
        std::cout << vals[5] << std::endl;
        in.close();
    }

    for (int i = 0; i < 52; ++i)
        vals[i] /= 500;
    for (int i = 0; i < 52; ++i)
        vals[i] *= 1000;
    ofstream out("average_execution.txt");
    for (int i = 0; i < 52; ++i)
        out << vals[i] << " " << min_vals[i]*1000 << " " << max_vals[i]*1000 << "\n";
    out.close();


}
