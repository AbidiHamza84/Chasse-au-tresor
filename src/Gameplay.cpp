#include "../include/Gameplay.h"
#include "../include/Input.h"


Gameplay::Gameplay(){
	// une map
	map = new Map("../maps/map1");
	this->nb_player = 1 ;
	player = new Corsaire*[nb_player];
	player[0] = new Corsaire(map,0 /* position x */ , 0 /* position y */);

		srand(time(NULL));
		do{
			player[0]->setPos( rand()%map->getHeight() , rand()%map->getSegmentWidth());
		}while(map->accessible(player[0]->getPos()) == false);
	}

Gameplay::Gameplay(Save& save){
	map = new Map(save.name,true,false);
	this->nb_player = save.nb_corsaire ;
	this->nb_pirates = save.nb_boucanier + save.nb_flibustrier ;

	pirates = new Personne*[this->nb_pirates];

	for(int i = 0 ;i<save.nb_boucanier ; i++){
		pirates[i] = new Boucanier(map,save.boucanierPos[i]);
		map->addElement(pirates[i]);
	}

	for(int i = save.nb_boucanier ,  j = 0 ;i<save.nb_boucanier+save.nb_flibustrier ; i++,j++){
		pirates[i] = new Flibustrier(map,save.flibustrierPos[j]);
		map->addElement(pirates[i]);
		std::cerr << "flib" << '\n';
	}

	player = new Corsaire*[nb_player];
	for (int i = 0; i < nb_player; i++)
	{
		player[i] = new Corsaire(map,save.corsairePos[i].cord);
		if(save.corsairePos[i].pelle)
			player[i]->setObject(new Pelle());
		if(save.corsairePos[i].armure)
			player[i]->setObject(new Armure());
		if(save.corsairePos[i].mousquet)
			player[i]->setObject(new Mousquet());

		map->addElement(player[i]);
		std::cerr << "cors" << '\n';
	}
	map->distribuerObjects(save);
}

// plusieurs joueurs
Gameplay::Gameplay(string nameMap ,int nb_player , int difficulte , bool creationMap){
	map = new Map(nameMap,true,creationMap);
	this->nb_player = nb_player ;
	srand(time(NULL));
	//******************************************************************************************
	//pirates
	this->nb_pirates = difficulte * 10 ;
	pirates = new Personne*[this->nb_pirates];

	for(int i = 0 ;i<this->nb_pirates ; i++){
		if (i < this->nb_pirates / 2)
			pirates[i] = new Boucanier(map);
		else
			pirates[i] = new Flibustrier(map);

		map->addElement(pirates[i]);
	}
//******************************************************************************************
//corsaires
	player = new Corsaire*[nb_player];

	for (int i = 0; i < nb_player; i++)
	{
		player[i] = new Corsaire(map);
		map->addElement(player[i]);
	}

	//******************************************************************************************
	//objects

	map->distribuerObjects();

}

void Gameplay::movePirates(){
	srand(time(NULL));
	for(int i = 0 ; i < this->nb_pirates ; i++ ){
		if(map->belongsToMap(this->pirates[i])){
			this->pirates[i]->seDeplacer();
		}
	}
}


void Gameplay::play() {

	int role = 0;
	Input* input = new Input();
	char c ;
	int radar;
	bool continuer = true ;
	int fin = 0 ;
	bool tresor;
	bool suivant = true;

	while(continuer == true) {
		suivant = true;
		input->setCursorPosition(1,1);
		map->display();
		input->setCursorPosition(player[role]->getPos().x+1,player[role]->getPos().y+1);

		// faire bouger les pirates
		movePirates();

		c = input->keyboard();

		// se deplacer
		if(c == UP) {
			radar = player[role]->seDeplacer('A');
		}
		else if(c == DOWN) {
			radar = player[role]->seDeplacer('B');
		}
		else if(c == RIGHT) {
			radar = player[role]->seDeplacer('C');
		}
		else if(c == LEFT) {
			radar = player[role]->seDeplacer('D');
		}
		else if(c == SPACE){
			if(player[role]->havePelle() == true && map->estCreuse(player[role]->getPos()) == false){
				tresor = player[role]->creuse();
				cerr<<"je creuse = "<<map->estCreuse(player[role]->getPos());
				if(tresor == true){
					input->setCursorPosition(window_height+1,1);
					cout<<"La partie est termie ! le joueur "<<role<<" a gagne !\n";
					continuer = false;
					break;
				}
				suivant = true;
			}
			else
				suivant = false;
		}
		else if( c == E){
			Sauvegarde* s = new Sauvegarde(map);
			s->sauvegarder();
			Cord cur = input->getCursorPosition();
			input->setCursorPosition(window_height+1,1);
			cout<<"Enregistrement ..."<<endl;
			input->setCursorPosition(cur.x,cur.y);
			sleep(1);
		}
		else if(c == ESC){
			Cord cur = input->getCursorPosition();
			clear_screen();
			Colors color;
			input->setCursorPosition(1,1);

			int choix = 0;
			bool cont = true;
			while(cont){
					color.setColorText("Voulez vous enregistrez avant de quitter ?\n",'V');
	        if(choix == 0){
	          color.setColorText("Oui    ",'R');
						cout<<"Non"<<endl;
	         }
	         else{
						 cout<<"Oui    ";
						 color.setColorText("Non\n",'R');
	         }
				char car = input->keyboard();
				switch(car){
			    case RIGHT : {
			      if(choix < 1)
			        choix++;
			      break;
			    }
			    case LEFT :
			      if(choix>0)
			        choix--;
			      break;
			    case ENT : cont  = false; break;
			  }
			  clear_screen();
			}
			if(choix == 1){
				clear_screen();
				input->setCursorPosition(1,1);
				continuer = false;
			}
			else{
				Sauvegarde* s = new Sauvegarde(map);
				s->sauvegarder();
				clear_screen();
				input->setCursorPosition(1,1);
				continuer = false;
			}
		}


		// recuperer un object si il y on a
		if(map->thereIsObjectIn(player[role]->getPos()) == true){
			if(player[role]->setObject() == true)
				map->deleteObjectFrom(player[role]->getPos()) ;
		}

		// lancer un combat si il y a un pirate
		if(radar == MONSTER){
			int result = player[role]->attaquer();
			if(result == WIN){ // le player a gagné le combat
					Personne* p = map->getPirateFrom(player[role]->getEnemyCord());
					map->deleteFromMap(p);
					player[role]->kill(player[role]->getEnemyCord());
			}
			else if (result == LOSE){
					player[role]->die();
					fin++;
			}
		}
		if(radar == BLOCK)
			suivant = false ;


		// faire passer le role au joueur suivant
		if(suivant == true){
			do{
			role++;
			if(role == nb_player)
				role = 0 ;
			}while(player[role]->isAlive() == false && fin < nb_player);
		}



		// si il y plus de joueurs on quitte
		if(fin == nb_player){
			map->display();
			input->setCursorPosition(window_height+1,1);
			cout<<"La partie est termie ! tout les joueurs sont mort !!\n";
			continuer = false;
		}
	}
}
