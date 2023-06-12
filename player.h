#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "character.h"
#include "seed.h"
#include <cmath>

class Player : public Character {
  protected:
    bool haveBSuit;
    RaceType race;

  public:
    Player (Position pos, CellType cType, int HP, int Atk, int Def, bool haveBSuit, RaceType race);

    // in cell
    void beAttacked(int atkVal) = 0;
    bool getCompass() override;

    // in player
    virtual void setAtk() = 0;
    virtual void setDef() = 0;
    virtual Player* extractPC() = 0;
    virtual void modifyHP(int changeHP) = 0;
    virtual bool getHaveBSuit() = 0;
    virtual void setHaveBSuit(bool changeValue) = 0;
    virtual RaceType getRace() = 0;
};

class Human : public Player {
  public:
    Human(Position pos);
    void setAtk() override;
    void setDef() override;
    void beAttacked(int atkVal) override;
    Player* extractPC() override;
    int getDef() override;
    void modifyHP(int changeHP) override;
    bool getHaveBSuit() override;
    void setHaveBSuit(bool changeValue) override;
    RaceType getRace() override; 
};

class Dwarf : public Player {
  public:
    Dwarf(Position pos);
    void setAtk() override;
    void setDef() override;
    void beAttacked(int atkVal) override;
    Player* extractPC() override;
    int getDef() override;
    void modifyHP(int changeHP) override;
    bool getHaveBSuit() override;
    void setHaveBSuit(bool changeValue) override;
    RaceType getRace() override; 
};

class Elves : public Player {
  public:
    Elves(Position pos);
    void setAtk() override;
    void setDef() override;
    void beAttacked(int atkVal) override;
    Player* extractPC() override;
    int getDef() override;
    void modifyHP(int changeHP) override;
    bool getHaveBSuit() override;
    void setHaveBSuit(bool changeValue) override;
    RaceType getRace() override; 
};

class Orc : public Player {
  public:
    Orc(Position pos);
    void setAtk() override;
    void setDef() override;
    void beAttacked(int atkVal) override;
    Player* extractPC() override;
    int getDef() override;
    void modifyHP(int changeHP) override;
    bool getHaveBSuit() override;
    void setHaveBSuit(bool changeValue) override;
    RaceType getRace() override; 
};

#endif
