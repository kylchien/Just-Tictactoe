#include "random.h"

#include <random>
#include <chrono>
#include <thread>

namespace util{

//ref http://www.guyrutenberg.com/2014/05/03/c-mt19937-example/

auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::seed_seq seq{seed};
std::mt19937 Random::rndEngine_(seq);

int Random::uniformInt(int inLB, int inUB) {
    std::uniform_int_distribution<> dist(inLB, inUB);
    return dist(rndEngine_);
}

double Random::uniformReal(double inLB, double exUB) {
    std::uniform_real_distribution<> dist(inLB, exUB);
    return dist(rndEngine_);
}

void this_thread_sleep(int milliseconds)
{
    std::chrono::milliseconds duration( milliseconds );
    std::this_thread::sleep_for( duration );
}


}
