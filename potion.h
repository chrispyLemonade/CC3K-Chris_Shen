#ifndef __POTION_H__
#define __POTION_H__

#include "decorator.h"

class Potion : public Decorator {
  public:
    Potion(Position pos, int HP, int Atk, int Def, Player *component);
    void beAttacked(int atkVal) override;
    int getHP() override;
    int getAtk() override;
    int getDef() override;
    int getGold() override;
    void addGold(int changeGold) override;
    Player* extractPC() override;
    void modifyHP(int changeHP) override;
    bool getHaveBSuit() override;
    void setHaveBSuit(bool changeValue) override;
    RaceType getRace() override;
    CellType getCType() override;
    void setAtk() override;
    void setDef() override;
    ~Potion();
};

#endif
