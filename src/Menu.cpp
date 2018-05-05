#include "../include/Menu.h"

Menu::Menu(){
  DIR *dr;
  input = new Input();
  dr=opendir("../maps/"); // j'accède au dossier
  struct dirent* drnt ; // je enregistre son contenu dans le tableau de dirent drnt (structure)
  nbMaps = 10 ;
  maps = new string[nbMaps];
  int i = 0 ;
   while (i<10 && (drnt=readdir(dr)) !=NULL){ // je parcours le dossier fichier par fichier
     if(strcmp(drnt->d_name,".") != 0 && strcmp(drnt->d_name,"..") != 0 && strcmp(drnt->d_name,"terrainDesCombats.txt") !=0){
       maps[i] = drnt->d_name; // je récupère les noms des fichiers
       i++;
     }

  }
  nbMaps = i;
  closedir(dr);

}

Menu::~Menu(){

}


void Menu::menuPrincipal(){
  char c ;
  int colonne ;
  int ligne ;
std::string user = "";

	   system("cvlc ../media/music.mp3 -q -R 2> /dev/null &");//ouvre la musique en mode repetition

     clear_screen();
     displayTitle();

 do{
   colonne = input->getTermSize().y / 2 - 5 ;
   ligne = 10;
   if(jouer){
     clear_screen();
     displayTitle();
     input->setCursorPosition(ligne,colonne);
     color.setColorText("Jouer\n",'R');

     ligne+=2;
     input->setCursorPosition(ligne,colonne);
     std::cout << "Charger" << '\n';

     ligne+=2;
     input->setCursorPosition(ligne,colonne);
     std::cout << "Quitter" << '\n';
   }
   else if(charger){
     clear_screen();
     displayTitle();
     input->setCursorPosition(ligne,colonne);
     std::cout << "Jouer" << '\n';

     ligne+=2;
     input->setCursorPosition(ligne,colonne);
     color.setColorText("Charger\n",'R');

     ligne+=2;
     input->setCursorPosition(ligne,colonne);
     std::cout << "Quitter" << '\n';
   }
   else{
     clear_screen();
     displayTitle();
     input->setCursorPosition(ligne,colonne);
     std::cout << "Jouer" << '\n';

     ligne+=2;
     input->setCursorPosition(ligne,colonne);
     std::cout << "Charger" << '\n';

     ligne+=2;
     input->setCursorPosition(ligne,colonne);
     color.setColorText("Quitter\n",'R');
   }
   c = input->keyboard();
   if(jouer && c == DOWN){
     jouer = false;
     charger = true;
   }
   else if(charger){
     if(c == DOWN){
       charger = false;
       quitter = true;
     }
     else if(c == UP){
       charger = false;
       jouer = true;
     }
   }
   else if(quitter && c == UP){
     quitter = false;
     charger = true;
   }
 }while(c != ENT);

 clear_screen();
 if(jouer){
   parametresJeu();
 }
 else if(charger){
   Sauvegarde* s = new Sauvegarde() ;
   s->charger();
 }
 else if(quitter){
   exit(1);
 }
}

void Menu::displayTitle(){

    Colors color ;
  	std::cout << "\t\t\t"; color.setColorText("██████╗ ██████╗  ██████╗      ██╗███████╗████████╗ ",'R'); color.setColorText("   ██╗   ██╗███╗   ███╗██╗     \n",'B') ;
  	std::cout << "\t\t\t"; color.setColorText("██╔══██╗██╔══██╗██╔═══██╗     ██║██╔════╝╚══██╔══╝ ",'R'); color.setColorText("   ██║   ██║████╗ ████║██║     \n",'B');
  	std::cout << "\t\t\t"; color.setColorText("██████╔╝██████╔╝██║   ██║     ██║█████╗     ██║    ",'R'); color.setColorText("   ██║   ██║██╔████╔██║██║     \n",'B');
  	std::cout << "\t\t\t"; color.setColorText("██╔═══╝ ██╔══██╗██║   ██║██   ██║██╔══╝     ██║    ",'R'); color.setColorText("   ██║   ██║██║╚██╔╝██║██║     \n",'B');
  	std::cout << "\t\t\t"; color.setColorText("██║     ██║  ██║╚██████╔╝╚█████╔╝███████╗   ██║    ",'R'); color.setColorText("   ╚██████╔╝██║ ╚═╝ ██║███████╗\n",'B');
  	std::cout << "\t\t\t"; color.setColorText("╚═╝     ╚═╝  ╚═╝ ╚═════╝  ╚════╝ ╚══════╝   ╚═╝    ",'R'); color.setColorText("    ╚═════╝ ╚═╝     ╚═╝╚══════╝\n",'B');

}

void Menu::parametresJeu(){
  int indMap = 0;
  int indNbJoueur = 0 ;
  int indDiff = 0 ;
  int choix = 0 ;
  char c ;
  bool continuer = true;

  while(continuer){

    color.setColorText("Choisir une map\n",'V');
   for (int i = 0 ; i < nbMaps ; i++){
     if(indMap == i){
      color.setColorText(maps[i]+"    ",'R');
     }
     else{
         std::cout << maps[i] << "    ";
     }
   }

   std::cout << '\n'<< '\n'<< '\n'<< '\n'<< '\n';

   color.setColorText("Nombre de joueurs\n",'V');

    for(int i = 0 ; i < 5 ; i++){
       if( indNbJoueur == i){
        color.setColorText(to_string(i+1)+"    ",'R');
       }
       else{
           std::cout << to_string(i+1) << "    " ;
       }
     }


     std::cout << '\n'<< '\n'<< '\n'<< '\n'<< '\n';

     color.setColorText("Difficulté\n",'V');
     for(int i = 0 ; i < 3 ; i++){
       if(indDiff == i){
         color.setColorText(to_string(i+1)+"    ",'R');
        }
        else{
            std::cout << to_string(i+1) << "    " ;
        }
     }

   c = input->keyboard();

  switch(c){
    case RIGHT : {
      if(choix == 0 && indMap < nbMaps-1)
        indMap++;
      else if(choix == 1 && indNbJoueur < 4 )
        indNbJoueur++;
      else if(choix == 2 && indDiff < 2 )
        indDiff++;
      break;
    }
    case LEFT : {
      if(choix == 0 && indMap>0)
        indMap--;
      else if(choix == 1 && indNbJoueur > 0 )
        indNbJoueur--;
      else if(choix == 2 && indDiff > 0 )
        indDiff--;
      break;
    }
    case ENT :{
      if(choix == 2 )
        continuer = false ;
      else
        choix++;
      break;
    }
  }
  clear_screen();
 }
 string newMapName ;
 cerr<<"nb joueurs = "<<indNbJoueur<< "diff = "<<indDiff<<endl;
Gameplay gameplay("../maps/"+maps[indMap],indNbJoueur+1,indDiff+1,false);
gameplay.play();
}
