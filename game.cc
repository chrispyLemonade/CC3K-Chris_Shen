#include "game.h"
#include "enum.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

Game::Game(): pc{nullptr}, f{nullptr}, bFloor{0}, floorNum{0}, merchant_hostile{0} {}

void Game::gameStart(bool hasMap, string fileName) {
    this->hasMap = hasMap;
    this->fileName = fileName;
    for (int i = 0; i < 6; ++i) {
        floor.emplace_back(new Floor{});
    }
    // generate five floors;

    f = floor[5];

    if (hasMap) {
        ifstream fileMap (fileName);

        int k = 0;
        int i = 0;
        int j = 0;
        bool holdCompass = true;
        Enemy *newEnemy = nullptr;

        char c;
        while (fileMap.get(c)) {
            switch(c) {
                case '@':
                    pc = new Human{Position{i,j}};
                    break;
                case '0':
                    floor[k]->grid[i][j] = new Potion{Position{i, j}, 10, 0, 0, nullptr};
                    break;
                case '1':
                    floor[k]->grid[i][j] = new Potion{Position{i, j}, 0, 5, 0, nullptr};
                    break;
                case '2':
                    floor[k]->grid[i][j] = new Potion{Position{i, j}, 0, 0, 5, nullptr};
                    break;
                case '3':
                    floor[k]->grid[i][j] = new Potion{Position{i, j}, -10, 0, 0, nullptr};
                    break;
                case '4':
                    floor[k]->grid[i][j] = new Potion{Position{i, j}, 0, -5, 0, nullptr};
                    break;
                case '5':
                    floor[k]->grid[i][j] = new Potion{Position{i, j}, 0, 0, -5, nullptr};
                    break;
                case '6':
                    floor[k]->grid[i][j] = new Nhorde{Position{i,j}};
                    break;
                case '7':
                    floor[k]->grid[i][j] = new Shorde{Position{i, j}};
                    break;
                case '9':
                    floor[k]->grid[i][j] = new Dhorde{Position{i,j}, CellType::TREASURE, 6};
                    break;
                case '\\':
                    floor[k]->grid[i][j] = new Stairs{Position{i,j}};
                    break;
                case 'B':
                    bFloor = k;
                    floor[k]->grid[i][j] = new BarrierSuit{Position{i,j}, 0};
                    break;
                case 'V':
                    newEnemy = new Vampire{Position{i,j}, holdCompass};
                    floor[k]->grid[i][j] = newEnemy;
                    floor[k]->enemyVec.emplace_back(newEnemy);
                    holdCompass = false;
                    break;
                case 'W':
                    newEnemy = new Werewolf{Position{i,j}, holdCompass};
                    floor[k]->grid[i][j] = newEnemy;
                    floor[k]->enemyVec.emplace_back(newEnemy);
                    holdCompass = false;
                    break;
                case 'N':
                    newEnemy = new Goblin{Position{i,j}, holdCompass};
                    floor[k]->grid[i][j] = newEnemy;
                    floor[k]->enemyVec.emplace_back(newEnemy);
                    holdCompass = false;
                    break;
                case 'M':
                    newEnemy = new Merchant{Position{i,j}, holdCompass};
                    floor[k]->grid[i][j] = newEnemy;
                    floor[k]->enemyVec.emplace_back(newEnemy);
                    holdCompass = false;
                    break;
                case 'D':
                    newEnemy = new Dragon{Position{i,j}, nullptr, holdCompass};
                    floor[k]->grid[i][j] = newEnemy;
                    holdCompass = false;
                    break;
                case 'X':
                    newEnemy = new Phoenix{Position{i,j}, holdCompass};
                    floor[k]->grid[i][j] = newEnemy;
                    floor[k]->enemyVec.emplace_back(newEnemy);
                    holdCompass = false;
                    break;
                case 'T':
                    newEnemy = new Troll{Position{i,j}, holdCompass};
                    floor[k]->grid[i][j] = newEnemy;
                    floor[k]->enemyVec.emplace_back(newEnemy);
                    holdCompass = false;
                    break;
                case '\n':
                    continue;
                    break;
            }
            j++;
            if (j >= 79) {
                i++;
                holdCompass = true;
                if (i >= 25) {
                    floor[k]->hasStairs = 0;
                    k++;
                    i = 0;
                }
                j=0;
            }
        }

    } else {
        // generate pc
        Seed newSeed = Seed{};
        srand(newSeed.getSeed());
        crtchamber = floor[0]->randomChamber();
        Position pos = floor[0]->fc[crtchamber].randomPosition();
        pc = new Human{pos};
        // generate BarrierSuit
        bFloor = rand() % 5 + 1;

        for (int i = 0; i < 5; ++i) {
            if (i == bFloor) {
                floor[i]->generation(true);
            } else {
                floor[i]->generation(false);
            }
        }
    }
    
    floorNum = 1;
    merchant_hostile = 0;
    printInfo();
}

