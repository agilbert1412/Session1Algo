//============================================================================
// Name        : main.cpp
// Author      : Slim Ben Yahia
// Author      : Alex Gilbert
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "arret.h"
#include "auxiliaires.h"
#include "coordonnees.h"
#include "ligne.h"
#include "station.h"
#include "voyage.h"
#include "reseau.h"
#include "gestionnaire.h"
#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;
//
//const string agencyFile = "RTC/agency.txt";
//const string calendarDatesFile = "RTC/calendar_dates.txt";
//const string routesFile = "RTC/routes.txt";
//const string shapesFile = "RTC/shapes.txt";
//const string stopsFile = "RTC/stops.txt";
//const string stopTimesFile = "RTC/stop_times.txt";
//const string transfersFile = "RTC/transfers.txt";
//const string tripsFile = "RTC/trips.txt";
//const string resultatFile = "Resultat.txt";
//const char delimiter { ',' };

string TrouverNomRepertoire(const string& cheminFichier)
{
     size_t position = cheminFichier.find_last_of("\\/");
     if (string::npos == position)
         return "";
     return cheminFichier.substr(0, position);
}

int main(int argc, char *argv[]) {

	string repertoireDossierCourant = TrouverNomRepertoire(argv[0]) + "/";
	clock_t clkStart { };
	clock_t clkEnd { };
	double timePassed { };

	//cout << "Lecture des fichiers..." << endl;

	clkStart = clock();

	Gestionnaire gest = Gestionnaire(repertoireDossierCourant);

	clkEnd = clock();
	timePassed = (double)(clkEnd - clkStart) / CLOCKS_PER_SEC;

	cout << "Bienvenue dans l'application RTC" << endl;
	cout << "Chargement des données terminé en " << timePassed << " secondes" << endl;

	bool quitter = false;
	while (!quitter)
	{
		cout << endl << endl;
		string choix;
		cout << "Menu" << endl;
		cout << "1 - Stations à proximité" << endl;
		cout << "2 - Consulter horaire du bus" << endl;
		cout << "3 - Itinéraire" << endl;
		cout << "4 - Stats de connectivité" << endl;
		cout << "Sélectionner une option en indiquant un chiffre ou autre chose pour quitter: ";
		getline(cin, choix);
		if (choix == "1")
		{
			string lat, lon, rayon;
			double latd, lond, rayond;
			cout << "Entrez vos coordonnées GPS" << endl;
			cout << "Latitude: ";
			getline(cin, lat);
			cout << "Longitude: ";
			getline(cin, lon);
			cout << "Entrez un rayon (en Km) pour la recherche: ";
			getline(cin, rayon);
			stringstream myStream1(lat);
			stringstream myStream2(lon);
			stringstream myStream3(rayon);
			if ((myStream1 >> latd) && (myStream2 >> lond) && (myStream3 >> rayond))
			{
				vector<pair<double, Station*>> stationsProche = gest.trouver_stations_environnantes(Coordonnees(latd, lond), rayond);
				for (int i = 0; i < stationsProche.size(); i++)
				{
					cout << "À une distance de " << stationsProche[i].first << "km:" << endl;
					cout << stationsProche[i].second->getId() << " - " <<  stationsProche[i].second->getDescription() << endl;
				}
			}
			else
			{
				cout << "Entrée invalide." << endl;
			}
		}
		else if (choix == "2")
		{
			string annee, mois, jour, heure, minute, secondes, noBus, noStation;
			int anneei, moisi, jouri, heurei, minutei, secondei, noStationi;
			cout << "Entrez la date qui vous intéresse!" << endl;
			cout << "annee [défaut=2016] : ";
			getline(cin, annee);
			cout << "mois [défaut=10] : ";
			getline(cin, mois);
			cout << "jour [défaut=5] : ";
			getline(cin, jour);
			cout << "Entrez l'heure de début de l'horaire!" << endl;
			cout << "heure [défaut=20] : ";
			getline(cin, heure);
			cout << "minutes [défaut=20] : ";
			getline(cin, minute);
			cout << "secondes [défaut=44] : ";
			getline(cin, secondes);
			cout << "Entrez le numéro du bus: ";
			getline(cin, noBus);
			cout << "Entrez le numéro de la station: ";
			getline(cin, noStation);
			stringstream myStream1(annee);
			stringstream myStream2(mois);
			stringstream myStream3(jour);
			stringstream myStream4(heure);
			stringstream myStream5(minute);
			stringstream myStream6(secondes);
			stringstream myStream7(noStation);
			if (!(myStream1 >> anneei))
				anneei = 2016;
			if (anneei < 1900 || anneei > 2050)
				anneei = 2016;
			if (!(myStream2 >> moisi))
				moisi = 10;
			if (moisi < 1 || moisi > 12)
				moisi = 10;
			if (!(myStream3 >> jouri))
				jouri = 5;
			if (jouri < 1 || jouri > 31)
				jouri = 5;
			if (!(myStream4 >> heurei))
				heurei = 20;
			if (heurei < 0 || heurei >= 30)
				heurei = 20;
			if (!(myStream5 >> minutei))
				minutei = 20;
			if (minutei < 0 || minutei >= 60)
				minutei = 20;
			if (!(myStream6 >> secondei))
				secondei = 44;
			if (secondei < 0 || secondei >= 60)
				secondei = 44;
			if ((myStream7 >> noStationi) && gest.station_existe(noStationi) && gest.bus_existe(noBus))
			{
				Ligne laLigne = gest.getLigne(noBus);
				pair<string, string> dests = laLigne.getDestinations();
				Station laStation = gest.getStation(noStationi);
				if (!dests.first.empty())
				{
					vector<Heure> horaire = gest.trouver_horaire(Date {anneei, moisi, jouri}, Heure {heurei, minutei, secondei}, noBus, noStationi, dests.first);
					if (horaire.size() > 0)
					{
						cout << laLigne.categorieToString(laLigne.getCategorie()) << " " << laLigne.getNumero() << " : " << dests.first << endl;
						cout << laStation.getId() << " - " << laStation.getDescription() << endl;
						for (unsigned int i = 0; i < horaire.size(); i++)
						{
							cout << horaire[i] << endl;
						}
					}
					if (!dests.second.empty())
					{
						horaire = gest.trouver_horaire(Date {anneei, moisi, jouri}, Heure {heurei, minutei, secondei}, noBus, noStationi, dests.second);
						if (horaire.size() > 0)
						{
							cout << laLigne.categorieToString(laLigne.getCategorie()) << " " << laLigne.getNumero() << " : " << dests.second << endl;
							cout << laStation.getId() << " - " << laStation.getDescription() << endl;
							for (unsigned int i = 0; i < horaire.size(); i++)
							{
								cout << horaire[i] << endl;
							}
						}
					}
				}
			}
			else
			{
				cout << "Entrée Invalide" << endl;
			}
		}

		else if (choix == "3")
		{
			string orig, dest, annee, mois, jour, heure, minute, secondes;
			int origi, desti, anneei, moisi, jouri, heurei, minutei, secondei;

			bool success = false;

			map<string, Coordonnees> carnet;
			carnet.insert(make_pair("1 - 3475 avenue maricourt, Québec", Coordonnees { 46.760074, -71.319867 }));
			carnet.insert(make_pair("2 - 2325 vie étudiante, Québec", Coordonnees { 46.778398, -71.26853 }));
			carnet.insert(make_pair("3 - Cineplex odéon sainte-foy", Coordonnees { 46.785923, -71.354046 }));
			carnet.insert(make_pair("4 - Pavillon pouliot", Coordonnees { 46.776635, -71.270671 }));
			carnet.insert(make_pair("5 - 2476, avenue de lisieux, québec", Coordonnees { 46.857245, -71.206804 }));
			carnet.insert(make_pair("6 - Pavillon desjardin", Coordonnees { 46.778808, -71.270014 }));
			vector<Coordonnees> carnetIndice;
			carnetIndice.push_back(Coordonnees { 46.760074, -71.319867 });

			cout << "Choisir votre point de départ" << endl;
			cout << "Carnets d'adresse" << endl;
			for (auto it : carnet)
			{
				carnetIndice.push_back(it.second);
				cout << it.first << ": (" << it.second.getLatitude() << ", " << it.second.getLongitude() << ")" << endl;
			}
			cout << "Sélectionner une adresse en indiquant un chiffre: ";
			getline(cin, orig);
			stringstream myStreamOrig(orig);
			if (myStreamOrig >> origi && origi > 0 && origi < 7)
			{
				cout << "Choisir votre point d'arrivée" << endl;
				cout << "Carnets d'adresse" << endl;
				for (auto it : carnet)
				{
					cout << it.first << ": (" << it.second.getLatitude() << ", " << it.second.getLongitude() << ")" << endl;
				}
				cout << "Sélectionner une adresse en indiquant un chiffre: ";
				getline(cin, dest);
				stringstream myStreamDest(dest);
				if (myStreamDest >> desti && desti > 0 && desti < 7)
				{
					cout << "Entrez la date qui vous intéresse!" << endl;
					cout << "annee [défaut=2016] : ";
					getline(cin, annee);
					cout << "mois [défaut=10] : ";
					getline(cin, mois);
					cout << "jour [défaut=5] : ";
					getline(cin, jour);
					cout << "Entrez l'heure de début de l'horaire!" << endl;
					cout << "heure [défaut=20] : ";
					getline(cin, heure);
					cout << "minutes [défaut=22] : ";
					getline(cin, minute);
					cout << "secondes [défaut=29] : ";
					getline(cin, secondes);
					stringstream myStream1(annee);
					stringstream myStream2(mois);
					stringstream myStream3(jour);
					stringstream myStream4(heure);
					stringstream myStream5(minute);
					stringstream myStream6(secondes);
					if (!(myStream1 >> anneei))
						anneei = 2016;
					if (anneei < 1900 || anneei > 2050)
						anneei = 2016;
					if (!(myStream2 >> moisi))
						moisi = 10;
					if (moisi < 1 || moisi > 12)
						moisi = 10;
					if (!(myStream3 >> jouri))
						jouri = 5;
					if (jouri < 1 || jouri > 31)
						jouri = 5;
					if (!(myStream4 >> heurei))
						heurei = 20;
					if (heurei < 0 || heurei >= 30)
						heurei = 20;
					if (!(myStream5 >> minutei))
						minutei = 22;
					if (minutei < 0 || minutei >= 60)
						minutei = 22;
					if (!(myStream6 >> secondei))
						secondei = 29;
					if (secondei < 0 || secondei >= 60)
						secondei = 29;
					cout << "Initialisation du réseau..." << endl;
					vector<unsigned int> courtChemin = gest.plus_court_chemin(Date {anneei, moisi, jouri}, Heure {heurei, minutei, secondei}, carnetIndice[origi], carnetIndice[desti]);
					cout << courtChemin[0] << " - Départ" << endl;
					for (unsigned int i = 1; i < courtChemin.size() - 1; i++)
					{
						Station s = gest.getStation(courtChemin[i]);
						cout << s.getId() << " - " << s.getDescription() << endl;
					}
					cout << courtChemin[courtChemin.size() - 1] << " - Arrivée" << endl;
					success = true;
				}
			}
			if (!success)
			{
				cout << "Entrée invalide." << endl;
			}
		}
		else if (choix == "4")
		{
			string annee, mois, jour, heure, minute, secondes;
			int anneei, moisi, jouri, heurei, minutei, secondei;
			cout << "Entrez la date qui vous intéresse!" << endl;
			cout << "annee [défaut=2016] : ";
			getline(cin, annee);
			cout << "mois [défaut=10] : ";
			getline(cin, mois);
			cout << "jour [défaut=5] : ";
			getline(cin, jour);
			cout << "Entrez l'heure de début de l'horaire!" << endl;
			cout << "heure [défaut=20] : ";
			getline(cin, heure);
			cout << "minutes [défaut=29] : ";
			getline(cin, minute);
			cout << "secondes [défaut=57] : ";
			getline(cin, secondes);
			stringstream myStream1(annee);
			stringstream myStream2(mois);
			stringstream myStream3(jour);
			stringstream myStream4(heure);
			stringstream myStream5(minute);
			stringstream myStream6(secondes);
			if (!(myStream1 >> anneei))
				anneei = 2016;
			if (anneei < 1900 || anneei > 2050)
				anneei = 2016;
			if (!(myStream2 >> moisi))
				moisi = 10;
			if (moisi < 1 || moisi > 12)
				moisi = 10;
			if (!(myStream3 >> jouri))
				jouri = 5;
			if (jouri < 1 || jouri > 31)
				jouri = 5;
			if (!(myStream4 >> heurei))
				heurei = 20;
			if (heurei < 0 || heurei >= 30)
				heurei = 20;
			if (!(myStream5 >> minutei))
				minutei = 29;
			if (minutei < 0 || minutei >= 60)
				minutei = 29;
			if (!(myStream6 >> secondei))
				secondei = 57;
			if (secondei < 0 || secondei >= 60)
				secondei = 57;
			cout << "Calcul en cours..." << endl;
			bool connexeAvec = gest.reseau_est_fortement_connexe(Date {anneei, moisi, jouri}, Heure {heurei, minutei, secondei}, true);
			bool connexeSans = gest.reseau_est_fortement_connexe(Date {anneei, moisi, jouri}, Heure {heurei, minutei, secondei}, false);
			if (connexeAvec)
				cout << "Avec les arêtes de transfert, le réseau est fortement connexe." << endl;
			else
				cout << "Avec les arêtes de transfert, le réseau n'est pas fortement connexe." << endl;
			if (connexeSans)
				cout << "Sans les arêtes de transfert, le réseau est fortement connexe." << endl;
			else
				cout << "Sans les arêtes de transfert, le réseau n'est pas fortement connexe." << endl;
		}
		else
		{
			cout << "Au revoir!";
			quitter = true;
		}
	}


	return 0;

//	// tests de Gestionnaire //
//
//	cout << endl;
//	// tests de date_est_prise_en_charge
//	cout << "date_est_prise_en_charge: ";
//	cout << (gest.date_est_prise_en_charge(Date(2014, 9, 2)) == 0);
//	cout << (gest.date_est_prise_en_charge(Date(2016, 8, 16)) == 1);
//	cout << (gest.date_est_prise_en_charge(Date(2016, 12, 30)) == 0);
//	cout << endl;
//	// tests de bus_existe
//	cout << "bus_existe: ";
//	cout << (gest.bus_existe("1") == 1);
//	cout << (gest.bus_existe("2") == 0);
//	cout << (gest.bus_existe("3") == 1);
//	cout << (gest.bus_existe("4") == 1);
//	cout << (gest.bus_existe("5") == 0);
//	cout << (gest.bus_existe("10") == 1);
//	cout << (gest.bus_existe("800") == 1);
//	cout << endl;
//	// tests de station_existe
//	cout << "station_existe: ";
//	cout << (gest.station_existe(4955) == 1);
//	cout << (gest.station_existe(4956) == 1);
//	cout << (gest.station_existe(1001) == 0);
//	cout << (gest.station_existe(4957) == 1);
//	cout << (gest.station_existe(1002) == 0);
//	cout << (gest.station_existe(1003) == 1);
//	cout << (gest.station_existe(1004) == 0);
//	cout << (gest.station_existe(4958) == 1);
//	cout << (gest.station_existe(4959) == 1);
//	cout << endl;
//	// tests de getLigne et getStation
//	cout << "getLigne et getStation: ";
//	try
//	{
//		cout << (gest.getLigne("10").getNumero() == "10");
//	}
//	catch (char const* msg)
//	{
//		cout << 0;
//	}
//	try
//	{
//		cout << (gest.getLigne("2").getNumero());
//	}
//	catch (char const* msg)
//	{
//		cout << (strcmp(msg, "Il n’existe pas de ligne ayant ce numéro") == 0);
//	}
//	try
//	{
//		cout << (gest.getStation(4955).getId() == 4955);
//	}
//	catch (char const* msg)
//	{
//		cout << 0;
//	}
//	try
//	{
//		cout << (gest.getStation(1002).getId());
//	}
//	catch (char const* msg)
//	{
//		cout << (strcmp(msg, "Il n’existe pas de station ayant cet identifiant") == 0);
//	}
//	cout << endl;
//	// tests de trouver_voyages
//	cout << "trouver_voyage: ";
//	vector<Voyage*> vect1 = gest.trouver_voyages(1412, "7");
//	cout << (vect1.size() == 262);
//	cout << (vect1[4]->getLigne()->getNumero() == "7");
//	cout << (vect1[245]->getLigne()->getNumero() == "7");
//	cout << (vect1[4]->arretDeLaStation(1412).getStationId() == 1412);
//	cout << (vect1[55]->arretDeLaStation(1412).getStationId() == 1412);
//	vector<Voyage*> vect2 = gest.trouver_voyages(1412, "800");
//	cout << (vect2.size() == 0);
//	vector<Voyage*> vect3 = gest.trouver_voyages(1412, "907");
//	cout << (vect3.size() == 10);
//	vector<Voyage*> vect4 = gest.trouver_voyages(3371, "800");
//	cout << (vect4.size() == 718);
//	vector<Voyage*> vect5 = gest.trouver_voyages(3371, "7");
//	cout << (vect5.size() == 0);
//	cout << endl;
//	// tests de get_bus_destinations
//	cout << "get_bus_destinations: ";
//	pair<string, string> paire1 = gest.get_bus_destinations(1412, "7");
//	cout << (paire1.first == "Pointe-de-Sainte-Foy (Ouest)");
//	cout << (paire1.second == "Place D'Youville / Vieux-Québec (Est)");
//	pair<string, string> paire2 = gest.get_bus_destinations(1412, "800");
//	cout << (paire2.first == "");
//	cout << (paire2.second == "");
//	pair<string, string> paire3 = gest.get_bus_destinations(1412, "907");
//	cout << (paire3.first == "Place D'Youville (Est)");
//	cout << (paire3.second == "Pointe-de-Sainte-Foy (Ouest)");
//	pair<string, string> paire4 = gest.get_bus_destinations(3371, "800");
//	cout << (paire4.first == "Beauport (Est)");
//	cout << (paire4.second == "Pointe-de-Sainte-Foy (Ouest)");
//	pair<string, string> paire5 = gest.get_bus_destinations(3371, "7");
//	cout << (paire5.first == "");
//	cout << (paire5.second == "");
//	pair<string, string> paire6 = gest.get_bus_destinations(5882, "915");
//	cout << (paire6.first == "Cap-Rouge (Ouest)");
//	cout << (paire6.second == "");
//	cout << endl;
//	// Tests de trouver_stations_environnantes
//	cout << "trouver_stations_environnantes: ";
//	vector<pair<double, Station*>> stationsProche1 = gest.trouver_stations_environnantes(Coordonnees(46.788183, -71.273083), 0.12);
//	cout << (stationsProche1.size() == 1);
//	cout << (stationsProche1[0].first < 0.12);
//	cout << (stationsProche1[0].second->getId() == 1412);
//	vector<pair<double, Station*>> stationsProche2 = gest.trouver_stations_environnantes(Coordonnees(46.788183, -71.273083), 0.32);
//	cout << (stationsProche2.size() == 4);
//	cout << (stationsProche2[0].second->getId() == 1412);
//	cout << (stationsProche2[1].second->getId() == 1473);
//	cout << (stationsProche2[2].second->getId() == 2442);
//	cout << (stationsProche2[3].second->getId() == 2437);
//	cout << (stationsProche2[0].first < stationsProche2[1].first);
//	cout << (stationsProche2[1].first < stationsProche2[2].first);
//	cout << (stationsProche2[2].first < stationsProche2[3].first);
//	cout << endl;
//	// Tests de trouver_horaire
//	cout << "trouver_horaire: ";
//	Heure heure1 = Heure {0, 0, 0};
//	vector<Heure> horaire1 = gest.trouver_horaire(Date {2016, 8, 16}, heure1, "7", 1412, "Place D'Youville / Vieux-Québec (Est)");
//	cout << (horaire1.size() == 0);
//	vector<Heure> horaire2 = gest.trouver_horaire(Date {2016, 8, 16}, heure1, "7", 1412, "Pointe-de-Sainte-Foy (Ouest)");
//	cout << (horaire2.size() == 48);
//	for (int i = 0; i < 48; i++)
//	{
//		if (horaire2[i] <= heure1)
//			cout << 0;
//	}
//	Heure heure2 = Heure {20, 0, 0};
//	vector<Heure> horaire3 = gest.trouver_horaire(Date {2016, 8, 16}, heure2, "7", 1412, "Pointe-de-Sainte-Foy (Ouest)");
//	cout << (horaire3.size() == 42);
//	for (unsigned int i = 0; i < horaire3.size(); i++)
//	{
//		if (horaire3[i] <= heure2)
//			cout << 0;
//	}
//	Heure heure3 = Heure {23, 0, 0};
//	vector<Heure> horaire4 = gest.trouver_horaire(Date {2016, 8, 16}, heure3, "7", 1412, "Pointe-de-Sainte-Foy (Ouest)");
//	cout << (horaire4.size() == 23);
//	for (unsigned int i = 0; i < horaire4.size(); i++)
//	{
//		if (horaire4[i] <= heure3)
//			cout << 0;
//	}
//	try
//	{
//		cout << (gest.trouver_horaire(Date {2016, 12, 16}, heure3, "7", 1412, "Pointe-de-Sainte-Foy (Ouest)").size() == 0);
//	}
//	catch (char const* msg)
//	{
//		cout << 0;
//	}
//	cout << endl;
////	// Tests de initialiser_reseau
////	cout << "initialiser_reseau 1: ";
////	gest.initialiser_reseau(Date {2016, 12, 16}, heure2, heure3, Coordonnees {46.788274, -71.272794}, Coordonnees {46.788440, -71.270579}, 0.55, 0.55);
////	cout << (gest.m_reseau.nombreSommets() == 4606);
////	cout << (gest.m_reseau.nombreArcs() == 96614);
////	cout << (gest.m_reseau.sommetExiste(0));
////	cout << (gest.m_reseau.sommetExiste(1));
////	cout << (gest.m_reseau.sommetExiste(1412));
////	cout << (gest.m_reseau.sommetExiste(1420));
////	cout << (gest.m_reseau.sommetExiste(3001));
////	cout << (gest.m_reseau.arcExiste(0, 1));
////	cout << (!gest.m_reseau.arcExiste(1, 0));
////	cout << (gest.m_reseau.getCoutArc(0, 1) == 122);
////	cout << (gest.m_reseau.arcExiste(1412, 1413));
////	cout << (gest.m_reseau.getCoutArc(1412, 1413) == 334);
////	cout << endl;
////	cout << "initialiser_reseau 2: ";
////	gest.initialiser_reseau(Date {2016, 8, 16}, heure2, heure3, Coordonnees {46.788274, -71.272794}, Coordonnees {46.780440, -71.300579}, 0.55, 0.55);
////	cout << (gest.m_reseau.nombreSommets() == 4606);
////	cout << (gest.m_reseau.nombreArcs() == 96739);
////	cout << gest.m_reseau.sommetExiste(0);
////	cout << gest.m_reseau.sommetExiste(1);
////	cout << gest.m_reseau.sommetExiste(1412);
////	cout << gest.m_reseau.sommetExiste(1420);
////	cout << gest.m_reseau.sommetExiste(3001);
////	cout << (!gest.m_reseau.arcExiste(0, 1));
////	cout << (!gest.m_reseau.arcExiste(1, 0));
////	cout << (gest.m_reseau.arcExiste(1412, 1413));
////	cout << (gest.m_reseau.getCoutArc(1412, 1413) == 60);
////	cout << endl;
////	cout << "reseau_est_fortement_connexe: ";
////	bool connexe1 = gest.reseau_est_fortement_connexe(Date {2016, 12, 16}, heure2, true);
////	cout << !connexe1 << endl;
////	bool connexe2 = gest.reseau_est_fortement_connexe(Date {2016, 8, 16}, heure2, true);
////	cout << !connexe2 << endl;
////	bool connexe3 = gest.reseau_est_fortement_connexe(Date {2016, 10, 5}, heure2, true);
////	cout << !connexe3 << endl;
////	bool connexe4 = gest.reseau_est_fortement_connexe(Date {2016, 8, 16}, heure3, false);
////	cout << !connexe4 << endl;
////	cout << endl;
////	cout << "composantes_fortement_connexes: ";
////	vector<vector<unsigned int>> vectorConnexe1;
////	gest.composantes_fortement_connexes(Date {2016, 12, 16}, heure2, vectorConnexe1, true);
////	cout << vectorConnexe1.size() << endl;
////	vector<vector<unsigned int>> vectorConnexe2;
////	gest.composantes_fortement_connexes(Date {2016, 8, 16}, heure2, vectorConnexe2, true);
////	cout << vectorConnexe2.size() << endl;
////	vector<vector<unsigned int>> vectorConnexe3;
////	gest.composantes_fortement_connexes(Date {2016, 10, 5}, heure2, vectorConnexe3, true);
////	cout << vectorConnexe3.size() << endl;
////	vector<vector<unsigned int>> vectorConnexe4;
////	gest.composantes_fortement_connexes(Date {2016, 8, 16}, heure3, vectorConnexe4, false);
////	cout << vectorConnexe4.size() << endl;
//	cout << endl;
//	cout << "plus_court_chemin: ";
//	Coordonnees depart1 = Coordonnees {46.778808, -71.270014};
//	Coordonnees arrivee1 = Coordonnees {46.760074, -71.319867};
//	Date dateCourtChemin1 = Date { 2016, 10, 5 };
//	Heure heure4 = Heure { 12, 0, 0 };
//	vector<unsigned int> courtChemin1 = gest.plus_court_chemin(dateCourtChemin1, heure4, depart1, arrivee1);
//	cout << courtChemin1.size() << endl;
//	cout << courtChemin1[0] << " - Départ" << endl;
//	for (unsigned int i = 1; i < courtChemin1.size() - 1; i++)
//	{
//		Station s = gest.getStation(courtChemin1[i]);
//		cout << s.getId() << ": " << s.getNom() << " (" << s.getDescription() << ")" << endl;
//	}
//	cout << courtChemin1[courtChemin1.size() - 1] << " - Arrivée" << endl;

	//return 0;
}
