#ifndef ARMURE_H
#define ARMURE_H
#include "DefenseObject.h"

class Armure : public DefenseObject {
public:
  Armure(Map*);
  Armure();
  virtual string getClass();
};




#endif
