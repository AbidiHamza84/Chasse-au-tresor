#ifndef PISTOLET_H
#define PISTOLET_H
#include "AttackObject.h"

class Pistolet : public AttackObject{
public:
  Pistolet(Map*);
  Pistolet();
  virtual string getClass();
};


#endif
