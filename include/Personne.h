// \autor Abidi Hamza
// \date 28/11/2017

///
/// ... Documentation ...
///

#ifndef PERSONNE_H
#define PERSONNE_H


#include <iostream>

#include <stdlib.h>

#include <string>

#include "Cord.h"

#include "ManageFile.h"

class Object;

#include "ClearSrc.h"

class Map;

/// \class Personne
class Personne
{
protected:
		std::string name;
		int pv;
		int pvMax;
		int id ;
		Cord cord ;
		Map* map;
	public:

		/*!
			 *  \brief constructeur vide
			 *
			 *  construire une personne
			 *  \param[in] la map dans laquelle il joue
			 */
			Personne(Map* &map);

			/*!
			 *  \brief constructeur
			 *
			 *  construire une personne
			 *  \param[in] la map dans laquelle il joue
			 *  \param[in] x : le x du personnage
			 *  \param[in] y : le y du personnage
			 */
			Personne(Map* &map,int x, int y);

			/*!
			 *  \brief constructeur
			 *
			 *  construire une personne
			 *  \param[in] la map dans laquelle il joue
			 *  \param[in] Cord : les cordonnées du personnage
			 */
			Personne(Map* &map,Cord);




		/*!
		 *  \brief setPos
		 *
		 *  modifier la position du personnage
		 *
		 *  \param Cord : les nouvelles cordonnées
		 */
		void setPos(Cord);

		/*!
		 *  \brief setPos
		 *
		 *  modifier la position du personnage
		 *
		 *  \param x : le nouveau x
		 *  \param y : le nouveau y
		 */
		void setPos(int x, int y);

		/*!
		 *  \brief getPos
		 *
		 *  recuperer la position du personnage
		 *
		 */

		Cord getPos();


		/*!
		 *  \brief getPv
		 *
		 *  recuperer les points de vie du personnage
		 *
		 */
		int getPv();

		/*!
		 *  \brief getPv
		 *
		 *  modifier les points de vie du personnage
		 *
		 */
		void setPv(int);


		/*!
		 *  \brief getPvMax
		 *
		 *  recuperer les points de vie maximale du personnage
		 *
		 */
		int getPvMax();


		/*!
		 *  \brief getId
		 *
		 *  recuperer l'id du personnage'
		 *
		 */
		int getId();

		/*!
		 *  \brief regenFullPv
		 *
		 *  remettre à fond les points de vie du personnage
		 *
		 */
		void regenFullPv();

		/*!
		 *  \brief takeDamage
		 *
		 *  diminiuer les points de vie du personnage
		 *	param[in] damage est le nompre de points qui vont etre enlové au personnage
		 */
		void takeDamage (int damage);

		/*!
		 *  \brief seDeplacer
		 *
		 *  faire deplacer le personnage
		 *	param[in] direction du deplacement, A pour haut, B pour bas, C pour droite, D pour gauche
		 * return MONSTER, MOVE ou BLOCK
		 */
		virtual int seDeplacer(char direction){};

		/*!
		 *  \brief seDeplacer
		 *
		 *  faire deplacer le personnage aléatoirement
		 * \return true si le deplacement est fait, false sinon
		 */
		virtual int seDeplacer(){};

		/*!
		 *  \brief attaquer
		 *
		 *  chaque personnage peut attaquer à sa propre façon
		 *
		 * \return true si l'attaque a été réussit, false sinon (celui qui a ataqué est mort)
		 */
		virtual int attaquer(){};

		/*!
		 *  \brief getClass
		 *
		 *  recuperer le type de la classe en string
		 *
		 */
		virtual string getClass();

		virtual bool haveAlready(Object*);

		virtual bool haveAlready(string);

};

#endif
