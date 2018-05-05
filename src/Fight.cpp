/*#include <iostream>

#include <stdlib.h>

#include <string>
#include <fstream>
#include <time.h>

#include "../include/Fight.h"
#include "../include/Personne.h"

#include "../include/Input.h"

using namespace std;

	Fight::Fight (Corsaire* corsaire , Personne* allMonsters, int numberOfMonsters) : Input()
	{
		monstres = allMonsters ;
		joueur = perso;
		nbMonstres = numberOfMonsters;

		terrain = new Map("../maps/terrainDesCombats.txt",false);
		turn=0;
	}

	Fight::~Fight()
	{

	}

	bool Fight::startBattle()
	{
		srand(time(0));
		int indMonstre = rand()%nbMonstres;
		monstre = monstres[indMonstre]; // on choisi un monstre aléatoirement

		setCursorPosition({1,1});
		joueur.regenFullPv();
		joueur.regenFullMana();
		terrain->display();
		InitialisationBattleDisplay();

		bool tour = true; // true : le joueur qui attaque , false le monstre qu'il attaque
		char c ;
		while(monstre.getPv() != 0 && joueur.getPv() != 0 ){
			if(tour){
				c = keyboard();
				switch (c) {
					case SPACE:
							displayAttack({window_height/2,1},{window_height/2,segment_width-1},"->");
							monstre.takeDamage(1);
							InitialisationBattleDisplay();
							tour = false;
						break;
				}
			}
			else{
				setSleep(10);
				displayAttack({window_height/2,segment_width-1},{window_height/2,1},"<-");
				joueur.takeDamage(1);
				InitialisationBattleDisplay();
				 tour = true ;
			}
	}
	return joueur.getPv() != 0;
	}

void Fight::displayOnCord(Cord cord,string c){
	Cord cur = getCursorPosition();
	setCursorPosition(cord);
	Colors color;
	color.displayColor(c,'V');
	setCursorPosition(cur);
}

void Fight::displayAttack(Cord cord1,Cord cord2 , string c){ // cord1 qui attaque cord2
	Cord cur = getCursorPosition();
	int pas = 1;
	if(cord1.y > cord2.y)
		pas = -1 ;

	Colors color;
	int l = c.length();
	string vide = "";
	for(int i = 0 ; i < l ; i++)
		vide += " ";
	do{
		cord1.y =cord1.y + pas*l ;
		setCursorPosition(cord1);
		color.displayColor(c,'V');
		fflush(stdout);
		setCursorPosition(cord1);
		setSleep(4);
		color.displayColor(vide,'V');
	}while(cord1.y+(pas*l) != cord2.y);
	setCursorPosition(cur);
}

void Fight::InitialisationBattleDisplay(){
	Cord cord{1,1};
	setCursorPosition(cord);
	joueur.displayStat();

	cord.y = segment_width-15;
	setCursorPosition(cord);
	monstre.displayStat();

	cord.y = 1 ;

	cord.x = window_height/2;
	setCursorPosition(cord);
	displayOnCord(cord,"T");

	cord.y = segment_width-1;
	setCursorPosition(cord);
	displayOnCord(cord,"M");
	setCursorPosition({window_height/2,1});
}*/

// 	int Fight::chooseSkill()
// 	{
// 		int skillNum=0;
//
// 		if ( entity[turn].isIa()==true )
// 		{
// 			skillNum=autoChooseSkill();
// 		}
// 		else
// 		{
// 			skillNum=entity[turn].displaySkill();  //---------------------
// 	//		cout<<endl;
// 	//		skillNum=manualChooseSkill();  //-----------------------interface
// 		}
//
//
//
// 		if (entity[turn].manaCost(skillNum)==false)
// 		{
// 			if (entity[turn].isIa()==false)
// 			{
// 				cout<<" no enought mana : "<<entity[turn].getMana()<<endl;
// 			}
// 			return chooseSkill();
// 		}
// 		else
// 		{
// 			cout<<"skill : "<<skillNum<<" joueur : "<<turn<<endl;
// 			return entity[turn].useSkill (skillNum);
// 		}
// 	}
//
//
// 	bool Fight::onlyOneFighter()
// 	{
// 		int cpt=0;
//
// 		for (int i=0; i<numbOfEntity; i++)
// 		{
// 			if (entity[i].getPv() >0)
// 			{
// 				cout<<"joueur "<<i<<" en vie avec "<<entity[i].getPv()<<" pv"<<endl;
// 				cpt+=1;
// 			}
// 			else
// 				cout<<"joueur "<<i<<" mort"<<endl;
//
// 		}
// 		if (cpt >= 2)
// 			{
// 				return false;
// 			}
// 		return true;
//
// 	}
//
//
// 	void Fight::chooseFighter(int damage)
// 	{
// 		int target=turn;
//
// 		while (target==turn || target<0 || target>=numbOfEntity)
// 		{
// 		if (numbOfEntity>2)
// 		{
// 			if ( entity[turn].isIa()==true )
// 			{
// 				target=autoChooseTarget();
// 			}
// 			else
// 			{
// 				target=manualChooseTarget();
//     //-----------------------interface
// 			}
// 		}
// 		else
// 		{
// 			target=(turn+1)%numbOfEntity;
// 		}
// 			      //--------------------------------------interface
// 			if (entity[target].getPv()<1)
// 			{
// 				target=-1;
// 			}
// 		}
// 		//-----------------------------------------------------------
// 		cout<<"combat : "<<entity[target].getPv()<<" target : " <<target<<endl;
// 		entity[target].takeDamage (damage);
// 		cout<<"combat : "<<entity[target].getPv()<<endl;
// 		//---------------------------------------
//
// 	int Fight::autoChooseTarget()
// 	{
// 		srand(time(NULL));
// 		return rand()%(numbOfEntity);
// 	}
//
// 	int Fight::autoChooseSkill()
// 	{
// 		if (entity[turn].manaCost(3)==false)
// 			return 3;
//
// 		if (entity[turn].manaCost(2)==false)
// 			return 2;
//
// 		if (entity[turn].manaCost(1)==false)
// 			return 1;
//
// 		if (entity[turn].manaCost(0)==false)
// 			return 0;
//
// /*		cout<<"auto skill"<<endl;
// 		srand(time(NULL));
// 		return rand()%(4);
// */	}
//
// 	int Fight::manualChooseTarget()
// 	{
// 		int choice;
// 		cout<<"quel perso : ";
// 		choice=inInt();
// 		cout<<endl;
// 		choice-=1;
// 		if (choice>numbOfEntity || choice<0)
// 		{
// 			cout<<"ce perso n'existe pas"<<endl;
// 			choice=manualChooseSkill();
// 		}
// 		return choice;
// 	}
//
// 	int Fight::manualChooseSkill()
// 	{
// 		int choice;
// 		cout<<"quel skill : ";
// 		cin>>choice;
// 		cout<<endl;
// 		if (choice>3 || choice<0)
// 		{
// 			cout<<"error"<<endl;
// 			choice=manualChooseSkill();
// 		}
// 		return choice;
// 	}
