#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <sstream>
#include <string>

namespace util{

class Timer
{

using hi_res_clock = std::chrono::high_resolution_clock;
using milliseconds = std::chrono::milliseconds;
using seconds = std::chrono::seconds;
using minutes = std::chrono::minutes;
using hours = std::chrono::hours;

private:
    hi_res_clock::time_point start_;

public:
    Timer()
    {
        start_ = hi_res_clock::now();
    }
    
    ~Timer(){}

    void start()
    {
        start_ = hi_res_clock::now();
    }
    
    std::string elapse(){
        auto duration = hi_res_clock::now() - start_;
        auto mi = std::chrono::duration_cast<milliseconds>(duration);
        auto time = mi.count();
        auto h = time/3600000;
        time %= 3600000;
        auto m = time/60000;
        time %= 60000;
        auto s = time/1000;
        time %= 1000;

        std::stringstream ss;
        if(h>=1) ss << h << "hr ";
        if(m>=1) ss << m << "m ";
        ss << s << "." << time << "s";;
        return ss.str();
    }


};

}//namespace 
#endif
