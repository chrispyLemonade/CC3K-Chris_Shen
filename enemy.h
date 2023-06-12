#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "character.h"
#include "seed.h"

class Enemy : public Character {
  protected:
    bool holdCompass;
    bool isDead;
    
  public:
    // normal constructor
    Enemy(Position pos, CellType cType, int HP, int Atk, int Def, bool holdCompass);
    bool getCompass() override;
    void beAttacked(int atkVal) override;
    void Dead() override;
    bool haveDead();
    void setAtk() override;
    void setDef() override;
};

class Goblin : public Enemy {
  public:
    // normal constructor
    Goblin (Position pos, bool holdCompass);
    void beAttacked(int atkVal) override;
};

class Troll : public Enemy {
  public: 
    // normal constructor
    Troll (Position pos, bool holdCompass);
    void beAttacked(int atkVal) override;
};

class Werewolf : public Enemy {
  public: 
    // normal constructor
    Werewolf(Position pos, bool holdCompass);
    void beAttacked(int atkVal) override;
};

class Vampire : public Enemy {
  public: 
    // normal constructor
    Vampire(Position pos, bool holdCompass);
    void beAttacked(int atkVal) override;
};

class Phoenix : public Enemy {
    bool havedead;

  public: 
    // normal constructor
    Phoenix(Position pos, bool holdCompass);
    void beAttacked(int atkVal) override;
};

class Merchant : public Enemy {
  public: 
    // normal constructor
    Merchant(Position pos, bool holdCompass);
    void beAttacked(int atkVal) override;
};

class Dragon : public Enemy {
    Cell *protecthorde;
  public: 
    // normal constructor
    Dragon(Position pos, Cell *horde, bool holdCompass);
    void beAttacked(int atkVal) override;
};

#endif