void Game::nextFloor() {
    // first floor in floor[0]
    f = floor[floorNum-1];
    f->ctype = CellType::VALID;
    f->placePc(pc);
    printInfo();
    cout << "PC moved to the next floor." << endl;
}

void Game::printInfo() {
    cout << *f;
    cout << "Race: ";
    switch (pc->getRace()) {
        case RaceType::HUMAN:
            cout << "Human ";
            break;
        case RaceType::DWARF:
            cout << "Dwarf ";
            break;
        case RaceType::ELVES:
            cout << "Elves ";
            break;
        case RaceType::ORC:
            cout << "Orc   ";
            break;
    }

    cout << "Gold: ";
    if (pc->getRace() == RaceType::ORC) {
        bool hasHalf = false;
        cout << pc->getGold() / 2;
        if (pc->getGold() % 2 != 0) {
            cout << ".5";
        }
    } else {
        cout << pc->getGold();
    }
    cout << "                                                ";
    cout << "Floor: ";
    cout << floorNum << endl;
    
    cout << "HP: " << pc->getHP() << endl;
    cout << "Atk: " << pc->getAtk() << endl;
    cout << "Def: " << pc->getDef() << endl;
    cout << "Action: ";
}

void Game::setRace(RaceType race) {
    Player *tmp = nullptr;
    Position pcpos = pc->getPos();
    switch (race) {
        case RaceType::HUMAN:
            tmp = new Human{pcpos};
            break;
        case RaceType::ELVES:
            tmp = new Elves{pcpos};
            break;
        case RaceType::DWARF:
            tmp = new Dwarf{pcpos};
            break;
        case RaceType::ORC:
            tmp = new Orc{pcpos};
            break;    
    }

    //delete pc;
    pc = tmp;
    f->grid[pcpos.row][pcpos.col] = pc;

    printInfo();
}

Position Game::findDirPos(DirectionType dir) {
    int x = 0, y = 0;
    switch (dir) {
        case DirectionType::NO:
            x--;
            break;
        case DirectionType::SO:
            x++;
            break;
        case DirectionType::WE:
            y--;
            break;
        case DirectionType::EA:
            y++;
            break;
        case DirectionType::NW:
            x--;
            y--;
            break;
        case DirectionType::NE:
            x--;
            y++;
            break;
        case DirectionType::SW:
            x++;
            y--;
            break;
        case DirectionType::SE:
            x++;
            y++;
            break;
    }
    return Position{x, y};
}


