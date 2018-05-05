#ifndef _DIAGRAMS_GAMEPLAY_H
#define _DIAGRAMS_GAMEPLAY_H

#include "Map.h"
#include "Input.h"
#include "Corsaire.h"
#include "Boucanier.h"
#include "Flibustrier.h"
#include "Sauvegarde.h"
#include "Save.h"
#include <iostream>
#include <time.h>
#include <signal.h>



class Gameplay {
	public:
		Gameplay();
		Gameplay(Save&);
		Gameplay(string ,int  , int  , bool = false);
		void play();
		void movePirates();
	private:
		Map* map;
		int nb_player ;
		int nb_pirates ;
		Corsaire** player;
		Personne** pirates;
};

#endif
