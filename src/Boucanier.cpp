#include "../include/Boucanier.h"

Boucanier::Boucanier(Map* &map): Personne(map){
  machette = new Machette();
  id = static_id++;
  do{
    cord.x = rand()%map->getHeight();
    cord.y = rand()%map->getSegmentWidth();
  }while(map->accessible(cord) == BLOCK || map->accessible(cord) == MONSTER  );
}

Boucanier::Boucanier( Map* &map,int x, int y) : Personne(map,x,y){
id = static_id++;
machette = new Machette();
cord = Cord{x,y};
}
Boucanier::Boucanier(Map* &map,Cord cord) : Personne(map,cord){
id = static_id++;
machette = new Machette();
this->cord = cord ;
}
Boucanier::~Boucanier(){

}

int Boucanier::seDeplacer(){

  char direction;
  int displaced = BLOCK; /* pour savoir si le déplacement a été bien fait ou pas*/
  int directed = 0 ;
  bool haut , bas , gauche , droit ;

  haut = bas = gauche = droit = false;

  map->removeMonsterFrom(cord);

  while(displaced == BLOCK && directed < 4 ){
    direction = 65 + rand()%4;
    switch (direction) {
      case 'A':{
        if(haut == false){
          haut = true ;
          directed++;
          if(map){
            cord.x -=STEP;
            displaced = map->accessible(cord);
            if(displaced == BLOCK)
              cord.x +=STEP;
          }
          else
            directed = 4 ;
        }
      }
      break;

      case 'B':{
        if(bas == false){
          bas = true ;
          directed++;
          if(map){
            cord.x +=STEP;
            displaced = map->accessible(cord);
            if(displaced == BLOCK)
              cord.x -=STEP;
          }
          else
            directed = 4 ;
        }
      }
      break;

      case 'C':{
        if(droit == false){
          droit = true ;
          directed++;
          if(map){
            cord.y +=STEP;
            displaced = map->accessible(cord);
            if(displaced == BLOCK)
              cord.y -=STEP;
          }
          else
            directed = 4 ;
        }
      }
      break;

      case 'D':{
        if(gauche == false){
          gauche = true ;
          directed++;
          if(map){
            cord.y -=STEP;
            displaced = map->accessible(cord);
            if(displaced == BLOCK)
              cord.y +=STEP;
          }
          else
            directed = 4 ;
        }
      }
      break;

    }
  }
  map->setMonsterIn(cord);
  return displaced ;
}
// int Boucanier::seDeplacer(char direction){
//
// }

string Boucanier::getClass(){
  return "Boucanier";
}
