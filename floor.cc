#include "floor.h"
#include "textdisplay.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "color.h"
using namespace std;

Floor::Floor() {
    for (int i = 0; i < 5; ++i) {
        fc.emplace_back(Chamber{});
    }

    ifstream emptyMap ("cc3kfloor.txt");
    
    char c;
    int i = 0;
    int j = 0;

    // initialize TextDisplay
    td = new TextDisplay(25, 79);

    for (int i = 0; i < 25; ++i) {
        vector<Cell*> tmp;
        for (int j = 0; j < 79; ++j) {
            tmp.emplace_back(new White{Position{i, j}});
        }
        grid.emplace_back(tmp);
    }

    i = 0;
    j = 0;

    while (emptyMap.get(c)) {
        switch(c) {
            case '|' :
                grid[i][j] = new VWall{Position{i, j}};
                grid[i][j]->attach(td);
                break;
            case '-' :
                grid[i][j] = new HWall{Position{i, j}};
                grid[i][j]->attach(td);
                break;
            case '.' :
                grid[i][j] = new Valid{Position{i, j}};
                grid[i][j]->attach(td);
                if (i < 7 && j < 30) {
                    fc[0].addPosition(Position{i, j});
                    fc[0].addSize();
                } else if ((i < 8) || (i < 13 && j > 60)) {
                    fc[1].addPosition(Position{i, j});
                    fc[1].addSize();
                } else if (i < 13 ) {
                    fc[2].addPosition(Position{i, j});
                    fc[2].addSize();
                } else if (j < 25) {
                    fc[3].addPosition(Position{i, j});
                    fc[3].addSize();
                } else {
                    fc[4].addPosition(Position{i, j});
                    fc[4].addSize();
                }
                break;
            case '+' :
                grid[i][j] = new Door{Position{i, j}};
                grid[i][j]->attach(td);
                break;
            case '#' :
                grid[i][j] = new Passway{Position{i, j}};
                grid[i][j]->attach(td);
                break;
            case ' ':
                grid[i][j]->attach(td);
                break;
            default:
                continue;
        }

        ++j;
        if (j >= 79) {
            ++i;
            j = 0;
        }
        if (i >= 25) {break;}
    }
}

// quick sort for enenyPos
int compare (const void * a, const void * b) {
    Enemy *enemy_1 = ((Enemy*)a);
    Enemy *enemy_2 = ((Enemy*)b);
    Position pos_1 = enemy_1->getPos();
    Position pos_2 = enemy_2->getPos();
    if (pos_1.row < pos_2.row) return -1;
    if (pos_1.row == pos_2.row) {
        if (pos_1.col < pos_2.col) return -1;
        if (pos_1.col == pos_2.col) return 0;
        if (pos_1.col > pos_2.col) return 1;
    }
    return 1;
}

