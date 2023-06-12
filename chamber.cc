#include "chamber.h"
#include <cstdlib>
#include <vector>
using namespace std;

Chamber::Chamber(): size{0} {}

Position Chamber::randomPosition() {
    Seed newSeed = Seed{};
    srand(newSeed.getSeed());
    int n = rand() % size;
    return cposition[n];
}

void Chamber::addSize() {
    size++;
}

void Chamber::addPosition(Position pos) {
    cposition.emplace_back(pos);
}

Chamber::~Chamber() {
    cposition.clear();
}