int Game::pickUpPotion(DirectionType dir) {
    Position pcpos = pc->getPos();
    Position changepos = findDirPos(dir);
    int x = pcpos.row + changepos.row;
    int y = pcpos.col + changepos.col;
    
    if (f->grid[x][y]->getCType() != CellType::POTION) {
        printInfo();
        cout << "Error! Please enter a valid direction:" << endl;
        return 1;
    }

    Cell *tmp = f->grid[x][y];
    if (tmp->getHP() == 0) {
        if (tmp->getAtk() != 0) {
            cout << "Picked up the potion! Atk added by " << tmp->getAtk() << "." << endl;
        } else if (tmp->getDef() != 0) {
            cout << "Picked up the potion! Def added by " << tmp->getDef() << "." << endl;
        }

        if (pc->getRace() == RaceType::ELVES) {
            pc = new Potion{pcpos, 0, abs(tmp->getAtk()), abs(tmp->getDef()), pc};
        } else {
            pc = new Potion{pcpos, 0, tmp->getAtk(), tmp->getDef(), pc};
        }
        f->grid[pcpos.row][pcpos.col] = pc;
    } else {
        pc->modifyHP(tmp->getHP());
        if (pc->getHP() <= 0) {
            gameOver();
            return 0;
        }
        cout << "Picked up the potion! HP added by " << tmp->getHP() << "." << endl;
    }
    f->grid[x][y] = new Valid{Position{x, y}};

    bool returnValue = EnemyAttack(false);
    printInfo();
    cout << "Player picked up the potion." << endl;
    return returnValue;
}


void Game::gameOver() {
    cout << endl;
    cout << endl;
    int finalScore = pc->getGold();
    if (pc->getRace() == RaceType::HUMAN) {
        finalScore += finalScore / 2;
    } else if (pc->getRace() == RaceType::ORC) {
        finalScore /= 2;
    }
    if (floorNum > 5) {
        cout << "Congrats. You have conquered the dungeon!" << endl;
        cout << "Score: " << finalScore << endl;
    }
    if (pc->getHP() <= 0) {
        cout << "Another warrior fell down in the dungeon." << endl;
    }
    if (finalScore == 0) {
        cout << "REALLY? O SCORE? THAT'S ALL U GOT?" << endl;
    } else if (finalScore <= 5) {
        cout << "Don't give up, man." << endl;
        cout << "Try a few more times so that u can get a higher score!" << endl;
    } else if (finalScore <= 15) {
        cout << "Yo, u r getting better at this."<< endl;
    } else if (finalScore <= 50) {
        cout << "U did a grrrrrreat job." << endl;
    } else if (finalScore == 246) {
        cout << "Difficulty set to: HELL!" << endl;
    }
}


DirectionType Game::posToDir(int x, int y) {
    if (x == -1 && y == -1) {
        return DirectionType::NW;
    }

    if (x == -1 && y == 0) {
        return DirectionType::NO;
    }

    if (x == -1 && y == 1) {
        return DirectionType::NE;
    }

    if (x == 0 && y == -1) {
        return DirectionType::WE;
    }

    if (x == 0 && y == 1) {
        return DirectionType::EA;
    }

    if (x == 1 && y == -1) {
        return DirectionType::SW;
    }

    if (x == 1 && y == 0) {
        return DirectionType::SO;
    }

    if (x == 1 && y == 1) {
        return DirectionType::SE;
    }
}


