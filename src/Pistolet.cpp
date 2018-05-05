#include "../include/Pistolet.h"

Pistolet::Pistolet() : AttackObject(50){}

Pistolet::Pistolet(Map* map) : AttackObject(map,50){}

string Pistolet::getClass(){
  return "Pistolet";
}
