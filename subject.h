#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "observer.h"
#include "position.h"
#include "enum.h"

class Subject {
  std::vector<Observer*> observers;

 public:
  Subject();
  void attach( Observer *o );
  void detach( Observer *o );
  void notifyObservers(CellType ctype, Position pos);
  virtual ~Subject() = 0;
};

#endif
