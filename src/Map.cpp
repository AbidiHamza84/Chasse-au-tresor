#include "../include/Map.h"

using namespace std ;

Map::Map(string nameMap , bool withMonsters , bool toCreate){

  map = nameMap ;
  nb_personnes = 0 ;
  nb_personnes_max = 60 ;
  personnes = new Personne*[nb_personnes_max];
  nb_corsaires = 0 ;

  // Initialisation du curseur de Map
  cursor = new Input() ;
  if (toCreate){ // si le joueur avait choisi de creer une nouvelle map (toCreate à true)
    creerMap();
  }

  beginIndex = monstersNumber = 0;
  matrixMap = new Case*[window_height];
  ManageFile file(nameMap , "r");
  for (int  i = 0 ; i < window_height ; i++){
  	matrixMap[i] = new Case[window_width];
  	for(int j = 0 ; j < window_width ; j++){
  		matrixMap[i][j].c = file.readChar();
      matrixMap[i][j].monster = false ;
      matrixMap[i][j].creuser = false ;
      matrixMap[i][j].tresor = false ;
      matrixMap[i][j].object = ' ';
  	}
  }

srand(time(NULL));
Cord cord;
do{
  cord.x = rand()% window_height;
  cord.y = rand()% window_width;
}while(accessible(cord) == false);
matrixMap[cord.x][cord.y].tresor = true ;

}

Map::~Map(){
  delete* matrixMap ;
}


void Map::display(){
  clear_screen();
  string c ;
  Colors color ;
	for (int  i = 0 ; i < window_height ; i++){
		for(int j = 0 ; j < segment_width; j++){
  			switch(matrixMap[i][j].c){
  				case 'h' :{

            c = getEspece(Cord{i,j}) ;
            if(c == "B")
              color.displayColor(c,'N');
            else if(c == "F")
              color.displayColor(c,'R');
            else{
              if(c != "x" && c != "y" && c != "z"){
                if(matrixMap[i][j].creuser == true){
                  color.displayColor(c,'J');
                }
                else
                  color.displayColor(c,'V');
              }
              else {
                color.displayColor(c,'C');
              }


            }
            break;
          }
  				case 'a' :
              color.displayColor(" ",'J');
            break;
  				case 'e' :
              color.displayColor(" ",'B');
            break;
  			}
      }
      cout << '\n';
		}
    Input* input = new Input();
    int x,y;
    x = 2;y=90;

    for(int i = 0 ; i < nb_personnes ; i++){
      if(personnes[i]->getClass() == CORSAIRE){
        input->setCursorPosition(x,y);
        color.displayColor("x : Pelle",'B');
        if(personnes[i]->haveAlready(PELLE) == true)
          color.displayColor("  V",'B');
        x = x+2;
        input->setCursorPosition(x,y);
        color.displayColor("y : Mousquet",'B');
        if(personnes[i]->haveAlready(MOUSQUET) == true)
          color.displayColor("  V",'B');
        x = x+2;
        input->setCursorPosition(x,y);
        color.displayColor("z : Armure",'B');
        if(personnes[i]->haveAlready(ARMURE) == true)
          color.displayColor("  V",'B');

        x = x + 4;
      }
    }


	}

string Map::getEspece(Cord cord){
  for (int i = 0 ;i<nb_personnes ; i++){
    if(equal(personnes[i]->getPos(),cord)){
      if(personnes[i]->getClass() == FLIBUSTRIER){
        return "F";
      }
      if(personnes[i]->getClass() == BOUCANIER){
        return "B";
      }
      if(personnes[i]->getClass() == CORSAIRE){
        return to_string(personnes[i]->getId());
      }
    }
  }

  if(matrixMap[cord.x][cord.y].object == ' ')
    return " ";
  else
    return string(1,matrixMap[cord.x][cord.y].object) ;
}

void Map::addElement(Personne* personne)
{
  if(personne && nb_personnes < nb_personnes_max - 1)
  {
    cerr<<"0 | x = "<<personne->getPos().x<<"   y = "<<personne->getPos().y<<endl;
    personnes[nb_personnes] = personne;
    cerr<<"1"<<endl;
    if(personne->getClass() == CORSAIRE)
      nb_corsaires++;
    else
      matrixMap[personne->getPos().x][personne->getPos().y].monster = true ;
      cerr<<"2"<<endl;
    nb_personnes++;
  }
}

