#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
#include "Map.h"
#include "Corsaire.h"
#include "Boucanier.h"
#include "Flibustrier.h"
#include "Gameplay.h"
#include "Save.h"


class Sauvegarde{
public:
   Sauvegarde();
   Sauvegarde(Map*);
  ~Sauvegarde();
    void sauvegarder();
    void charger();
    Save getSave();
  private:
    Map* map ;
    Save save ;
};

#endif
