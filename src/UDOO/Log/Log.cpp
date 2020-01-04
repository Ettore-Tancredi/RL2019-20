#include "Log.h"

Log::Log(std::string filename)
{
    log_file.open(filename);
}

void Log::start_clock()
{
    time_points_vector temp;
    temp.push_back(robot_clock::now());
    time_points.push_back(temp);
}

void Log::add_time_point()
{
    time_points.back().push_back(robot_clock::now());
}

void Log::stop_clock()
{
    time_points.back().push_back(robot_clock::now());
    time_points_vector temp = time_points.back();
    execution_time.push_back(std::chrono::duration_cast<time_span>(temp.back() - temp.front()));
}

void Log::print_current_execution_time()
{
    std::cout << "Execution time: " << execution_time.back().count() * 1000 << "ms" << std::endl;
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

void Log::write(std::string text)
{
    log_file << text << "\n";
}

void Log::save()
{
    time_points_vector temp;
    for (int i = 0; i < time_points.size(); ++i)
    {

        log_file << i + 1 << " ";
        temp = time_points[i];
        for (int j = 0; j < temp.size(); ++j)
        {
            log_file  << std::chrono::duration_cast<time_span>(temp[j] - temp[0]).count() * 1000 << " ";
        }
        log_file << "\n";
    }

    log_file.close();
}