#include "enemy.h"
#include "enum.h"
#include <cmath>
#include <iostream>
using namespace std;

Enemy::Enemy(Position pos, CellType cType, int HP, int Atk, int Def, bool holdCompass) : 
        Character{pos, cType, HP, Atk, Def}, holdCompass{holdCompass}, isDead{0} {}

bool Enemy::getCompass() { return holdCompass; }

void Enemy::beAttacked(int atkVal) { return; }

void Enemy::Dead() {isDead = 1; }

bool Enemy::haveDead() {return isDead;}

void Enemy::setAtk() {}

void Enemy::setDef() {}

Goblin::Goblin(Position pos, bool holdCompass): Enemy{pos, CellType::GOBLIN, 70, 5, 10, holdCompass} {}

void Goblin::beAttacked(int atkVal) {
    int dmg = this->damage(atkVal);
    HP -= dmg;
}

Troll::Troll(Position pos, bool holdCompass): Enemy{pos, CellType::TROLL, 120, 25, 15, holdCompass} {}

void Troll::beAttacked(int atkVal) {
    int dmg = this->damage(atkVal);
    HP -= dmg + 5;
}

Werewolf::Werewolf(Position pos, bool holdCompass): Enemy{pos, CellType::WEREWOLF, 120, 30, 5, holdCompass} {}

void Werewolf::beAttacked(int atkVal) {
    int dmg = this->damage(atkVal);
    HP -= dmg;
    if (HP < 60) {
        cout << "Werewolf is strengthened(+attack) while Hp is below half." << endl;
        Atk = 40;
    }
    // if HP is less than half (60), then Atk will increase 1/3
}

Vampire::Vampire(Position pos, bool holdCompass): Enemy{pos, CellType::VAMPIRE, 50, 25, 25, holdCompass} {}

void Vampire::beAttacked(int atkVal) {
    int dmg = this->damage(atkVal);
    HP -= dmg + HP/10;
    // add the current 10%HP, as the Vampire ability
}

Phoenix::Phoenix(Position pos, bool holdCompass): Enemy{pos, CellType::PHOENIX, 50, 35, 20, holdCompass}, havedead{false} {}

void Phoenix::beAttacked(int atkVal) {
    int dmg = this->damage(atkVal);
    HP -= dmg;
    if (HP <= 0 && havedead == false) {
        HP = 50;
        havedead = true;
    }
    // Phoenix could revail one time. 
}

Merchant::Merchant(Position pos, bool holdCompass): Enemy{pos, CellType::MERCHANT, 30, 70, 5, holdCompass} {}

void Merchant::beAttacked(int atkVal) {
    int dmg = this->damage(atkVal);
    HP -= dmg;
}

Dragon::Dragon(Position pos, Cell *horde, bool holdCompass): Enemy{pos, CellType::DRAGON, 150, 20, 20, holdCompass}, protecthorde{horde} {}

void Dragon::beAttacked(int atkVal) {
    int dmg = this->damage(atkVal);
    HP -= dmg;
    if (HP <= 0) protecthorde->dragonDead();
}
