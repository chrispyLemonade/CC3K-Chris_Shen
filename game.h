#ifndef __GAME_H__
#define __GAME_H__
#include "enum.h"
#include "floor.h"
#include "string.h"
#include "seed.h"

class Game {
  Player *pc;
  std::vector<Floor*> floor;
  Floor *f;
  int bFloor;
	int floorNum;
	bool merchant_hostile;
  bool hasMap;
  std::string fileName;
  int crtchamber; // restore the current chamber number where pc in
  Position findDirPos(DirectionType dir);
  DirectionType posToDir(int x, int y);
  bool isEnemy(CellType gType);
  void EnemyTypePrint(CellType gType);

  public:
    Game();
    void gameStart(bool hasMap, std::string fileName);
    void nextFloor();
    void setRace(RaceType race);
    int pickUpPotion(DirectionType dir);
    void gameOver();
    int pcMove(DirectionType dir);
    void gameClear();
    int calScore();
    int pcAttack(DirectionType dir);
    int EnemyAttack(bool isAtkMode);
    void printInfo();
    void developerMode();
    ~Game();

    friend class Floor;
};

#endif
