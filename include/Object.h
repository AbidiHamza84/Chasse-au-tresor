#ifndef OBJECT_H
#define OBJECT_H
#include "Map.h"
#include <iostream>
#include "Cord.h"

using namespace std ;
class Object {
  public:
    Object(Map*);
    Object();
    virtual string getClass();
    virtual string getType() {};
    Cord getPos();
  protected:
    Map* map ;
    Cord cord ;
};

#endif
