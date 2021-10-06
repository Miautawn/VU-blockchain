#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

// Timer class
///////////////////////////////

class Timer 
{
    private:
       std::chrono::time_point<std::chrono::high_resolution_clock> start;
    public:
        Timer();
        void reset();
        double current_time();

};
#endif