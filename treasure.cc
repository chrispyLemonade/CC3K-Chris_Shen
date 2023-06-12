#include "treasure.h"

Treasure::Treasure(Position pos, CellType cType, int value): Thing{pos, cType}, value{value} {}

int Treasure::getGold() { return value; }

Treasure::~Treasure() {}

Shorde::Shorde(Position pos): Treasure{pos, CellType::TREASURE, 2} {}

Mhorde::Mhorde(Position pos): Treasure{pos, CellType::TREASURE, 4} {}

Compass::Compass(Position pos, int value): Treasure{pos, CellType::COMPASS, value} {}

CellType Compass::getCType() { return CellType::COMPASS; }

Nhorde::Nhorde(Position pos): Treasure{pos, CellType::TREASURE, 1} {}

Dhorde::Dhorde(Position pos, CellType cType, int value): Treasure{pos, CellType::TREASURE, value}, hasDragon{true} {}

BarrierSuit::BarrierSuit(Position pos, int value): Dhorde{pos, CellType::BARRIERSUIT, value} {}

CellType BarrierSuit::getCType() { return CellType::BARRIERSUIT; }

void Dhorde::dragonDead() { hasDragon = false; }

bool Dhorde::getHasDragon() { return hasDragon; }
