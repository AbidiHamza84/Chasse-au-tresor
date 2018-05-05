// \autor Abidi Hamza
// \date 28/11/2017

///
/// Boucanier est une personne avec quelques caractéristiques spécifiés
/// Un boucanier
///

#ifndef BOUCANIER_H
#define BOUCANIER_H

#include "Personne.h"
#include "Map.h"
#include "Machette.h"



class Boucanier : public Personne
{
	public:
		static int static_id ;
		Boucanier(Map* &map);

		Boucanier(Map* &map,int x, int y);
		Boucanier(Map* &map,Cord cord);
		~Boucanier();

		int seDeplacer() ;
		int seDeplacer(char direction){} ;
		string getClass() ;
private:
	const int STEP = 2 ;
	Machette* machette ;
};

#endif
