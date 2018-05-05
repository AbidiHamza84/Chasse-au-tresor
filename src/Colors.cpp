#include "../include/termcolor.h"
#include "../include/Colors.h"
#include <iostream>
#include <string>


using namespace std;
using namespace termcolor;

Colors::Colors(){}
void Colors::activerTermcolorBackground(char c){
  switch(toupper(c)){
    case 'R' : cout << on_red;
              break;
    case 'B' : cout << on_blue;
              break;
    case 'V' : cout << on_green;
              break;
    case 'J' : cout << on_yellow;
              break;
    case 'M' : cout << on_magenta;
              break;
    case 'C' : cout << on_cyan;
              break;
    case 'N' : cout << on_grey;
              break;
    case 'W' : cout << on_white;
              break;
    case 'X' : cout << reset;
              break;
    default :std::cout << "cette couleur n'existe pas parmis les choix disponibles" << '\n';
  }
}

void Colors::activerTermcolor(char c){
  switch(toupper(c)){
    case 'R' : cout << red;
              break;
    case 'B' : cout << blue;
              break;
    case 'V' : cout << green;
              break;
    case 'J' : cout << yellow;
              break;
    case 'M' : cout << magenta;
              break;
    case 'C' : cout << cyan;
              break;
    case 'N' : cout << grey;
              break;
    case 'W' : cout << white;
              break;
    default :std::cout << "cette couleur n'existe pas parmis les choix disponibles" << '\n';
  }
}

void Colors::desactiverTermcolor(){
  cout<<termcolor::reset;
}
void Colors::displayColor(char c){
  activerTermcolor(c);
  std::cout << "   ";
  desactiverTermcolor();
}

void Colors::displayColor(string s ,char c){
  activerTermcolorBackground(c);
  std::cout << s;
  desactiverTermcolor();
}

void Colors::setColorText(string s ,char c){
  activerTermcolor(c);
  std::cout << s;
  desactiverTermcolor();
}
