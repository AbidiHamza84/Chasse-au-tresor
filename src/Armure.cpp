#include "../include/Armure.h"

Armure::Armure() : DefenseObject(90){}
Armure::Armure(Map* map) : DefenseObject(map,90){}

string Armure::getClass(){
  return "Armure";
}
