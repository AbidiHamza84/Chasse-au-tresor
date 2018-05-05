#include "../include/Object.h"

Object::Object(Map* map){
  this->map = map ;
  srand(time(NULL));
  do{
    cord.x = rand()% this->map->getHeight();
    cord.y = rand()% this->map->getSegmentWidth();
  }while(this->map->accessible(cord) == false);
}

Object::Object(){
  this->map = NULL ;
}

string Object::getClass(){
  return "Object";
}

Cord Object::getPos(){
  if(this->map)
    return cord ;
  else{
    cord.x = -1;
    cord.y = -1;
    return cord ;
  }
}
