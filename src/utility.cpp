#include "utility.h"

#include <random>
#include <chrono>
#include <thread>





//ref http://www.guyrutenberg.com/2014/05/03/c-mt19937-example/
int util::uniformRand(int min, int max)
{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    static std::mt19937 rnd(seed);
    std::uniform_int_distribution<> dist(min, max);
    return dist(rnd);
}

void util::this_thread_sleep(int milliseconds)
{
    std::chrono::milliseconds duration( milliseconds );
    std::this_thread::sleep_for( duration );
}