void Map::distribuerObjects(){
  Cord cord ;
  srand(time(NULL));
  for(int i = 0 ; i < nb_corsaires ; i++){

    // pelle
    do{
			cord.x = rand()%this->getHeight();
      cord.y = rand()%this->getSegmentWidth();
		}while(this->accessible(cord) == false || this->thereIsPlayerIn(cord) == true || matrixMap[cord.x][cord.y].object != ' ');
    matrixMap[cord.x][cord.y].object = 'x';

    // mousquet
    do{
			cord.x = rand()%this->getHeight();
      cord.y = rand()%this->getSegmentWidth();
		}while(this->accessible(cord) == false || this->thereIsPlayerIn(cord) == true || matrixMap[cord.x][cord.y].object != ' ');
    matrixMap[cord.x][cord.y].object = 'y';

    // armure
    do{
			cord.x = rand()%this->getHeight();
      cord.y = rand()%this->getSegmentWidth();
		}while(this->accessible(cord) == false || this->thereIsPlayerIn(cord) == true || matrixMap[cord.x][cord.y].object != ' ');
    matrixMap[cord.x][cord.y].object = 'z';

  }
}

void Map::distribuerObjects(Save save){
  // pelle
  for(int i = 0 ; i < save.nb_pelle ; i++){
    matrixMap[save.pellePos[i].x][save.pellePos[i].y].object = 'x';
  }

  // mousquet
  for(int i = 0 ; i < save.nb_mousquet ; i++){
    matrixMap[save.mousquetPos[i].x][save.mousquetPos[i].y].object = 'y';
  }

  // armure
  for(int i = 0 ; i < save.nb_armure ; i++){
    matrixMap[save.armurePos[i].x][save.armurePos[i].y].object = 'z';
  }
}

void Map::display(Case** m,int begin){
  clear_screen();
  Colors color ;
  for (int  i = 0 ; i < window_height ; i++){
    for(int j = 0 ; j < segment_width; j++){
        switch(m[i][j].c){
          case 'h' : {
               color.displayColor(" ",'V');
            break;
        }
          case 'a' :
              color.displayColor(" ",'J');
            break;
          case 'e' :
              color.displayColor(" ",'B');
            break;
        }
      }
      cout << '\n';
    }
}

  int Map::getWidth(){
    return window_width ;
  }

  int Map::getHeight(){
    return window_height ;
  }

  int Map::getSegmentWidth(){
    return segment_width ;
  }

  int Map::accessible(Cord cord){
    if(cord.y < window_width-1 && cord.x < window_height && cord.y >= 0 && cord.x >= 0 ){
        if(matrixMap[cord.x][cord.y].c != 'e' && matrixMap[cord.x][cord.y].c != 'a'){
          if(matrixMap[cord.x][cord.y].monster)
            return MONSTER ;
          else
            return MOVE;
        }
      }
      return BLOCK;
  }

  bool Map::thereIsPlayerIn(Cord cord){
    for(int i = 0 ; i < nb_personnes ; i++){
      if(personnes[i]->getClass() == CORSAIRE && personnes[i]->getPos().x == cord.x && personnes[i]->getPos().y == cord.y)
        return true ;
    }
    return false ;
  }

  void Map::setPirate(Cord cord){
    matrixMap[cord.x][cord.y].monster = true ;
    monstersNumber++;
  }

  void Map::creerMap(){
    clear_screen();
    Colors color ;
    Case** m = new Case*[window_height];
    for (int  i = 0 ; i < window_height ; i++){
      m[i] = new Case[window_width];
      for(int j = 0 ; j < window_width-1 ; j++){
      	m[i][j].c = 'h';
      }
    }
    int begin = 0 ;
    cursor->setCursorPosition(1,1);
    display(m,begin);
    cursor->setCursorPosition(1,1);
    Cord position;position.x = position.y = 1 ;
    Cord indMat{0,0};
    char c ;
    bool continuer = true;
    while(continuer) {
  		c = cursor->keyboard();
      if(c == ENT)
        continuer = false;
      else
    		switch(c){
          case UP :
            if(position.x>1){
              position.x--;
              indMat.x--;
            }
          break ;

          case DOWN :
            if(position.x<window_height){
              position.x++;
              indMat.x++;
            }
          break ;

          case RIGHT :
            if(position.y<segment_width){
              position.y++;
              indMat.y++;
            }
            else if (begin < window_width - segment_width-1){
              begin+= segment_width ;
              indMat.y ++;
              cursor->setCursorPosition(1,1);
              display(m,begin);
              position.y = 1 ;
            }
          break ;

          case LEFT :
            if(position.y>1){
              position.y--;
              indMat.y--;
            }
            else if (begin != 0){
              begin-= segment_width ;
              indMat.y --;
              cursor->setCursorPosition(1,1);
              display(m,begin);
              position.y = segment_width;
            }
          break ;

          case E :
            m[indMat.x][indMat.y].c = 'e';
            color.displayColor(" ",'B');
            break ;
          case H :
            m[indMat.x][indMat.y].c = 'h';
            color.displayColor(" ",'V');
            break ;
          case A :
            m[indMat.x][indMat.y].c = 'a';
            color.displayColor(" ",'J');
            break ;
        }
      cursor->setCursorPosition(position);
    }

    ManageFile file(map , "w");
    for (int  i = 0 ; i < window_height ; i++){
      for(int j = 0 ; j < window_width-1 ; j++){
        file.write(m[i][j].c);
      }
      file.write('\n');
    }
    file.close();
    cursor->setCursorPosition(1,1);
  }

  Personne* Map::getPirateFrom(Cord cord){
    for (int i = 0 ;i<nb_personnes ; i++){
      if(equal(personnes[i]->getPos(),cord) == true){
        if(personnes[i]->getClass() != CORSAIRE){
          return personnes[i];
        }
      }
    }
    return nullptr ;
  }

