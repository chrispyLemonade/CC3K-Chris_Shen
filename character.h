#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <vector>
#include "cell.h"

// define the class Character
class Character : public Cell{
  protected:
    int HP;
    int Atk;
    int Def;
    int Gold;
    int damage(int atkVal);

  public:
    Character(Position pos, CellType cType, int HP, int Atk, int Def);
    int getHP() override;
    int getAtk() override;
    virtual void setAtk() = 0;
    int getDef() override;
    virtual void setDef() = 0;
    int getGold() override;
    CellType getCType() override;
    void addGold(int changeGold) override;
    virtual void beAttacked(int atkVal) = 0; // use in enemy + player
    void dragonDead() override; // use in thing
    virtual bool getCompass() = 0; // use in enemy
    bool getHasDragon() override; // use in thing
    void Dead() override;
};

#endif