// PC move one block with specified direction
int Game::pcMove(DirectionType dir) {
    Position relativePos = findDirPos(dir);
    Position pcPos = pc->getPos();
    Position nextPos = Position{pcPos.row + relativePos.row, pcPos.col + relativePos.col};
    CellType nextType = f->grid[nextPos.row][nextPos.col]->getCType();        

    // send error message when it is not a legal move
    if (nextType == CellType::VAMPIRE ||
        nextType == CellType::WEREWOLF ||
        nextType == CellType::TROLL ||
        nextType == CellType::MERCHANT ||
        nextType == CellType::GOBLIN ||
        nextType == CellType::DRAGON ||
        nextType == CellType::PHOENIX ||
        nextType == CellType::POTION ||
        nextType == CellType::VWALL ||
        nextType == CellType::HWALL ||
        nextType == CellType::WHITE) {
            cout << *f;
            cout << "Invalid move. Plz try something else" << endl;
            return 1;
        }

    // when it is dragon horde
    if (nextType == CellType::TREASURE) {// not included dragon hoard yet!!! (checked)
                                            // and Warning: the class relationship was changed (checked)
                                            // also there are different (checked)
        
        bool hasDragon = f->grid[nextPos.row][nextPos.col]->getHasDragon();
        if ((f->grid[nextPos.row][nextPos.col]->getGold() == 6 && hasDragon)
        || (f->grid[nextPos.row][nextPos.col]->getGold() == 0 && hasDragon)) {
            cout << "Inaccessible. Plz defeat the dragon to grab the reward." << endl;
            return 1;
        } else {
            if (f->grid[pcPos.row][pcPos.col]->getGold() == 0 && !hasDragon) {
                pc->setHaveBSuit(true);
            }
            int treasureValue = f->grid[nextPos.row][nextPos.col]->getGold();
            cout << "Gold Consumed! Value: " << treasureValue << "." << endl;
            nextType = CellType::VALID;

            if (pc->getRace() == RaceType::DWARF) {
                pc->addGold(treasureValue * 2);
            } else {
                pc->addGold(treasureValue);
            }
        }
    } else if (nextType == CellType::DOOR) {
        Player *tmp = pc->extractPC();
        pc = tmp;
    } else if (nextType == CellType::STAIRS) {
        floorNum++;
        if (floorNum > 5) {
            gameOver();
            return 0;
        } else {
            pc->setPos(nextPos.row, nextPos.col);
            nextFloor();
            return 1;
        }
    } else if (nextType == CellType::COMPASS) {
        pc->addGold(f->grid[nextPos.row][nextPos.col]->getGold());
        f->hasStairs = true;
        nextType = CellType::VALID;
        cout << endl;
        cout << "Player picked up the compass." << endl;
    }

    // move the pc and set cType
    if (f->ctype == CellType::PASSWAY) {
        f->grid[pcPos.row][pcPos.col] = new Passway{pcPos};
    } else if (f->ctype == CellType::DOOR) {
        f->grid[pcPos.row][pcPos.col] = new Door{pcPos};
    } else if (f->ctype == CellType::VALID) {
        f->grid[pcPos.row][pcPos.col] = new Valid{pcPos};
    }
    f->ctype = nextType;
    f->grid[nextPos.row][nextPos.col] = pc;
    pc->setPos(nextPos.row, nextPos.col);

    DirectionType atkDir;
    int totEnemy = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            CellType surroundType = f->grid[nextPos.row + i][nextPos.col + j]->getCType();
            if ( surroundType== CellType::VAMPIRE
            || surroundType == CellType::WEREWOLF
            || surroundType == CellType::TROLL
            || surroundType == CellType::MERCHANT
            || surroundType == CellType::GOBLIN
            || surroundType == CellType::DRAGON
            || surroundType == CellType::PHOENIX) {
                totEnemy++;
                atkDir = posToDir(i, j);
            }
        }
    }

    if (totEnemy == 0) {
        f->enemyMove();
        printInfo();
        cout << "Player moved." << endl;
    } else if (totEnemy == 1) {
        return pcAttack(atkDir);
    } else {
        printInfo();
        cout << "Player is prompted to choose one enemy to attack." << endl;
        cout << "Multiple enemies around! Please choose your attack direction:" << endl;
    }
    return 1;
}

bool Game::isEnemy(CellType gType) {
    if (gType != CellType::VAMPIRE 
    && gType != CellType::WEREWOLF 
    && gType != CellType::TROLL 
    && gType != CellType::MERCHANT
    && gType != CellType::GOBLIN
    && gType != CellType::DRAGON
    && gType != CellType::PHOENIX)
        return false;
    return true;
}

void Game::EnemyTypePrint(CellType gType) {
    switch (gType) {
        case CellType::VAMPIRE:
            cout << "Vampire";
            break;
        case CellType::GOBLIN:
            cout << "Goblin";
            break;
        case CellType::WEREWOLF:
            cout << "WereWolf";
            break;
        case CellType::MERCHANT:
            cout << "Merchant";
            break;
        case CellType::DRAGON:
            cout << "Dragon";
            break;
        case CellType::PHOENIX:
            cout << "Phoneix";
            break;
        case CellType::TROLL:
            cout << "Troll";
            break;
    }

}