void Floor::generation(bool hasBarrier) {

    hasStairs = 0;
    ctype = CellType::VALID;
    
    Seed newSeed = Seed{};
    srand(newSeed.getSeed());

    int cnum = randomChamber();
    Position pos = fc[cnum].randomPosition();
    grid[pos.row][pos.col] = new Stairs{Position{pos.row, pos.col}};
    grid[pos.row][pos.col]->notifyObservers(CellType::STAIRS, pos);
    // generate potion
    int type;
    for (int i = 0; i < 10; ++i) {
        cnum = randomChamber();
        pos = fc[cnum].randomPosition();
        while (grid[pos.row][pos.col]->getCType() != CellType::VALID) {
            pos = fc[cnum].randomPosition();
        }
        // try to deal with invalid input
        type = randomType(6);
        switch (type) {
            case 0:
                grid[pos.row][pos.col] = new Potion{pos, 10, 0, 0, nullptr};
                grid[pos.row][pos.col]->notifyObservers(CellType::POTION, pos);
                break;
            case 1:
                grid[pos.row][pos.col] = new Potion{pos, 0, 5, 0, nullptr};
                grid[pos.row][pos.col]->notifyObservers(CellType::POTION, pos);
                break;
            case 2:
                grid[pos.row][pos.col] = new Potion{pos, 0, 0, 5, nullptr};
                grid[pos.row][pos.col]->notifyObservers(CellType::POTION, pos);
                break;
            case 3:
                grid[pos.row][pos.col] = new Potion{pos, -10, 0, 0, nullptr};
                grid[pos.row][pos.col]->notifyObservers(CellType::POTION, pos);
                break;
            case 4:
                grid[pos.row][pos.col] = new Potion{pos, 0, -5, 0, nullptr};
                grid[pos.row][pos.col]->notifyObservers(CellType::POTION, pos);
                break;
            case 5:
                grid[pos.row][pos.col] = new Potion{pos, 0, 0, -5, nullptr};
                grid[pos.row][pos.col]->notifyObservers(CellType::POTION, pos);
                break;
        }
    }
    
    // generate treasure
    vector<Position> drg;
    vector<int> chambernum;
    for (int i = 0; i < 10; ++i) {
        cnum = randomChamber();
        pos = fc[cnum].randomPosition();
        while (grid[pos.row][pos.col]->getCType() != CellType::VALID) {
            pos = fc[cnum].randomPosition();
        }
        type = randomType(8);
        if (type < 5) {
            grid[pos.row][pos.col] = new Nhorde{pos};
            grid[pos.row][pos.col]->notifyObservers(CellType::TREASURE, pos);
        } else if (type < 7) {
            grid[pos.row][pos.col] = new Shorde{pos};
            grid[pos.row][pos.col]->notifyObservers(CellType::TREASURE, pos);
        } else {
            grid[pos.row][pos.col] = new Dhorde{pos, CellType::TREASURE, 6};
            grid[pos.row][pos.col]->notifyObservers(CellType::TREASURE, pos);
            drg.emplace_back(pos);
            chambernum.emplace_back(cnum);
        }

    }
    // put the barrier suit
    if (hasBarrier) {
        cnum = randomChamber();
        pos = fc[cnum].randomPosition();
        while (grid[pos.row][pos.col]->getCType() != CellType::VALID) {
            pos = fc[cnum].randomPosition();
        }
        grid[pos.row][pos.col] = new BarrierSuit{pos, 0};
        grid[pos.row][pos.col]->notifyObservers(CellType::BARRIERSUIT, pos);
        drg.emplace_back(pos);
        chambernum.emplace_back(cnum);
    }
                    
    int drgtot = drg.size();
    // Dragon
    for (int k = 0; k < drgtot; ++k) {
        bool halt = 0;
        for (int i = drg[k].row-1; i <= drg[k].row+1; ++i) {
            // if (i < 0 || i >= 25) continue;
            for (int j = drg[k].col-1; j <= drg[k].col+1; ++j) {
                // if (j < 0 || j >= 79) continue;
                if (i == drg[k].row && j == drg[k].col) continue;
                if (grid[i][j]->getCType() == CellType::VALID) {
                    grid[i][j] = new Dragon{Position{i,j}, grid[drg[k].row][drg[k].col], 0};
                    grid[pos.row][pos.col]->notifyObservers(CellType::DRAGON, pos);
                    halt = 1;
                    break;
                }
            }
            if (halt) break;
        }
    }
    drg.clear();
    chambernum.clear();


    // generate enemy
    int whocompass = rand() % (20 - drgtot);
    bool hasCompass = false;
    for (int i = 0; i < 20 - drgtot; ++i) {
        if (whocompass == i) {
            hasCompass = true;
        } else {
            hasCompass = false;
        }
        
        cnum = randomChamber();
        pos = fc[cnum].randomPosition();
        while (grid[pos.row][pos.col]->getCType() != CellType::VALID) {
            pos = fc[cnum].randomPosition();
        }
        type = randomType(18);

        Enemy *newEnemy;
        if (type < 4) {
            newEnemy = new Werewolf{pos, hasCompass};
        } else if (type < 7) {
            newEnemy = new Vampire{pos, hasCompass};
        } else if (type < 12) {
            newEnemy = new Goblin{pos, hasCompass};
        } else if (type < 14) {
            newEnemy = new Troll{pos, hasCompass};
        } else if (type < 16) {
            newEnemy = new Phoenix{pos, hasCompass};
        } else {
            newEnemy = new Merchant{pos, hasCompass};
        }
        grid[pos.row][pos.col] = newEnemy;
        enemyVec.emplace_back(newEnemy);
    }
    qsort(&*enemyVec.begin(), enemyVec.size(), sizeof(Enemy*), compare);
}


