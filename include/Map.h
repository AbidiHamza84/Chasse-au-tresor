/// \file Map.cpp
/// \author Abidi Hamza
/// \date 20 Avril 2017
///
/// La classe Map s'occupe de la construction , l'affichage , la modification d'une map
///
/// une map est construite par un ensemble des lettres dans un fichier texte (a : arbre , h : herbe , e : eau)
///
#ifndef _DIAGRAMS_MAP_H
#define _DIAGRAMS_MAP_H

#define MONSTER 2
#define MOVE 1
#define BLOCK 0



#define CORSAIRE "Corsaire"
#define BOUCANIER "Boucanier"
#define FLIBUSTRIER "Flibustrier"
#define PELLE "Pelle"
#define MOUSQUET "Mousquet"
#define ARMURE "Armure"

#include <string>
#include "Colors.h"

#include <iostream>
#include <time.h>
#include <typeinfo>
#include <stdio.h>
#include "Input.h"
#include "ManageFile.h"
#include "Save.h"
class Corsaire;

class Boucanier;

class Flibustrier;

#include "Personne.h"

#include <fcntl.h>
#include <unistd.h>


#define window_width 110 // \brief La largeur maximale de la map (la longueur des lignes du fichier texte qui represente la map)
#define window_height 40 // \brief La hauteur maximale de la map (le nombre des lignes du fichier texte qui represente la map)
#define segment_width 110 // \brief La largeur du segment qui sera affiché sur l'ecran

// les numeros des lignes dans la matrice objects, chaque object a une ligne, dans une ligne il y'a autant d'object que le nombre des joueurs
#define IND_PELLE 0
#define IND_MOUSQUET 1
#define IND_ARMURE 2


/// \class Map
class Map {
  private:
    string map;
    int monstersNumber ;
    int beginIndex;
    Input* cursor ;

    int nb_personnes_max;


    Personne** personnes ;
    int nb_personnes ;
    int nb_corsaires ;

    typedef struct Case{
      char c;
      bool monster ;
      char object;
      bool creuser;
      bool tresor;
    }Case ;

    Case** matrixMap ;

  public:

    /// \brief initialiser la map avec le nom d'un fichier texte qui contient les éléments de la map

    /// \param[in] map le nom de la map choisie par l'utilisateur
    /// \param[in] with_monsters true si on veut construire uene map contenant des pirates (Boucanier et Flibustrier) , false sinon
    /// \param[in] to_create true si veut créer une nouvelle map , false sinon
    Map(string map,bool with_monsters = true , bool to_create = false);

    /// \brief Désallocation de la memoire
    ~Map();

    /// \brief afficher la map
    void display();

    void display(Case**,int);

    /// \brief récuperer la largeur de la map
    int getWidth();

    /// \brief récuperer la langueur de la map
    int getHeight();

    /// \brief récuperer la largeur d'un segment de la map
    int getSegmentWidth();

    /// \brief retourne vrai si on peut accéder a une case donnée
    /// \param[in] cord c'est les cordonnées de la case oû on veut veut verifier si elle est accéssible ou pas (accessible != eau && arbre && monsters)
    /// \return elle retourne MONSTER , MOVE ou BLOCK
    int accessible(Cord cord);

    /// \brief Inisialiser à true la variable monster à la position passé en paramétre
    /// \param[in] cord c'est les cordonnées de la case oû on veut veut mettre un monster
    void setPirate(Cord);

    /// \brief Créer une nouvelle map
    void creerMap();

    /// \brief Connaitre le nature de l'object qui est dans la position passé en paramétre
    /// \return F pour Flibustrier , C pour Corsaire , B pour Boucanier et ' ' si il n'y a aucun object
    string getEspece(Cord);

    /// \brief Rajouter un personnage à la liste des personnages dans la map
    void addElement(Personne*);

    /// \brief retourne true si il y'a un joueur qui été déja placé à la position passé en paramétre
    bool thereIsPlayerIn(Cord);

    /// \brief retourne true si il y'a un objet(pelle,mousquet,armure), false sinon
    bool thereIsObjectIn(Cord);

    /// \brief distribue les objects(pelles, mousquets et armures )sur la map en initialisant la variable object de charque case concerné
    void distribuerObjects();

    void distribuerObjects(Save);

    Personne* getPirateFrom(Cord);

    Personne* getCorsaireFrom(Cord);

    void deleteFromMap(Personne*);

    char getObjectNameFrom(Cord);

    void deleteObjectFrom(Cord);

    bool belongsToMap(Personne*);

    void setMonsterIn(Cord);

    void removeMonsterFrom(Cord);

    void setCreuserValue(Cord,bool);

    bool estCreuse(Cord);

    bool thereIsTresor(Cord);

    int getNbBoucaniers();

    int getNbFlibustriers();

    int getNbCorsaires();

    int getNbPelles();

    int getNbArmures();

    int getNbMousquets();

    string getName();
};
#endif
