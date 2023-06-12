#include "thing.h"

Thing::Thing(Position pos, CellType cType): Cell{pos, cType} {}

int Thing::getHP() { return 0; }
int Thing::getAtk() { return 0; }
int Thing::getDef() { return 0; }
int Thing::getGold() { return 0; }
void Thing::addGold(int changeGold) { return;  }
void Thing::beAttacked(int atkVal) { return; }
void Thing::dragonDead() { return; }
bool Thing::getCompass() { return 1; }
bool Thing::getHasDragon() { return 0; } 
CellType Thing::getCType() { return cType; }
void Thing::Dead() { return; }

Door::Door(Position pos): Thing{pos, CellType::DOOR } {}

Passway::Passway(Position pos): Thing{pos, CellType::PASSWAY } {}

Stairs::Stairs(Position pos): Thing{pos, CellType::STAIRS} {}

Valid::Valid(Position pos): Thing{pos, CellType::VALID} {}

VWall::VWall(Position pos): Thing{pos, CellType::VWALL} {}

HWall::HWall(Position pos): Thing{pos, CellType::HWALL} {}

White::White(Position pos): Thing{pos, CellType::WHITE} {}

