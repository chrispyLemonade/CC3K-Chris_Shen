#include "potion.h"

Potion::Potion(Position pos, int HP, int Atk, int Def, Player *component): Decorator{pos, CellType::POTION, HP, Atk, Def, component} {}

void Potion::beAttacked(int atkVal) { 
    if (component != nullptr) {
        component->beAttacked(atkVal);
    }
}

int Potion::getHP() { 
    if (component != nullptr) {
        return HP + component->getHP();
    }
    return HP;
}

int Potion::getAtk() { 
    if (component == nullptr) return Atk;

    int totAtk = Atk;
    if (component != nullptr) {
        totAtk += component->getAtk();
    }
    if (totAtk < 0) return 0;
    return totAtk;
}

int Potion::getDef() { 
    if (component == nullptr) return Def;

    int totDef = Def;
    if (component != nullptr) {
        totDef += component->getDef();
    }
    if (totDef < 0) return 0;
    return totDef;
}

int Potion::getGold() { 
    if (component != nullptr) {
        return component->getGold(); 
    }
    return 0;
}

Player* Potion::extractPC() {
    if (component == nullptr) return nullptr;
    Player *tmp = component->extractPC();
    if (component->getCType() == CellType::PC) {
        component = nullptr;
    }
    return tmp;
}

/*
Player* Potion::extractPC() { 
    if (component == nullptr) return nullptr;
    if (component->getCType() == CellType::PC) {
        Player *pc = component;
        component = nullptr;
        return pc;
    }
    return component->extractPC();
}
*/

void Potion::modifyHP(int changeHP) { 
    if (component != nullptr) {
        component->modifyHP(changeHP); 
    } 
    return;
}

void Potion::setAtk() {
    if (component != nullptr) {
        component->setAtk(); 
    } 
    return;
}

void Potion::setDef() {
    if (component != nullptr) {
        component->setDef(); 
    } 
    return;
}

bool Potion::getHaveBSuit() { 
    if (component != nullptr) {
        return component->getHaveBSuit(); 
    }
    return false;
}

void Potion::setHaveBSuit(bool changeValue) { 
    if (component != nullptr) {
        component->setHaveBSuit(changeValue); 
    }
    return;
}

RaceType Potion::getRace() { 
    if (component != nullptr) {
        return component->getRace(); 
    } 
    return RaceType::POTION;
}

CellType Potion::getCType() {
    if (component != nullptr) {
        return component->getCType();
    }
    return cType;
}

void Potion::addGold (int changeGold) {
    if (component != nullptr) {
        component->addGold(changeGold);
    }
    return;
}

Potion::~Potion() { 
    // if (component != nullptr) delete component; 
}
