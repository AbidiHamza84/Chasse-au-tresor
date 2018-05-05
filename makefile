all : lib

lib:  obj/Armure.o obj/AttackObject.o obj/Boucanier.o obj/ClearSrc.o obj/Colors.o obj/Cord.o obj/Corsaire.o obj/DefenseObject.o obj/Fight.o obj/Flibustrier.o obj/Gameplay.o obj/Input.o obj/Machette.o obj/main.o obj/ManageFile.o obj/Map.o obj/Menu.o obj/Mousquet.o obj/Object.o obj/Pelle.o obj/Personne.o obj/Pistolet.o obj/SafeObject.o obj/Sauvegarde.o obj/WarObject.o
	ar -q lib/librairie.a obj/Armure.o obj/AttackObject.o obj/Boucanier.o obj/ClearSrc.o obj/Colors.o obj/Cord.o obj/Corsaire.o obj/DefenseObject.o obj/Fight.o obj/Flibustrier.o obj/Gameplay.o obj/Input.o obj/Machette.o obj/ManageFile.o obj/Map.o obj/Menu.o obj/Mousquet.o obj/Object.o obj/Pelle.o obj/Personne.o obj/Pistolet.o obj/SafeObject.o obj/Sauvegarde.o obj/WarObject.o 
	g++ -std=c++11 -pg -o bin/Executable src/main.cpp src/Armure.cpp src/AttackObject.cpp src/Boucanier.cpp src/ClearSrc.cpp src/Colors.cpp src/Cord.cpp src/Corsaire.cpp src/DefenseObject.cpp src/Fight.cpp src/Flibustrier.cpp src/Gameplay.cpp src/Input.cpp src/Machette.cpp src/ManageFile.cpp src/Map.cpp src/Menu.cpp src/Mousquet.cpp src/Object.cpp src/Pelle.cpp src/Personne.cpp src/Pistolet.cpp src/SafeObject.cpp src/Sauvegarde.cpp src/WarObject.cpp   lib/librairie.a

obj/main.o :  src/main.cpp
	g++ -std=c++11 -pg -o obj/main.o -c src/main.cpp

obj/Armure.o : src/Armure.cpp
	g++ -std=c++11 -pg -o obj/Armure.o -c src/Armure.cpp
obj/AttackObject.o : src/AttackObject.cpp
	g++ -std=c++11 -pg -o obj/AttackObject.o -c src/AttackObject.cpp
obj/Boucanier.o : src/Boucanier.cpp
	g++ -std=c++11 -pg -o obj/Boucanier.o -c src/Boucanier.cpp
obj/ClearSrc.o : src/ClearSrc.cpp
	g++ -std=c++11 -pg -o obj/ClearSrc.o -c src/ClearSrc.cpp
obj/Colors.o : src/Colors.cpp
	g++ -std=c++11 -pg -o obj/Colors.o -c src/Colors.cpp
obj/Cord.o : src/Cord.cpp
	g++ -std=c++11 -pg -o obj/Cord.o -c src/Cord.cpp
obj/Corsaire.o : src/Corsaire.cpp
	g++ -std=c++11 -pg -o obj/Corsaire.o -c src/Corsaire.cpp
obj/DefenseObject.o : src/DefenseObject.cpp
	g++ -std=c++11 -pg -o obj/DefenseObject.o -c src/DefenseObject.cpp
obj/Fight.o : src/Fight.cpp
	g++ -std=c++11 -pg -o obj/Fight.o -c src/Fight.cpp
obj/Flibustrier.o : src/Flibustrier.cpp
	g++ -std=c++11 -pg -o obj/Flibustrier.o -c src/Flibustrier.cpp
obj/Gameplay.o : src/Gameplay.cpp
	g++ -std=c++11 -pg -o obj/Gameplay.o -c src/Gameplay.cpp
obj/Input.o : src/Input.cpp
	g++ -std=c++11 -pg -o obj/Input.o -c src/Input.cpp
obj/Machette.o : src/Machette.cpp
	g++ -std=c++11 -pg -o obj/Machette.o -c src/Machette.cpp
obj/ManageFile.o : src/ManageFile.cpp
	g++ -std=c++11 -pg -o obj/ManageFile.o -c src/ManageFile.cpp
obj/Map.o : src/Map.cpp
	g++ -std=c++11 -pg -o obj/Map.o -c src/Map.cpp
obj/Menu.o : src/Menu.cpp
	g++ -std=c++11 -pg -o obj/Menu.o -c src/Menu.cpp
obj/Mousquet.o : src/Mousquet.cpp
	g++ -std=c++11 -pg -o obj/Mousquet.o -c src/Mousquet.cpp
obj/Object.o : src/Object.cpp
	g++ -std=c++11 -pg -o obj/Object.o -c src/Object.cpp
obj/Pelle.o : src/Pelle.cpp
	g++ -std=c++11 -pg -o obj/Pelle.o -c src/Pelle.cpp
obj/Personne.o : src/Personne.cpp
	g++ -std=c++11 -pg -o obj/Personne.o -c src/Personne.cpp
obj/Pistolet.o : src/Pistolet.cpp
	g++ -std=c++11 -pg -o obj/Pistolet.o -c src/Pistolet.cpp
obj/SafeObject.o : src/SafeObject.cpp
	g++ -std=c++11 -pg -o obj/SafeObject.o -c src/SafeObject.cpp
obj/Sauvegarde.o : src/Sauvegarde.cpp
	g++ -std=c++11 -pg -o obj/Sauvegarde.o -c src/Sauvegarde.cpp
obj/WarObject.o : src/WarObject.cpp
	g++ -std=c++11 -pg -o obj/WarObject.o -c src/WarObject.cpp

clean:
	rm -rf obj/*.o
mrproper: clean
	rm -rf bin/Executable
