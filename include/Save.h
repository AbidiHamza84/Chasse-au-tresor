#ifndef SAVE_H
#define SAVE_H
#include "Cord.h"
#include <iostream>
using namespace std ;

typedef struct Cors{
  bool pelle ;
  bool armure;
  bool mousquet;
  Cord cord;
}Cors;

typedef struct Save{
  string name;
  int nb_boucanier;
  int nb_flibustrier;
  int nb_corsaire;
  Cord* boucanierPos;
  Cord* flibustrierPos;
  Cors* corsairePos;
  Cord tresor;
  int nb_pelle;
  int nb_armure;
  int nb_mousquet;
  Cord* pellePos;
  Cord* armurePos;
  Cord* mousquetPos;
}Save;

#endif
