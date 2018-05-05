#include "../include/AttackObject.h"

AttackObject::AttackObject(int purcent) : WarObject(purcent){}

AttackObject::AttackObject(Map* map , int purcent) : WarObject(map,purcent){}

string AttackObject::getType(){
  return "ATTACK";
}

string AttackObject::getClass(){
  return "AttackObject";
}
