#include "../include/SafeObject.h"

SafeObject::SafeObject(Map* map) : Object(map){}

SafeObject::SafeObject() : Object(){}

string SafeObject::getClass(){
  return "SafeObject";
}

string SafeObject::getType(){
  return "SAFE";
}
