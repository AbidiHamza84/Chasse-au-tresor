#ifndef DEFENSE_OBJECT_H
#define DEFENSE_OBJECT_H
#include "WarObject.h"

class DefenseObject : public WarObject {
public:
  DefenseObject(Map*,int purcent);
  DefenseObject(int purcent);
  virtual string getClass();
  string getType();
};

#endif
