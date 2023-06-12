#include "textdisplay.h"
#include "enum.h"
#include <iostream>
#include <fstream>
using namespace std;

// the normal constructor
TextDisplay::TextDisplay(int row, int col) : row{row}, col{col} {
    // intialize a 25 * 79 empty floor
    for (int i = 0; i < row; ++i) {
        vector<char> r;
    for (int j = 0; j < col; ++j) {
        r.emplace_back(' ');
    }
        theFloor.emplace_back(r);
    }
    
    // read in the empty floor
    ifstream emptyMap ("cc3kfloor.txt");
    char c;
    int i = 0;
    int j = 0;
    while (emptyMap.get(c)) {
        if (c == '|' || c == '-' || c == '.' || c == '+' || c == '#' || c == ' ') {
            theFloor[i][j] = c;
        } else {
            continue;
        }
        ++j;
        if (j >= 79) {
            ++i;
            j = 0;
        }
        if (i >= 25) { break; }
    }
}


// the notify function
void TextDisplay::notify(Subject &whoNotified, CellType ctype, Position pos) {
    int r = pos.row;
    int c = pos.col;
    switch (ctype) {
        case CellType::VAMPIRE:
            theFloor[r][c] = 'V';
            break;
        case CellType::WEREWOLF:
            theFloor[r][c] = 'W';
            break;
        case CellType::TROLL:
            theFloor[r][c] = 'T';
            break;
        case CellType::MERCHANT:
            theFloor[r][c] = 'M';
            break;
        case CellType::GOBLIN:
            theFloor[r][c] = 'N';
            break;
        case CellType::DRAGON:
            theFloor[r][c] = 'D';
            break;
        case CellType::PHOENIX:
            theFloor[r][c] = 'X';
            break;
        case CellType::PC:
            theFloor[r][c] =  '@';
            break;
        case CellType::DOOR:
            theFloor[r][c] = '+';
            break;
        case CellType::PASSWAY:
            theFloor[r][c] =  '#';
            break;
        case CellType::STAIRS:
            theFloor[r][c] = '\\';
            break;
        case CellType::POTION:
            theFloor[r][c] = 'P';
            break;
        case CellType::VALID:
            theFloor[r][c] = '.';
            break;
        case CellType::VWALL:
            theFloor[r][c] = '|';
            break;
        case CellType::HWALL:
            theFloor[r][c] = '-';
            break;
        case CellType::WHITE:
            theFloor[r][c] = ' ';
            break;
        case CellType::COMPASS:
            theFloor[r][c] = 'C';
            break;
        case CellType::BARRIERSUIT:
            theFloor[r][c] = 'B';
            break;
        case CellType::TREASURE:
            theFloor[r][c] = 'G';
            break;
        default:
            break;
    }
}

// the operator overloading print function
ostream &operator<<(ostream &out, const TextDisplay &td) {
    for(int i = 0; i < 25; ++i) {
        for (int j = 0; j < 79; ++j) {
            char c = td.theFloor[i][j];
            out << c;
        }
        out << endl;
    }
    return out;
}
