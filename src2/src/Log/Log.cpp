#include "Log.h"

Log::Log(std::string filename)
{
    log_file.open(filename);
}

void Log::start_clock()
{
    start_time.push_back(clock::now());
}

void Log::stop_clock()
{
    stop_time.push_back(clock::now());
    execution_time.push_back(std::chrono::duration_cast<time_span>(stop_time.back() - start_time.back()));
}

void Log::print_current_execution_time()
{
    std::cout << "Execution time: " << execution_time.back().count() << "s"<<std::endl;
}