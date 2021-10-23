#include "timer.hpp"

//constructor
Timer::Timer() : start{ std::chrono::high_resolution_clock::now() } {}

//reset the timer
void Timer::reset() { start = std::chrono::high_resolution_clock::now(); }

//return elapsed time 
double Timer::current_time() {return std::chrono::duration<double> (std::chrono::high_resolution_clock::now() - start).count();}
