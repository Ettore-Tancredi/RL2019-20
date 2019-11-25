#include "Log.h"

Log::Log(std::string filename)
{
    log_file.open(filename);
}

void Log::start_clock()
{
    start_time.push_back(robot_clock::now());
}

void Log::stop_clock()
{
    stop_time.push_back(robot_clock::now());
    execution_time.push_back(std::chrono::duration_cast<time_span>(stop_time.back() - start_time.back()));
}

void Log::print_current_execution_time()
{
    std::cout << "Execution time: " << execution_time.back().count() << "s"<<std::endl;
}

std::string dbg(int i)
{
    if (i <= 52)
        return " s";
    else if (i <= 66)
        return " t";
    else if (i <= 75)
        return " c";
    else if (i <= 78)
        return " t";
    else if (i <= 84)
        return " c";
    else 
        return " s";
}

void Log::save()
{
    for (int i = 0; i < execution_time.size(); ++i)
        log_file << i+1 << " " << execution_time[i].count() /*<< dbg(i+1)*/ << "\n";        

    log_file.close();
}