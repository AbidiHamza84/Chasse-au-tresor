// \autor Abidi Hamza
// \date 28/11/2017

///
/// ... Documentation ...
///

#ifndef CORSAIRE_H
#define CORSAIRE_H

#define NB_OBJECTS_MAX 3

#define WIN 0
#define LOSE 1
#define EQUALITY 2


#include "Personne.h"
//#include "WarObject.h"
#include "Pelle.h"
#include "Mousquet.h"
#include "Armure.h"




class Corsaire : public Personne
{
	public:
		Corsaire(Map* &map) ;

		Corsaire(Map* &map,int x, int y);
		Corsaire(Map* &map,Cord cord);
		~Corsaire();

		static int static_id ;

		int seDeplacer(char direction) ;
		int seDeplacer(){} ;
		int attaquer() ;
		bool setObject(Object*);
		string getClass() ;
		bool haveAlready(Object*);
		bool haveAlready(string);
		int howManyObjectCanIGet();
		Cord getEnemyCord();
		bool setObject();
		void kill(Cord);
		bool havePelle();
		bool creuse();
		bool isAlive();
		void die();
		private:
			const int STEP = 1 ;
			Object* objects[10] ;
			int nb_objects;
			Cord enemyCord ;
			bool checkEntourage();
			bool alive;
};

#endif
