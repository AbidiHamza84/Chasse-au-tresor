#ifndef _DIAGRAMS_MENU_H
#define _DIAGRAMS_MENU_H

#include "ManageFile.h"
#include "Gameplay.h"
#include "Sauvegarde.h"
#include <dirent.h>
#ifndef _DIAGRAMS_WIN32
    #include <sys/types.h>
#endif
#include <string.h>

#include "ClearSrc.h"

#include <stdlib.h>

using namespace std ;


class Menu{
  public:
    Menu();
    ~Menu();
    void menuPrincipal();
    void parametresJeu();
  private:
    Colors color;
    Input* input;
    int nbMaps ;
    int nbJoueurs;
    bool jouer = true;
    bool charger = false;
    bool quitter = false ;
    string* maps ;
    string** joueurs ;
    int choixMenuPricipal ;
    int personnage ;
    int map ;
    void displayTitle();
};
#endif
