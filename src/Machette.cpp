#include "../include/Machette.h"

Machette::Machette() : AttackObject(50){}

Machette::Machette(Map* map) : AttackObject(map,50){}

string Machette::getClass(){
  return "Machette";
}
