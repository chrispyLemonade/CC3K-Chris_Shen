#include "character.h"

Character::Character(Position pos, CellType cType, int HP, int Atk, int Def) : 
      Cell{pos, cType}, HP{HP}, Atk{Atk}, Def{Def}, Gold{0} {};

int Character::damage(int atkVal) {
    int ten_damage = 10 * 100 * atkVal / (100 + Def);
    if (ten_damage % 10 == 0) return ten_damage / 10;
    return ten_damage / 10 + 1;
}

int Character::getHP() { return HP; }

int Character::getAtk() { return Atk; }

int Character::getDef() { return Def; }

int Character::getGold() { return Gold; }

void Character::addGold(int changeGold) { Gold += changeGold; }

void Character::dragonDead() {}

bool Character::getHasDragon() { return false; }

CellType Character::getCType() { return cType; }

void Character::Dead() {return; }
