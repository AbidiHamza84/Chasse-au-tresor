#include "../include/Pelle.h"

Pelle::Pelle() : SafeObject(){}

Pelle::Pelle(Map* map) : SafeObject(map){}

string Pelle::getClass(){
  return "Pelle";
}
