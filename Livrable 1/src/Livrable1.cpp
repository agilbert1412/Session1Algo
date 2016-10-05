//============================================================================
// Name        : Livrable.cpp
// Author      : Slim Ben Yahia
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "auxiliaires.h"

using namespace std;

int main() {

	Heure* heure1 = new Heure { };

	vector<vector<string>> resultats1;
	string nomFichier1 = "/media/sf_Dossier_partage_VM/Énoncé/RTC/routes.txt";
	char delimiter1 = ',';
	bool entete1 = false;
	lireFichier(nomFichier1, resultats1, delimiter1, entete1);

	Heure* heure2 = new Heure { };

	vector<vector<string>> resultats2;
	string nomFichier2 = "/media/sf_Dossier_partage_VM/Énoncé/RTC/stops.txt";
	char delimiter2 = ',';
	bool entete2 = false;
	lireFichier(nomFichier2, resultats2, delimiter2, entete2);

	Heure* heure3 = new Heure { };

	vector<vector<string>> resultats3;
	string nomFichier3 = "/media/sf_Dossier_partage_VM/Énoncé/RTC/shapes.txt";
	char delimiter3 = ',';
	bool entete3 = false;
	lireFichier(nomFichier3, resultats3, delimiter3, entete3);

	Heure* heure4 = new Heure { };

	vector<vector<string>> resultats4;
	string nomFichier4 = "/media/sf_Dossier_partage_VM/Énoncé/RTC/stop_times.txt";
	char delimiter4 = ',';
	bool entete4 = false;
	lireFichier(nomFichier4, resultats4, delimiter4, entete4);

	Heure* heure5 = new Heure { };

	cout << *heure1 << endl;
	cout << *heure2 << endl;
	cout << *heure3 << endl;
	cout << *heure4 << endl;
	cout << *heure5 << endl;

	return 0;
}
