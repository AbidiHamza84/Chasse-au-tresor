#ifndef SAFE_OBJECT_H
#define SAFE_OBJECT_H
#include "Object.h"
class SafeObject : public Object{
public:
  SafeObject(Map*);
  SafeObject();
  virtual string getClass();
  virtual string getType();
};

#endif
