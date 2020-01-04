#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>

using robot_clock = std::chrono::high_resolution_clock;
using time_span = std::chrono::duration<double>;
using time_points_vector = std::vector<robot_clock::time_point>;


#ifndef LOG_H
#define LOG_H

class Log 
{
    private:
        std::ofstream log_file;

        std::vector<time_points_vector> time_points;
        std::vector<time_span> execution_time;

    public:
        Log(std::string);
    
        void start_clock();
        void add_time_point();
        void stop_clock();
        void print_current_execution_time(); //DBG func
        void write(std::string);
        void save();
};

 #endif
