#include <string>
#include <vector>
#include <chrono>
#include <iostream>

using clock = std::chrono::high_resolution_clock;
using time_span = std::chrono::duration<double>;

#ifndef LOG_H
#define LOG_H

class Log 
{
    std::ofstream log_file;

    std::vector<clock::time_point> start_time;
    std::vector<clock::time_point> stop_time;
    std::vector<time_span> execution_time;

    public:
        Log(std::string);
    
    void start_clock();
    void stop_clock();
    void print_current_execution_time(); //DBG func
    void save();
}


 #endif
