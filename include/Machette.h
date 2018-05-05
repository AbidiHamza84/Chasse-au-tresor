#ifndef MACHETTE_H
#define MACHETTE_H
#include "AttackObject.h"

class Machette : public AttackObject{
public:
  Machette(Map*);
  Machette();
  virtual string getClass();
};


#endif
