#include "decorator.h"

Decorator:: Decorator(Position pos, CellType cType, int HP, int Atk, int Def, Player *component ) : 
      Player{pos, cType, HP, Atk, Def, 0, RaceType::HUMAN}, component{component} {}


Decorator::~Decorator() {  /*delete component;*/ }
