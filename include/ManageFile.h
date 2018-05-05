/// \file ManageFile.cpp
/// \author Abidi Hamza
/// \date 20 Avril 2017
///
/// La classe ManageFile va s'occuper de l'ouverture , la fermeture , l'ecriture dans un fichier ,
/// la lecture à partir d'un fichier ..., elle gère l'affichage des erreurs d'ouverture des fichiers
#ifndef _DIAGRAMS_MANAGEFILE_H
#define _DIAGRAMS_MANAGEFILE_H
#define map_directory "../maps/"
#include <string>
#include <iostream>
#include <fstream>
using namespace std ;
class ManageFile{

  public:
    /// \breif creer un fichier en passant son nom et le type d'ouverture[lire : r , ecrire : w , lire et ecrire : rw] en parametre du constructeur
    ManageFile(string,string);

    /// \brief si le fichier est encore ouvert , il sera fermé lors de la destruction
    ~ManageFile();

    /// \brief recuperer la taille du fichier [le nombre de caractéres]
    long getSize();

    /// \brief recuperer le nombre des lignes d'un fichier
    int getNumberLines();

    /// \brief positionner le curseur sur la première ligne
    bool begin();

    /// \brief positionner le curseur sur la dernière ligne
    bool end();

    /// \brief positionner le curseur sur une position donnée
    bool setPosition(int);

    /// \brief lire une ligne à partir du fichier
    string readLine();

    /// \brief lire une ligne à partir du fichier
    string* readWordsOfLine(char);

    /// \brief lire un caractére à partir du fichier
    char readChar();

    /// \brief écrire un caractére dans le fichier
    void write(char);

    /// \brief écrire une chaine de caractéres dans le fichier
    void write(string);

    /// \breif supprimer le contenu du fichier
    void erase();

    /// \brief fermer le fichier
    void close();

  private:
    string nameFile ;
    fstream file;
    string type; /// \breif ouvert en lecture , ecriture ou en lecture et écriture
};
#endif