int Game::EnemyAttack(bool isAtkMode) {
    Position pcPos = pc->getPos();
    for (int i = pcPos.row-1; i <= pcPos.row+1; ++i) {
        if (i < 0 || i > 25) continue;
        for (int j = pcPos.col-1; j <= pcPos.col+1; ++j) {
            if (j < 0 || j > 79) continue;
            if (i == pcPos.row && j == pcPos.col) continue;

            CellType gType = f->grid[i][j]->getCType();
            if (!isEnemy(gType)) continue;
            

            Seed newSeed = Seed();
            srand(newSeed.getSeed());
            int miss = rand() % 2;
            if (miss == 0) {
                cout << "Oops...., ";
                EnemyTypePrint(gType);
                cout << " missed the attack.";
                cout << endl;
                continue;
            }

            // special case
            // merchant hostile
            if (gType == CellType::MERCHANT && merchant_hostile == false) continue;
            // dragon hostile
            if (gType == CellType::DRAGON) {
                bool arroundHorde = false;
                for (int a = -1; a <= 1; ++a) {
                    for (int b = -1; b <= 1; ++b) {
                        CellType tmpType = f->grid[pcPos.row + a][pcPos.col + b]->getCType();
                        if (tmpType == CellType::TREASURE) {
                            int treasureValue = f->grid[pcPos.row + a][pcPos.col + b]->getGold();
                            if (treasureValue == 6 || treasureValue == 0) {
                                arroundHorde = true;
                                break;
                            }
                        }
                    }
                }
                if (!arroundHorde) continue;
            }
            // goblin attack
            if (gType == CellType::GOBLIN) {
                if (pc->getGold() > 0) {
                    pc->addGold(-1);
                    f->grid[i][j]->addGold(1);
                }
            }

            pc->beAttacked(f->grid[i][j]->getAtk()); 
            cout << "PC was attacked by ";
            EnemyTypePrint(gType);
            cout << "." << endl;

            if (pc->getHP() <= 0) {
                gameOver();
                return 0;
            }
        }
    }
    f->enemyMove();
    if (isAtkMode) {
        printInfo();
        cout << "Player is in attacking mode." << endl;
    }
    return 1;
}

int Game::pcAttack(DirectionType dir) {
    Position pcpos = pc->getPos();
    Position changepos = findDirPos(dir);
    int x = pcpos.row + changepos.row;
    int y = pcpos.col + changepos.col;

    CellType gType = f->grid[x][y]->getCType();
    if (!isEnemy(gType)) {
        cout << "Error! No enemies around." << endl;
        return 1;
    }

    Cell *enemy = f->grid[x][y];
    enemy->beAttacked(pc->getAtk()); 

    if (gType == CellType::MERCHANT) merchant_hostile = true;

    if (enemy->getHP() <= 0) {
        EnemyTypePrint(gType);
        cout << " has been slain." << endl;
        int totGold = 1;
        if (enemy->getCType() == CellType::GOBLIN) {
            totGold += enemy->getGold();
        }

        if (pc->getRace() == RaceType::DWARF) {
            pc->addGold(totGold*2);
        } else {
            pc->addGold(totGold);
        }

        f->grid[x][y]->Dead();

        if (enemy->getCompass()) {
            if (enemy->getCType() == CellType::MERCHANT) {
                f->grid[x][y] = new Compass{Position{x, y}, 4};
            } else {
                f->grid[x][y] = new Compass{Position{x,y}, 0};
            }
        } else if (enemy->getCType() == CellType::MERCHANT) {
            f->grid[x][y] = new Mhorde{Position{x,y}};
        } else {
            f->grid[x][y] = new Valid{Position{x,y}};
        }
    }

    return EnemyAttack(true);
}

void Game::developerMode() {
    pc->modifyHP(246);
    pc->setAtk();
    pc->setDef();
    for (int i = 0; i < 5; ++i) floor[i]->hasStairs = 1;
}

Game::~Game() {
    //if (pc != nullptr) delete pc;
    //if (f != nullptr) delete f;
    floor.clear();
}
