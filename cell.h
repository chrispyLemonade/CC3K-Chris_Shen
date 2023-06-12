#ifndef __CELL_H__
#define __CELL_H__

#include "position.h"
#include "subject.h"
#include "enum.h"

class Cell : public Subject {
  protected:
    Position pos;
    CellType cType;
  public:
    Cell(Position pos, CellType cType);
    Position getPos();
    virtual CellType getCType() = 0;
    void setPos(int row, int col);
    virtual int getHP() = 0; 
    virtual int getAtk() = 0;
    virtual int getDef() = 0;
    virtual int getGold() = 0;
    virtual void addGold(int changeGold) = 0;
    virtual void beAttacked(int atkVal) = 0;
    virtual void dragonDead() = 0;
    virtual bool getCompass() = 0;
    virtual bool getHasDragon() = 0;
    virtual void Dead() = 0;
    ~Cell();
};

#endif
