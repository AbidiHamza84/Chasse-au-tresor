#include "../include/Personne.h"



using namespace std;



Personne::Personne(Map* &map, int x, int y)
{

  this->map = map ;
 	pv= 10;
 	pvMax=pv;

 	cord.x = x ;
 	cord.y = y ;

}

Personne::Personne(Map* &map, Cord)
{

  this->map = map ;
 	pv= 10;
 	pvMax=pv;
 	this->cord = cord ;

}

Personne::Personne(Map* &map)
{

  this->map = map ;
	pv=10;
	pvMax=pv;

}


int Personne::getPv()
{
	return pv;
}

void Personne::setPv(int Pv)
{
	pv = Pv;
}

int Personne::getPvMax()
{
	return pvMax;
}

void Personne::regenFullPv()
{
	pv=pvMax;

}
void Personne::setPos(Cord){
	this->cord = cord ;
}

void Personne::setPos(int x , int  y){
	cord.x = x ;
	cord.y = y ;
}

Cord Personne::getPos(){
	return cord;
}

void Personne::takeDamage (int damage)
{
		pv-=damage;
}

int Personne::getId(){
	return id;
}

string Personne::getClass(){
  return "Personne";
}
bool Personne::haveAlready(Object* object){
  return false;
}

bool Personne::haveAlready(string object){
  return false;
}
