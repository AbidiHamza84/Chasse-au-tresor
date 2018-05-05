#ifndef ATTACK_OBJECT_H
#define ATTACK_OBJECT_H
#include "WarObject.h"

class AttackObject : public WarObject{
public:
  AttackObject(Map*,int purcent);
  AttackObject(int purcent);
  virtual string getClass();
  string getType();
};


#endif
