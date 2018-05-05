#include "../include/DefenseObject.h"

DefenseObject::DefenseObject(int purcent) : WarObject(purcent){}

DefenseObject::DefenseObject(Map* map , int purcent) : WarObject(map , purcent){}

string DefenseObject::getType(){
  return "DEFENSE";
}

string DefenseObject::getClass(){
  return "DefenseObject";
}
