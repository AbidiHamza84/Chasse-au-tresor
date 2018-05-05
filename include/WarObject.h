#ifndef WAR_OBJECT_H
#define WAR_OBJECT_H
#include "Object.h"

class WarObject : public Object {
public:
  WarObject(Map*,int purcent);
  WarObject(int purcent);
  virtual string getClass();
  virtual string getType(){};
  bool isWin();
protected:
  int win_purcent;
  char t_win[10];
};

#endif
