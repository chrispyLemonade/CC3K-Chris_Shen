#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "enum.h"
#include "position.h"

class Subject;

class Observer {
  public:
    virtual void notify(Subject &whonotified, CellType CType, Position pos) = 0;
    virtual ~Observer();
};

#endif
