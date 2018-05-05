#include "../include/WarObject.h"

WarObject::WarObject(int purcent) : Object(){
  win_purcent = purcent ;
  int nb_win = (10*win_purcent)/100 ;

  int i = 0;
  int n = 0;

  for(int i = 0 ; i < 10 ; i++){
      t_win[i] = ' ';
  }

  srand(time(NULL));
  while(n < nb_win){
    i = rand() % 9;
    if(t_win[i] == ' '){
      t_win[i] = 'G';
      n++;
    }
  }

  for(int i = 0 ; i < 10 ; i++){
    if(t_win[i] == ' ')
      t_win[i] = 'P';
  }
}

WarObject::WarObject(Map* map, int purcent) : Object(map){
  win_purcent = purcent ;
  int nb_win = (10*win_purcent)/100 ;

  int i = 0;
  int n = 0;

  srand(time(NULL));
  while(n < nb_win){
    i = rand() % 9;
    if(!t_win[i]){
      t_win[i] = 'G';
      n++;
    }
  }

  for(int i = 0 ; i < 10 ; i++){
    if(!t_win[i])
      t_win[i] = 'P';
  }
}

string WarObject::getClass(){
  return "WarObject";
}

bool WarObject::isWin(){
  srand(time(NULL));
  int i = rand() % 9 ;
  return t_win[i] == 'G';
}
