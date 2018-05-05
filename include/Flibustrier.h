// \autor Abidi Hamza
// \date 28/11/2017

///
/// ... Documentation ...
///

#ifndef FLIBUSTRIER_H
#define FLIBUSTRIER_H


#include "Personne.h"
#include "Map.h"
#include "Pistolet.h"



class Flibustrier : public Personne
{
	public:
		static int static_id ;
		Flibustrier(Map* &map);

		Flibustrier(Map* &map,int x, int y);
		Flibustrier(Map* &map,Cord cord);
		~Flibustrier();

		int seDeplacer();
		int seDeplacer(char direction){};
		string getClass() ;
	private:
		const int STEP = 1 ;
		Pistolet* pistolet ;
};

#endif
