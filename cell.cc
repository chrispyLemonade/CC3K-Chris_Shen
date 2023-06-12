#include "cell.h"

Cell::Cell(Position pos, CellType cType) : pos{pos}, cType{cType} {}

Position Cell::getPos() {
    return pos;
}

void Cell::setPos(int row, int col) {
    pos.row = row;
    pos.col = col;
}

Cell::~Cell() {}
