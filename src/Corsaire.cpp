#include "../include/Corsaire.h"


Corsaire::Corsaire(Map* &map): Personne(map){
  nb_objects = 0 ;
  id = static_id++;
  alive = true ;

  enemyCord.x = -1 ;
  enemyCord.y = -1 ;

  do{
    cord.x = rand()%map->getHeight();
    cord.y = rand()%map->getSegmentWidth();
  }while(map->accessible(cord) == false || map->thereIsPlayerIn(cord) == true);
}

Corsaire::Corsaire(Map* &map,int x, int y) : Personne(map,x,y){
  id = static_id++;
  nb_objects = 0 ;
  alive = true ;
  cord = Cord{x,y};
  enemyCord.x = -1 ;
  enemyCord.y = -1 ;
}
Corsaire::Corsaire(Map* &map,Cord cord) : Personne(map,cord){
  id = static_id++;
  nb_objects = 0 ;
  alive = true ;
  this->cord = cord;
  enemyCord.x = -1 ;
  enemyCord.y = -1 ;
}
Corsaire::~Corsaire(){

}

int Corsaire::seDeplacer(char direction){
  system("cvlc ../media/bip.mp3 -q 2> /dev/null &");
  int displaced = BLOCK;
  switch (direction) {
    case 'A':{
      if(map){
        cord.x -=STEP;
        displaced = map->accessible(cord);
        if(displaced == BLOCK)
          cord.x +=STEP;
        }
      }
    break;

    case 'B':{
      if(map){
        cord.x +=STEP;
        displaced = map->accessible(cord);
        if(displaced == BLOCK)
          cord.x -=STEP;
      }
    }
    break;

    case 'C':{
      if(map){
        cord.y +=STEP;
        displaced = map->accessible(cord);
        if(displaced == BLOCK)
          cord.y -=STEP;
      }
    }
    break;

    case 'D':{
      if(map){
        cord.y -=STEP;
        displaced = map->accessible(cord);
        if(displaced == BLOCK)
          cord.y +=STEP;
      }
    }
    break;
  }
  if(checkEntourage()){ // si il y a un pirate, la fonction checkEntourage modifie la variable enemyCord
    displaced = MONSTER ;
  }

  return displaced ;
}
// int Corsaire::seDeplacer(){
//
// }

string Corsaire::getClass(){
  return "Corsaire";
}

bool Corsaire::setObject(Object* object){
  if(nb_objects < NB_OBJECTS_MAX && haveAlready(object) == false){
    objects[nb_objects] = object ;
    nb_objects++ ;
    return true;
  }
  return false ;
}

bool Corsaire::setObject(){
  if(nb_objects < NB_OBJECTS_MAX ){
    switch(map->getObjectNameFrom(cord)){
      case 'x':
        if(haveAlready(new Pelle()) == false){
          objects[nb_objects] = new Pelle() ;
          nb_objects++;
            return true;
        }
      break;

      case 'y':
        if(haveAlready(new Mousquet()) == false){
          objects[nb_objects] = new Mousquet() ;
          nb_objects++;
          return true;
        }
      break;

      case 'z':
        if(haveAlready(new Armure()) == false){
          objects[nb_objects] = new Armure() ;
          nb_objects++;
          return true;
        }
      break;
    }
    return false ;
  }
  else
    return false;
}

bool Corsaire::haveAlready(Object* object){
  if(nb_objects == 0)
    return false ;

  for(int i = 0 ; i < nb_objects ; i++){
      if(object->getClass() == objects[i]->getClass())
        return true ;
  }

  return false ;
}

bool Corsaire::haveAlready(string object){
  if(nb_objects == 0)
    return false ;

  for(int i = 0 ; i < nb_objects ; i++){
      if(object == objects[i]->getClass())
        return true ;
  }

  return false ;
}

