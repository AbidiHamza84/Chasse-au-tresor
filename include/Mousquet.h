#ifndef MOUSQUET_H
#define MOUSQUET_H
#include "AttackObject.h"

class Mousquet : public AttackObject{
public:
  Mousquet(Map*);
  Mousquet();
  virtual string getClass();
};

#endif
