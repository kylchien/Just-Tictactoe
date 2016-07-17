#ifndef RANDOM_H
#define RANDOM_H

#include "runtimeEx.h"
#include "timer.h"

#include <random>

namespace util{


class Random final
{
private:
    Random() = default;
    static std::mt19937 rndEngine_;

public:
    ~Random() = default;
    static int uniformInt(int inLB, int inUB);
    static double uniformReal(double inLB, double exUB);
};

void this_thread_sleep(int milliseconds);


}
#endif // RANDOM_H
