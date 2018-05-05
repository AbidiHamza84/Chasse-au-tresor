#include "../include/ManageFile.h"
using namespace std ;

ManageFile::ManageFile(string name , string type){
  nameFile = name ;
  this->type = type;
    if(this->type == "r") file.open(nameFile , ios::in);
    else if(this->type == "w") file.open(nameFile , ios::out);
    else if(this->type == "rw")  file.open(nameFile , ios::in | ios::out | ios::app);

}

ManageFile::~ManageFile(){
  if(file.is_open())
    file.close();
}

long ManageFile::getSize(){
  if(file.is_open()){
    long size = 0 ;
        if(this->type == "r"){ file.seekg( 0 , ios_base::end );
        size = file.tellg() ;
        }

        else if(this->type == "w"){ file.seekp( 0 , ios_base::end );
        size = file.tellp() ;
        }

        else if(this->type == "rw"){ file.seekg( 0 , ios_base::end );
        size = file.tellg() ;
        }
      return size ;
  }
  else{
    cout << "erreur : methode getSize , fichier : " << nameFile << " , impossible de recuperer la taille d'un fichier fermé !" <<'\n';
    return -1;
  }
}

int ManageFile::getNumberLines(){
  if(file.is_open()){
    file.clear();
    int size = 0 ;
      int positionInitiale = file.gcount();
      begin();
    string s ;
    while(readLine() != ""){
      size++;
    }
    begin();
    setPosition(positionInitiale);
    return size ;
 }
  else{
    cout << "erreur : methode getNumberLines , fichier : " << nameFile << " , impossible de recuperer le nombre des lignes d'un fichier fermé !" <<'\n';
    return -1 ;
  }
}

bool ManageFile::begin(){
  if(file.is_open()){
      file.clear();
      if(this->type == "r") file.seekg(ios_base::beg);
      else if(this->type == "w") file.seekp(ios_base::beg);
      else if(this->type == "rw") file.seekg(ios_base::beg);

    return true ;
  }
  else{
    cout << "erreur : methode begin , fichier : " << nameFile << " , n'est pas ouvert !" <<'\n';
    return false;
  }
}
bool ManageFile::end(){
  if(file.is_open()){
      file.clear();
      if(this->type == "r"){ file.seekg( 0 , ios_base::end );
      }

      else if(this->type == "w"){ file.seekp( 0 , ios_base::end );
      }

      else if(this->type == "rw"){ file.seekg( 0 , ios_base::end );
      }
    return true;
  }
  else{
    cout << "erreur : methode end , fichier : " << nameFile << " , n'est pas ouvert !" <<'\n';
    return false;
  }
}
bool ManageFile::setPosition(int position){
  if(file.is_open()){
    file.clear();
    if(this->type == "r"){ file.seekg( ios_base::beg);
    }

    else if(this->type == "w"){ file.seekp(ios_base::beg);
    }

    else if(this->type == "rw"){ file.seekg( ios_base::beg);
    }
    string s ;
    int i = 0 ;
    while(i != position && getline(file,s)){
      i++;
    }
    return true;
  }
  else{
    cout << "erreur : methode setPosition , fichier : " << nameFile << " , n'est pas ouvert !" <<'\n';
    return false ;
  }
}

char ManageFile::readChar(){
  if(file.is_open() == false){
    file.open(nameFile , ios::in);
    type = "r";
  }

  if(file.is_open()){
    char c;
    file.get(c);
    return c;
  }
  else{
    cout << "erreur : methode readChar , Impossible d'ouvrir le fichier " <<nameFile<< " en lecture !" <<'\n';
    exit(-1);
  }
}

string ManageFile::readLine(){
  if(file.is_open() == false){
    file.open(nameFile , ios::in);
    type = "r";
  }

  if(file.is_open()){
    string s = "" ;
    if(getline(file,s))
      return s;
    else
      return "";
  }
  else{
    cout << "erreur : methode readLine , Impossible d'ouvrir le fichier " <<nameFile<< " en lecture !" <<'\n';
    exit(-1);
  }
}

string* ManageFile::readWordsOfLine(char separateur){
  if(file.is_open() == false){
    file.open(nameFile , ios::in);
    type = "r";
  }
  if(file.is_open()){
    string s = "" ;
    getline(file,s);

    int n = 0 ;
    for(unsigned i = 0 ; i <s.length() ; i++){
      if(s[i] == separateur)
        n++;
    }

    string* tmp = new string[n];
    int j = 0 ;
    string tmps = "";
    for(unsigned i = 0 ; i < s.length() ;i++){
      if(s[i] != separateur){
        tmps += s[i];
      }
      else{
        tmp[j] = tmps ;
        j++;
        tmps = "";
      }
    }
    return tmp ;
  }
  else{
    cout << "erreur : methode readWordsOfLine , Impossible d'ouvrir le fichier " <<nameFile<< " en lecture !"<< '\n';
    exit(-1);
  }
}

void ManageFile::write(string s){
  if(file.is_open() == false){
    file.open(nameFile , ios::out);
    type = "w";
  }
  if(file.is_open())
    file << s ;
  else{
    cout << "erreur : methode write(string) , Impossible d'ouvrir le fichier " <<nameFile<< " en écriture !"<< '\n';
    exit(-1);
  }
}

void ManageFile::write(char c){
  if(file.is_open() == false){
    file.open(nameFile , ios::out);
    type = "w";
  }
  if(file.is_open())
    file << c ;
  else{
    cout << "erreur : methode write(char) , Impossible d'ouvrir le fichier " <<nameFile<< " en écriture !" <<'\n';
    exit(-1);
  }
}

void ManageFile::erase(){
  if(file.is_open()){
    file.close();
    if(this->type == "r") file.open(nameFile , ios::in | ios::trunc);
    else if(this->type == "w") file.open(nameFile , ios::out | ios::trunc);
    else if(this->type == "rw")  file.open(nameFile , ios::in | ios::out | ios::trunc);
  }
  else
    cout << "erreur : methode erase , fichier : " << nameFile << " , n'est pas ouvert !" <<'\n';
}

void ManageFile::close(){
  if(file.is_open())
    file.close();
  else
    cout << "erreur : methode close , fichier : " << nameFile << " , est déja fermé !" <<'\n';
}