int Floor::randomChamber() {
    return rand() % 5;
}

int Floor::randomType(int total) {
    return rand() % total;
}

void Floor::placePc(Player *pc){
    Position pcpos = pc->getPos();
    grid[pcpos.row][pcpos.col] = pc;
}

// find the valid cell in the 1-bit radius of one enemy
vector<Position> Floor::enemyValidPos(Position pos) {
    vector<Position> validPos;
    for (int i = -1; i <= 1; ++i) {
        if (pos.row + i < 0 || pos.row + i >= 25) { continue; } // there are 25 rows
        for (int j = -1; j <= 1; ++j) {
            if (pos.col + j < 0 || pos.col + j >= 79) { continue; } // there are 79 cols
            if (i == 0 && j == 0) { continue; }

            if (grid[pos.row + i][pos.col + j]->getCType() == CellType::VALID){
                validPos.emplace_back(Position{i, j});
            }
            if (grid[pos.row + i][pos.col + j]->getCType() == CellType::PC) {
                validPos.clear();
                return validPos;
            }
        }
    }

    return validPos; 
}

void cellPrint(CellType gType) {
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
        case CellType::VALID:
            cout << "Valid";
            break;
    }

}


// move all enemies to random directions
void Floor::enemyMove() {
    for (size_t i = 0; i < enemyVec.size(); ++i) {
        if (enemyVec[i]->haveDead()) continue;
        Position crtPos = enemyVec[i]->getPos();
        vector<Position> validPos = enemyValidPos(crtPos);

        // if there is no valid space--dont move
        if (validPos.size() == 0) {continue;}

        // random direction
        Seed newSeed = Seed{};
        srand(newSeed.getSeed());
        int randIndex = rand() % validPos.size();
        Position relativePos = validPos[randIndex];
        Position nxtPos = Position{crtPos.row+relativePos.row, crtPos.col+relativePos.col};
        grid[nxtPos.row][nxtPos.col] = enemyVec[i];
        enemyVec[i]->setPos(nxtPos.row, nxtPos.col);
        grid[crtPos.row][crtPos.col] = new Valid{Position{crtPos.row, crtPos.col}};
    }
    qsort(&*enemyVec.begin(), enemyVec.size(), sizeof(Enemy*), compare);
}


std::ostream &operator<<(std::ostream &out, const Floor &f) {
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 79; ++j) {
            CellType cType = f.grid[i][j]->getCType();
            switch(cType) {
                case CellType::VAMPIRE:
                    out << RED << 'V' << RESET;
                    break;
                case CellType::WEREWOLF:
                    out << RED << 'W' << RESET;
                    break;
                case CellType::TROLL:
                    out << RED << 'T' << RESET;
                    break;
                case CellType::MERCHANT:
                    out << RED << 'M' << RESET;
                    break;
                case CellType::GOBLIN:
                    out << RED << 'N' << RESET;
                    break;
                case CellType::DRAGON:
                    out << RED << 'D' << RESET;
                    break;
                case CellType::PHOENIX:
                    out << RED << 'X' << RESET;
                    break;
                case CellType::PC:
                    out << BLUE << '@' << RESET;
                    break;
                case CellType::DOOR:
                    out << '+';
                    break;
                case CellType::PASSWAY:
                    out << '#';
                    break;
                case CellType::STAIRS:
                    if (f.hasStairs) {
                        out << '\\';
                    } else {
                        out << '.';
                    }
                    break;
                case CellType::POTION:
                    out << GREEN << 'P' << RESET;
                    break;
                case CellType::VALID:
                    out <<  '.';
                    break;
                case CellType::VWALL:
                    out <<  '|';
                    break;
                case CellType::HWALL:
                    out <<  '-';
                    break;
                case CellType::WHITE:
                    out <<  ' ';
                    break;
                case CellType::COMPASS:
                    out <<  'C';
                    break;
                case CellType::BARRIERSUIT:
                    out <<  YELLOW << 'B' << RESET;
                    break;
                case CellType::TREASURE:
                    out <<  YELLOW << 'G' << RESET;
                    break;
            }
        }
        out << endl;
    }
    return out;
}


Floor::~Floor() {
    grid.clear();
    fc.clear();
    enemyVec.clear();
    // if (td != nullptr) delete td;
}
