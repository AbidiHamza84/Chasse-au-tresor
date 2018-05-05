#ifndef PELLE_H
#define PELLE_H
#include "SafeObject.h"

class Pelle : public SafeObject {
public:
  Pelle(Map*);
  Pelle();
  virtual string getClass();
};


#endif
