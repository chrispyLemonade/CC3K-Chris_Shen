#include "player.h"
#include <cmath>
using namespace std;

Player::Player(Position pos, CellType cType, int HP, int Atk, int Def, bool haveBSuit, RaceType race):
        Character{pos, cType, HP, Atk, Def}, haveBSuit{haveBSuit}, race{race} {}

bool Player::getCompass() { return 0; }

Human::Human(Position pos): Player{pos, CellType::PC, 140, 20, 20, 0, RaceType::HUMAN} {}

void Human::setAtk() { Atk = 246; }

void Human::setDef() { Def = 246; }

void Human::beAttacked(int atkVal) { 
    int dmg = damage(atkVal);
    if (haveBSuit) {
        if (dmg % 2 == 1) {
            dmg = dmg / 2 +1;
        } else {
            dmg = dmg / 2;
        }
    }
    HP -= dmg;
}

Player* Human::extractPC() { return this; }

int Human::getDef() { return Def; }

void Human::modifyHP(int changeHP) { 
    HP += changeHP; 
    if (HP > 140) HP = 140;
}

bool Human::getHaveBSuit() { return haveBSuit; }

void Human::setHaveBSuit(bool changeValue) { haveBSuit = changeValue; }

RaceType Human::getRace() { return race; }

Dwarf::Dwarf(Position pos): Player{pos, CellType::PC, 100, 20, 30, 0, RaceType::DWARF} {} 

void Dwarf::setAtk() { Atk = 246; }

void Dwarf::setDef() { Def = 246; }

void Dwarf::beAttacked(int atkVal) { 
    int dmg = damage(atkVal);
    if (haveBSuit) {
        if (dmg % 2 == 1) {
            dmg = dmg / 2 +1;
        } else {
            dmg = dmg / 2;
        }
    }
    HP -= dmg;
}

Player* Dwarf::extractPC() { return this; }

int Dwarf::getDef() { return Def; }

void Dwarf::modifyHP(int changeHP) { 
    HP += changeHP; 
    if (HP > 100) HP = 100;
}

bool Dwarf::getHaveBSuit() { return haveBSuit; }

void Dwarf::setHaveBSuit(bool changeValue) { haveBSuit = changeValue; }

RaceType Dwarf::getRace() { return race; }

Elves::Elves(Position pos): Player{pos, CellType::PC, 140, 30, 10, 0, RaceType::ELVES} {} 

void Elves::setAtk() { Atk = 246; }

void Elves::setDef() { Def = 246; }

void Elves::beAttacked(int atkVal) { 
    int dmg = damage(atkVal);
    if (haveBSuit) {
        if (dmg % 2 == 1) {
            dmg = dmg / 2 +1;
        } else {
            dmg = dmg / 2;
        }
    }
    HP -= dmg;
}

Player* Elves::extractPC() { return this; }

int Elves::getDef() { return Def; }

void Elves::modifyHP(int changeHP) { 
    HP += abs(changeHP); 
    if (HP > 140) HP = 140;
}

bool Elves::getHaveBSuit() { return haveBSuit; }

void Elves::setHaveBSuit(bool changeValue) { haveBSuit = changeValue; }

RaceType Elves::getRace() { return race; }

Orc::Orc(Position pos): Player{pos, CellType::PC, 180, 30, 25, 0, RaceType::ORC} {} 

void Orc::setAtk() { Atk = 246; }

void Orc::setDef() { Def = 246; }

void Orc::beAttacked(int atkVal) { 
    int dmg = damage(atkVal);
    if (haveBSuit) {
        if (dmg % 2 == 1) {
            dmg = dmg / 2 +1;
        } else {
            dmg = dmg / 2;
        }
    }
    HP -= dmg;
}

Player* Orc::extractPC() { return this; }

int Orc::getDef() { return Def; }

void Orc::modifyHP(int changeHP) {
    HP += changeHP; 
    if (HP > 180) HP = 180;
}

bool Orc::getHaveBSuit() { return haveBSuit; }

void Orc::setHaveBSuit(bool changeValue) { haveBSuit = changeValue; }

RaceType Orc::getRace() { return race; }
