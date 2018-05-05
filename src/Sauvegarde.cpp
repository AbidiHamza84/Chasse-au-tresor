#include "../include/Sauvegarde.h"

Sauvegarde::Sauvegarde(){
}

Sauvegarde::Sauvegarde(Map* map){
  this->map = map;
}

Sauvegarde::~Sauvegarde(){

}

void Sauvegarde::sauvegarder(){
  int f = open("sauvegarde.dat",O_CREAT|O_WRONLY,0666);
  int size = map->getName().length();
  write(f,&size,sizeof(int));
  write(f,map->getName().c_str(),size*sizeof(char));

  int n = map->getNbBoucaniers();
  write(f,&n,sizeof(int));
  for (int  i = 0 ; i < window_height ; i++){
  	for(int j = 0 ; j < window_width ; j++){
      Personne* p = map->getPirateFrom(Cord{i,j});
      if(p && p->getClass() == BOUCANIER){
        write(f,&i,sizeof(int));
        write(f,&j,sizeof(int));
      }
  	}
  }

  n = map->getNbFlibustriers();
  write(f,&n,sizeof(int));
  for (int  i = 0 ; i < window_height ; i++){
  	for(int j = 0 ; j < window_width ; j++){
      Personne* p = map->getPirateFrom(Cord{i,j});
      if(p && p->getClass() == FLIBUSTRIER){
        write(f,&i,sizeof(int));
        write(f,&j,sizeof(int));
      }
  	}
  }

  Cord tresor;
  n = map->getNbCorsaires();
  write(f,&n,sizeof(int));
  for (int  i = 0 ; i < window_height ; i++){
  	for(int j = 0 ; j < window_width ; j++){
      if(map->thereIsTresor(Cord{i,j})){
        tresor = Cord{i,j};
      }
      Personne* p = map->getCorsaireFrom(Cord{i,j});
      if(p && p->getClass() == CORSAIRE){
        bool v = p->haveAlready(new Pelle());
        write(f,&v,sizeof(bool));

        v = p->haveAlready(new Armure()) ;
        write(f,&v,sizeof(bool));

        v = p->haveAlready(new Mousquet());
        write(f,&v,sizeof(bool));

        write(f,&i,sizeof(int));
        write(f,&j,sizeof(int));
      }
  	}
  }

  write(f,&tresor.x,sizeof(int));
  write(f,&tresor.y,sizeof(int));

  n = map->getNbPelles();
  write(f,&n,sizeof(int));
  for (int  i = 0 ; i < window_height ; i++){
    for(int j = 0 ; j < window_width ; j++){
      string c = map->getEspece(Cord{i,j});
      if(c == "x"){
        write(f,&i,sizeof(int));
        write(f,&j,sizeof(int));
      }
    }
  }

  n = map->getNbArmures();
  write(f,&n,sizeof(int));
  for (int  i = 0 ; i < window_height ; i++){
    for(int j = 0 ; j < window_width ; j++){
      string c = map->getEspece(Cord{i,j});
      if(c == "z"){
        write(f,&i,sizeof(int));
        write(f,&j,sizeof(int));
      }
    }
  }


  n = map->getNbMousquets();
  write(f,&n,sizeof(int));
  for (int  i = 0 ; i < window_height ; i++){
    for(int j = 0 ; j < window_width ; j++){
      string c = map->getEspece(Cord{i,j});
      if(c == "y"){
        write(f,&i,sizeof(int));
        write(f,&j,sizeof(int));
      }
    }
  }
  close(f);
}

void Sauvegarde::charger(){
  int f = open("sauvegarde.dat",O_RDONLY,0666);
  int size ;
  read(f,&size,sizeof(int));
  char name[size];
  read(f,&name,size*sizeof(char));

  save.name = string(name);

  read(f,&save.nb_boucanier,sizeof(int));

  Cord boucanierPos[save.nb_boucanier] ;
  for(int i = 0 ; i < save.nb_boucanier ; i++){
    int x,y;
    read(f,&x,sizeof(int));
    read(f,&y,sizeof(int));
    boucanierPos[i] = Cord{x,y};
  }
  save.boucanierPos = boucanierPos;

  read(f,&save.nb_flibustrier,sizeof(int));
  Cord flibustrierPos[save.nb_flibustrier] ;
  for(int i = 0 ; i < save.nb_flibustrier ; i++){
    int x,y;
    read(f,&x,sizeof(int));
    read(f,&y,sizeof(int));
    flibustrierPos[i] = Cord{x,y};
  }
  save.flibustrierPos = flibustrierPos;

  cerr<<"8\n";
  read(f,&save.nb_corsaire,sizeof(int));

  Cors corsairePos[save.nb_corsaire] ;
  for(int i = 0 ; i < save.nb_corsaire ; i++){
    read(f,&corsairePos[i].pelle,sizeof(bool));
    read(f,&corsairePos[i].armure,sizeof(bool));
    read(f,&corsairePos[i].mousquet,sizeof(bool));

    int x,y;
    read(f,&x,sizeof(int));
    read(f,&y,sizeof(int));
    corsairePos[i].cord = Cord{x,y};
  }
  save.corsairePos = corsairePos ;


  int x,y;
  read(f,&x,sizeof(int));
  read(f,&y,sizeof(int));
  save.tresor = Cord{x,y};


  read(f,&save.nb_pelle,sizeof(int));
  Cord pellePos[save.nb_pelle];
  for(int i = 0 ; i < save.nb_pelle ; i++){
    int x,y;
    read(f,&x,sizeof(int));
    read(f,&y,sizeof(int));
    pellePos[i] = Cord{x,y};;
  }
  save.pellePos = pellePos;


  read(f,&save.nb_armure,sizeof(int));
  Cord armurePos[save.nb_armure];
  for(int i = 0 ; i < save.nb_armure ; i++){
    int x,y;
    read(f,&x,sizeof(int));
    read(f,&y,sizeof(int));
    armurePos[i] = Cord{x,y};
  }
  save.armurePos = armurePos;


  read(f,&save.nb_mousquet,sizeof(int));
  Cord mousquetPos[save.nb_mousquet];
  for(int i = 0 ; i < save.nb_mousquet ; i++){
    int x,y;
    read(f,&x,sizeof(int));
    read(f,&y,sizeof(int));
    mousquetPos[i] = Cord{x,y};
  }
  save.mousquetPos = mousquetPos;

  close(f);

  Gameplay* gameplay = new Gameplay(save);
  gameplay->play();
}
