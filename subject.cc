#include "subject.h"

Subject::Subject() {}
Subject::~Subject() {}

void Subject::attach( Observer *o ) {
  observers.emplace_back(o);
}

void Subject::detach( Observer *o ) {
  for ( auto it = observers.begin(); it != observers.end(); ++it ) {
    if ( *it == o ) {
      observers.erase(it);
      break;
    }
  }
}

void Subject::notifyObservers(CellType ctype, Position pos) {
  for (auto ob : observers) ob->notify(*this, ctype, pos);
}