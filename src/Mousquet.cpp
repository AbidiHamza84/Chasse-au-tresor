#include "../include/Mousquet.h"

Mousquet::Mousquet() : AttackObject(50){}

Mousquet::Mousquet(Map * map) : AttackObject(map,50){}

string Mousquet::getClass(){
  return "Mousquet";
}
