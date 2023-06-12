#ifndef __THING_H__
#define __THING_H__

#include "cell.h"

class Thing : public Cell {
  public:
    Thing(Position pos, CellType cType);
    int getHP() override;
    int getAtk() override;
    int getDef() override;
    int getGold() override;
    CellType getCType() override;
    void addGold(int changeGold) override;
    void beAttacked(int atkVal) override;
    void dragonDead() override;
    bool getCompass() override;
    bool getHasDragon() override;
    void Dead() override;
};

class Door : public Thing {
  public:
    Door(Position pos);
};

class Passway : public Thing  {
  public:
    Passway(Position pos);
};

class Stairs : public Thing  {
  public:
    Stairs(Position pos);
};

class Valid : public Thing  {
  public:
    Valid(Position pos);
};

class VWall : public Thing {
  public:
    VWall(Position pos);
};

class HWall : public Thing {
  public:
    HWall(Position pos);
};

class White : public Thing {
  public:
    White(Position pos);
};

#endif