Personne* Map::getCorsaireFrom(Cord cord){
  for (int i = 0 ;i<nb_personnes ; i++){
    if(equal(personnes[i]->getPos(),cord) == true){
      if(personnes[i]->getClass() == CORSAIRE){
        return personnes[i];
      }
    }
  }
  return nullptr ;
}
  void Map::deleteFromMap(Personne* personne){
      if(personne){
      bool v = false ;
      for (int i = 0 ; i < nb_personnes ; i++){
        if(v == false){
        if(personnes[i]->getClass() == personne->getClass()){
          if(personnes[i]->getId() == personne->getId()){
            v = true ;
            }
          }
        }
        else{
        personnes[i-1] = personnes[i];
        }
      }
      nb_personnes--;

      if(personne->getClass() == CORSAIRE)
        nb_corsaires--;
      else{
        matrixMap[personne->getPos().x][personne->getPos().y].monster = false ;
        monstersNumber--;
      }
    }
  }

bool Map::belongsToMap(Personne* personne){
  if(personne){
    for (int i = 0 ;i<nb_personnes ; i++){
      if(personnes[i]->getClass() == personne->getClass() && personnes[i]->getId() == personne->getId()){
        return true;
      }
    }
  }
  return false ;
}

bool Map::thereIsObjectIn(Cord cord){
  return matrixMap[cord.x][cord.y].object != ' ';
}

char Map::getObjectNameFrom(Cord cord){
  return matrixMap[cord.x][cord.y].object ;
}

void Map::deleteObjectFrom(Cord cord){
  matrixMap[cord.x][cord.y].object = ' ';
}

void Map::setMonsterIn(Cord cord){
  matrixMap[cord.x][cord.y].monster = true;
}

void Map::removeMonsterFrom(Cord cord){
  matrixMap[cord.x][cord.y].monster = false;
}

void Map::setCreuserValue(Cord cord,bool val){
  matrixMap[cord.x][cord.y].creuser = val;
}

bool Map::estCreuse(Cord cord){
  return matrixMap[cord.x][cord.y].creuser ;
}

bool Map::thereIsTresor(Cord cord){
  return matrixMap[cord.x][cord.y].tresor;
}

int Map::getNbBoucaniers(){
  int n = 0 ;
  for (int  i = 0 ; i < window_height ; i++){
    for(int j = 0 ; j < window_width ; j++){
      if(getEspece(Cord{i,j}) == "B")
        n++;
    }
  }
  return n ;
}
int Map::getNbFlibustriers(){
  int n = 0 ;
  for (int  i = 0 ; i < window_height ; i++){
    for(int j = 0 ; j < window_width ; j++){
      if(getEspece(Cord{i,j}) == "F")
        n++;
    }
  }
  return n ;
}
int Map::getNbCorsaires(){
  int n = 0 ;
  for (int  i = 0 ; i < window_height ; i++){
    for(int j = 0 ; j < window_width ; j++){
      string c = getEspece(Cord{i,j});
      if(c != "B" && c != "F" && c != "x" && c != "y" && c != "z" && c != " ")
        n++;
    }
  }
  return n ;
}
int Map::getNbPelles(){
  int n = 0 ;
  for (int  i = 0 ; i < window_height ; i++){
    for(int j = 0 ; j < window_width ; j++){
      if(getEspece(Cord{i,j}) == "x")
        n++;
    }
  }
  return n ;
}
int Map::getNbArmures(){
  int n = 0 ;
  for (int  i = 0 ; i < window_height ; i++){
    for(int j = 0 ; j < window_width ; j++){
      if(getEspece(Cord{i,j}) == "z")
        n++;
    }
  }
  return n ;
}
int Map::getNbMousquets(){
  int n = 0 ;
  for (int  i = 0 ; i < window_height ; i++){
    for(int j = 0 ; j < window_width ; j++){
      if(getEspece(Cord{i,j}) == "y")
        n++;
    }
  }
  return n ;
}

string Map::getName(){
  return map ;
}
