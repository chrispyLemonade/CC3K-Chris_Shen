#include "seed.h"
#include <cstdlib>
#include <chrono>
using namespace std;

Seed::Seed(): seed{0} {
    seed = std::chrono::system_clock::now().time_since_epoch().count();
}

unsigned int Seed::getSeed() { return Seed::seed; }