int Corsaire::attaquer(){
  bool defenseObject = false ;
  bool attackObject = false ;
  int k;
  cerr<<"1\n";
  for(int i = 0 ; i < nb_objects ; i++){
    if(objects[i]->getType() == "ATTACK"){
      attackObject = true ;
      k = i;
    }
    else if(objects[i]->getType() == "DEFENSE"){
      defenseObject = true ;
      k = i ;
    }
  }
  cerr<<"2\n";
  Personne* p = map->getPirateFrom(enemyCord);
  if(attackObject && defenseObject)
    return WIN ;
  else if(attackObject){
    if(p && p->getClass() == BOUCANIER && equal(enemyCord,cord) == false)
      return WIN ;
  }
  else if(defenseObject){
    if(p && p->getClass() == BOUCANIER && equal(enemyCord,cord) == false)
      return EQUALITY ;
  }
  if (attackObject || defenseObject){
    cerr<<"3\n";
    if(dynamic_cast<WarObject*>(objects[k])->isWin() == true){
      if(attackObject)
        return WIN;
      else if(defenseObject)
        return EQUALITY;
    }
    else
      return LOSE;
    cerr<<"4\n";
  }
  else{ // SI JE N'AI AUCUN outil
  cerr<<"5\n";
  if(p)
    cerr<<p->getClass()<<endl;
  else
    cerr<<"p est null ! mais il trouve un monster quand meme"<<endl;
      if(p && p->getClass() == BOUCANIER &&  equal(enemyCord,cord) == false){
        cerr<<"6\n";
        return EQUALITY ;
      }
    else
      return LOSE ;
  }
  cerr<<"7\n";
  return EQUALITY ;
}

int Corsaire::howManyObjectCanIGet(){
  return NB_OBJECTS_MAX ;
}

bool Corsaire::checkEntourage(){
  int x,y ;
  x = cord.x - 1 ;
  y = cord.y - 1 ;
  if(map->accessible(Cord{x,y}) == MONSTER){
      enemyCord.x = x;
      enemyCord.y = y;
      return true ;
  }

  x = cord.x - 1 ;
  y = cord.y ;
  if(map->accessible(Cord{x,y}) == MONSTER){
      enemyCord.x = x;
      enemyCord.y = y;
      return true ;
  }

  x = cord.x - 1 ;
  y = cord.y + 1 ;
  if(map->accessible(Cord{x,y}) == MONSTER){
      enemyCord.x = x;
      enemyCord.y = y;
      return true ;
  }

  x = cord.x ;
  y = cord.y - 1 ;
  if(map->accessible(Cord{x,y}) == MONSTER){
      enemyCord.x = x;
      enemyCord.y = y;
      return true ;
  }

  x = cord.x ;
  y = cord.y ;
  if(map->accessible(Cord{x,y}) == MONSTER){
      enemyCord.x = x;
      enemyCord.y = y;
      return true ;
  }

  x = cord.x  ;
  y = cord.y + 1 ;
  if(map->accessible(Cord{x,y}) == MONSTER){
      enemyCord.x = x;
      enemyCord.y = y;
      return true ;
  }

  x = cord.x + 1 ;
  y = cord.y - 1 ;
  if(map->accessible(Cord{x,y}) == MONSTER){
      enemyCord.x = x;
      enemyCord.y = y;
      return true ;
  }

  x = cord.x + 1 ;
  y = cord.y ;
  if(map->accessible(Cord{x,y}) == MONSTER){
      enemyCord.x = x;
      enemyCord.y = y;
      return true ;
  }
  x = cord.x + 1 ;
  y = cord.y + 1 ;
  if(map->accessible(Cord{x,y}) == MONSTER){
      enemyCord.x = x;
      enemyCord.y = y;
      return true ;
  }

  return false ;
}

Cord Corsaire::getEnemyCord(){
  return enemyCord ;
}

void Corsaire::kill(Cord cord){
  map->removeMonsterFrom(cord);
}

bool Corsaire::havePelle(){
  for(int i = 0 ; i < nb_objects ; i++){
    if(objects[i]->getClass() == "Pelle"){
      return true ;
    }
  }
  return false;
}

bool Corsaire::creuse(){
  map->setCreuserValue(cord,true);
  return map->thereIsTresor(cord);
}

bool Corsaire::isAlive(){
  return alive ;
}
void Corsaire::die(){
  map->deleteFromMap(this);
  alive = false;
}
