#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "observer.h"
#include "subject.h"
#include "potion.h"
#include "treasure.h"
#include "enemy.h"
#include "chamber.h"
#include "position.h"
#include "thing.h"
#include "seed.h"
#include "enum.h"
#include <ostream>
#include <vector>

class TextDisplay;
class Observer;

class Floor {
    std::vector<std::vector<Cell*>> grid;
    std::vector<Chamber> fc; // chamger in floor
    std::vector<Enemy*> enemyVec; // enemy in floor
    CellType ctype; // where pc stands
    bool hasStairs; // whether the stairs appear
    TextDisplay *td = nullptr; // the textdisplay

  public:
    Floor();
    void generation(bool hasBarrier);
    int randomChamber();
    int randomType(int total);
    void placePc(Player *pc);
    bool validDirect(DirectionType dir, Position pos);
    std::vector<Position> enemyValidPos(Position pos);
    void enemyMove();
    void floorPrint();
    ~Floor();

    friend std::ostream &operator<<(std::ostream &out, const Floor &f);
    friend class Game;
};

#endif
