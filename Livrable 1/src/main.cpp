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

struct comparerStations
{
    inline bool operator() (const Station& p_station1, const Station& p_station2)
    {
        return (p_station1.getId() < p_station2.getId());
    }
};

struct comparerLignes
{
    inline bool operator() (const Ligne& p_ligne1, const Ligne& p_ligne2)
    {
        return (p_ligne1.getNumero() < p_ligne2.getNumero());
    }
};

int main(int argc, char *argv[]) {

	string repertoireDossierCourant = TrouverNomRepertoire(argv[0]) + "/";
	clock_t clkStart { };
	clock_t clkEnd { };
	double timePassed { };

	cout << "Lecture des fichiers..." << endl;

	clkStart = clock();

	Gestionnaire gest = Gestionnaire(repertoireDossierCourant);

	clkEnd = clock();
	timePassed = (double)(clkEnd - clkStart) / CLOCKS_PER_SEC;

	cout << "Lecture terminée (" << timePassed << " secondes)" << endl;


	// tests de Gestionnaire //

	cout << endl;
	// tests de date_est_prise_en_charge
	cout << "date_est_prise_en_charge: ";
	cout << (gest.date_est_prise_en_charge(Date(2014, 9, 2)) == 0);
	cout << (gest.date_est_prise_en_charge(Date(2016, 8, 16)) == 1);
	cout << (gest.date_est_prise_en_charge(Date(2016, 12, 30)) == 0);
	cout << endl;
	// tests de bus_existe
	cout << "bus_existe: ";
	cout << (gest.bus_existe("1") == 1);
	cout << (gest.bus_existe("2") == 0);
	cout << (gest.bus_existe("3") == 1);
	cout << (gest.bus_existe("4") == 1);
	cout << (gest.bus_existe("5") == 0);
	cout << (gest.bus_existe("10") == 1);
	cout << (gest.bus_existe("800") == 1);
	cout << endl;
	// tests de station_existe
	cout << "station_existe: ";
	cout << (gest.station_existe(4955) == 1);
	cout << (gest.station_existe(4956) == 1);
	cout << (gest.station_existe(1001) == 0);
	cout << (gest.station_existe(4957) == 1);
	cout << (gest.station_existe(1002) == 0);
	cout << (gest.station_existe(1003) == 1);
	cout << (gest.station_existe(1004) == 0);
	cout << (gest.station_existe(4958) == 1);
	cout << (gest.station_existe(4959) == 1);
	cout << endl;
	// tests de getLigne et getStation
	cout << "getLigne et getStation: ";
	try
	{
		cout << (gest.getLigne("10").getNumero() == "10");
	}
	catch (char const* msg)
	{
		cout << 0;
	}
	try
	{
		cout << (gest.getLigne("2").getNumero());
	}
	catch (char const* msg)
	{
		cout << (strcmp(msg, "Il n’existe pas de ligne ayant ce numéro") == 0);
	}
	try
	{
		cout << (gest.getStation(4955).getId() == 4955);
	}
	catch (char const* msg)
	{
		cout << 0;
	}
	try
	{
		cout << (gest.getStation(1002).getId());
	}
	catch (char const* msg)
	{
		cout << (strcmp(msg, "Il n’existe pas de station ayant cet identifiant") == 0);
	}
	cout << endl;
	// tests de trouver_voyages
	cout << "trouver_voyage: ";
	vector<Voyage*> vect1 = gest.trouver_voyages(1412, "7");
	cout << (vect1.size() == 262);
	cout << (vect1[4]->getLigne()->getNumero() == "7");
	cout << (vect1[245]->getLigne()->getNumero() == "7");
	cout << (vect1[4]->arretDeLaStation(1412).getStationId() == 1412);
	cout << (vect1[55]->arretDeLaStation(1412).getStationId() == 1412);
	vector<Voyage*> vect2 = gest.trouver_voyages(1412, "800");
	cout << (vect2.size() == 0);
	vector<Voyage*> vect3 = gest.trouver_voyages(1412, "907");
	cout << (vect3.size() == 10);
	vector<Voyage*> vect4 = gest.trouver_voyages(3371, "800");
	cout << (vect4.size() == 718);
	vector<Voyage*> vect5 = gest.trouver_voyages(3371, "7");
	cout << (vect5.size() == 0);
	cout << endl;
	// tests de get_bus_destinations
	cout << "get_bus_destinations: ";
	pair<string, string> paire1 = gest.get_bus_destinations(1412, "7");
	cout << (paire1.first == "Pointe-de-Sainte-Foy (Ouest)");
	cout << (paire1.second == "Place D'Youville / Vieux-Québec (Est)");
	pair<string, string> paire2 = gest.get_bus_destinations(1412, "800");
	cout << (paire2.first == "");
	cout << (paire2.second == "");
	pair<string, string> paire3 = gest.get_bus_destinations(1412, "907");
	cout << (paire3.first == "Place D'Youville (Est)");
	cout << (paire3.second == "Pointe-de-Sainte-Foy (Ouest)");
	pair<string, string> paire4 = gest.get_bus_destinations(3371, "800");
	cout << (paire4.first == "Beauport (Est)");
	cout << (paire4.second == "Pointe-de-Sainte-Foy (Ouest)");
	pair<string, string> paire5 = gest.get_bus_destinations(3371, "7");
	cout << (paire5.first == "");
	cout << (paire5.second == "");
	pair<string, string> paire6 = gest.get_bus_destinations(5882, "915");
	cout << (paire6.first == "Cap-Rouge (Ouest)");
	cout << (paire6.second == "");
	cout << endl;
	// Tests de trouver_stations_environnantes
	cout << "trouver_stations_environnantes: ";
	vector<pair<double, Station*>> stationsProche1 = gest.trouver_stations_environnantes(Coordonnees(46.788183, -71.273083), 0.12);
	cout << (stationsProche1.size() == 1);
	cout << (stationsProche1[0].first < 0.12);
	cout << (stationsProche1[0].second->getId() == 1412);
	vector<pair<double, Station*>> stationsProche2 = gest.trouver_stations_environnantes(Coordonnees(46.788183, -71.273083), 0.32);
	cout << (stationsProche2.size() == 4);
	cout << (stationsProche2[0].second->getId() == 1412);
	cout << (stationsProche2[1].second->getId() == 1473);
	cout << (stationsProche2[2].second->getId() == 2442);
	cout << (stationsProche2[3].second->getId() == 2437);
	cout << (stationsProche2[0].first < stationsProche2[1].first);
	cout << (stationsProche2[1].first < stationsProche2[2].first);
	cout << (stationsProche2[2].first < stationsProche2[3].first);
	cout << endl;
	// Tests de trouver_horaire
	cout << "trouver_horaire: ";
	Heure heure1 = Heure {0, 0, 0};
	vector<Heure> horaire1 = gest.trouver_horaire(Date {2016, 8, 16}, heure1, "7", 1412, "Place D'Youville / Vieux-Québec (Est)");
	cout << (horaire1.size() == 0);
	vector<Heure> horaire2 = gest.trouver_horaire(Date {2016, 8, 16}, heure1, "7", 1412, "Pointe-de-Sainte-Foy (Ouest)");
	cout << (horaire2.size() == 48);
	for (int i = 0; i < 48; i++)
	{
		if (horaire2[i] <= heure1)
			cout << 0;
	}
	Heure heure2 = Heure {20, 0, 0};
	vector<Heure> horaire3 = gest.trouver_horaire(Date {2016, 8, 16}, heure2, "7", 1412, "Pointe-de-Sainte-Foy (Ouest)");
	cout << (horaire3.size() == 42);
	for (unsigned int i = 0; i < horaire3.size(); i++)
	{
		if (horaire3[i] <= heure2)
			cout << 0;
	}
	Heure heure3 = Heure {23, 0, 0};
	vector<Heure> horaire4 = gest.trouver_horaire(Date {2016, 8, 16}, heure3, "7", 1412, "Pointe-de-Sainte-Foy (Ouest)");
	cout << (horaire4.size() == 23);
	for (unsigned int i = 0; i < horaire4.size(); i++)
	{
		if (horaire4[i] <= heure3)
			cout << 0;
	}
	try
	{
		cout << (gest.trouver_horaire(Date {2016, 12, 16}, heure3, "7", 1412, "Pointe-de-Sainte-Foy (Ouest)").size() == 0);
	}
	catch (char const* msg)
	{
		cout << 0;
	}
	cout << endl;
//	// Tests de initialiser_reseau
//	cout << "initialiser_reseau 1: ";
//	gest.initialiser_reseau(Date {2016, 12, 16}, heure2, heure3, Coordonnees {46.788274, -71.272794}, Coordonnees {46.788440, -71.270579}, 0.55, 0.55);
//	cout << (gest.m_reseau.nombreSommets() == 4606);
//	cout << (gest.m_reseau.nombreArcs() == 96614);
//	cout << (gest.m_reseau.sommetExiste(0));
//	cout << (gest.m_reseau.sommetExiste(1));
//	cout << (gest.m_reseau.sommetExiste(1412));
//	cout << (gest.m_reseau.sommetExiste(1420));
//	cout << (gest.m_reseau.sommetExiste(3001));
//	cout << (gest.m_reseau.arcExiste(0, 1));
//	cout << (!gest.m_reseau.arcExiste(1, 0));
//	cout << (gest.m_reseau.getCoutArc(0, 1) == 122);
//	cout << (gest.m_reseau.arcExiste(1412, 1413));
//	cout << (gest.m_reseau.getCoutArc(1412, 1413) == 334);
//	cout << endl;
//	cout << "initialiser_reseau 2: ";
//	gest.initialiser_reseau(Date {2016, 8, 16}, heure2, heure3, Coordonnees {46.788274, -71.272794}, Coordonnees {46.780440, -71.300579}, 0.55, 0.55);
//	cout << (gest.m_reseau.nombreSommets() == 4606);
//	cout << (gest.m_reseau.nombreArcs() == 96739);
//	cout << gest.m_reseau.sommetExiste(0);
//	cout << gest.m_reseau.sommetExiste(1);
//	cout << gest.m_reseau.sommetExiste(1412);
//	cout << gest.m_reseau.sommetExiste(1420);
//	cout << gest.m_reseau.sommetExiste(3001);
//	cout << (!gest.m_reseau.arcExiste(0, 1));
//	cout << (!gest.m_reseau.arcExiste(1, 0));
//	cout << (gest.m_reseau.arcExiste(1412, 1413));
//	cout << (gest.m_reseau.getCoutArc(1412, 1413) == 60);
//	cout << endl;
//	cout << "reseau_est_fortement_connexe: ";
//	bool connexe1 = gest.reseau_est_fortement_connexe(Date {2016, 12, 16}, heure2, true);
//	cout << !connexe1 << endl;
//	bool connexe2 = gest.reseau_est_fortement_connexe(Date {2016, 8, 16}, heure2, true);
//	cout << !connexe2 << endl;
//	bool connexe3 = gest.reseau_est_fortement_connexe(Date {2016, 10, 5}, heure2, true);
//	cout << !connexe3 << endl;
//	bool connexe4 = gest.reseau_est_fortement_connexe(Date {2016, 8, 16}, heure3, false);
//	cout << !connexe4 << endl;
//	cout << endl;
//	cout << "composantes_fortement_connexes: ";
//	vector<vector<unsigned int>> vectorConnexe1;
//	gest.composantes_fortement_connexes(Date {2016, 12, 16}, heure2, vectorConnexe1, true);
//	cout << vectorConnexe1.size() << endl;
//	vector<vector<unsigned int>> vectorConnexe2;
//	gest.composantes_fortement_connexes(Date {2016, 8, 16}, heure2, vectorConnexe2, true);
//	cout << vectorConnexe2.size() << endl;
//	vector<vector<unsigned int>> vectorConnexe3;
//	gest.composantes_fortement_connexes(Date {2016, 10, 5}, heure2, vectorConnexe3, true);
//	cout << vectorConnexe3.size() << endl;
//	vector<vector<unsigned int>> vectorConnexe4;
//	gest.composantes_fortement_connexes(Date {2016, 8, 16}, heure3, vectorConnexe4, false);
//	cout << vectorConnexe4.size() << endl;
	cout << endl;
	cout << "plus_court_chemin: ";
	Coordonnees depart1 = Coordonnees {46.778808, -71.270014};
	Coordonnees arrivee1 = Coordonnees {46.760074, -71.319867};
	Date dateCourtChemin1 = Date { 2016, 10, 5 };
	Heure heure4 = Heure { 12, 0, 0 };
	vector<unsigned int> courtChemin1 = gest.plus_court_chemin(dateCourtChemin1, heure4, depart1, arrivee1);
	cout << courtChemin1.size() << endl;
	for (unsigned int i = 0; i < courtChemin1.size(); i++)
	{
		Station s = gest.getStation(courtChemin1[i]);
		cout << s.getId() << ": " << s.getNom() << " (" << s.getDescription() << ")" << endl;
	}

	return 0;
}

//string repertoireDossierCourant = TrouverNomRepertoire(argv[0]) + "/";
//clock_t clkStart;
//clock_t clkEnd;
//double timePassed;
//vector<Ligne> vectLignes;
//vector<Station> vectStations;
//vector<Voyage> vectVoyages;
//unordered_map<string, vector<Arret>> mapVoyageArrets;
//vector<vector<string>> resultsAgency;
//vector<vector<string>> resultsCalendarDates;
//vector<vector<string>> resultsRoutes;
//vector<vector<string>> resultsShapes;
//vector<vector<string>> resultsStops;
//vector<vector<string>> resultsStopsTimes;
//vector<vector<string>> resultsTransfers;
//vector<vector<string>> resultsTrips;
//
//clkStart = clock();
//
//try
//{
//	//lireFichier(repertoireDossierCourant + agencyFile, resultsAgency, delimiter, true);
//	lireFichier(repertoireDossierCourant + calendarDatesFile, resultsCalendarDates, delimiter, true);
//	lireFichier(repertoireDossierCourant + routesFile, resultsRoutes, delimiter, true);
//	//lireFichier(repertoireDossierCourant + shapesFile, resultsShapes, delimiter, true);
//	lireFichier(repertoireDossierCourant + stopsFile, resultsStops, delimiter, true);
//	lireFichier(repertoireDossierCourant + stopTimesFile, resultsStopsTimes, delimiter, true);
//	//lireFichier(repertoireDossierCourant + transfersFile, resultsTransfers, delimiter, true);
//	lireFichier(repertoireDossierCourant + tripsFile, resultsTrips, delimiter, true);
//
//	for (unsigned int i = 0; i < resultsStopsTimes.size(); i++)	{
//		Arret arretTemp = Arret(resultsStopsTimes[i]);
//		if (mapVoyageArrets.find(arretTemp.getVoyageId()) != mapVoyageArrets.end()) {
//			mapVoyageArrets[arretTemp.getVoyageId()].push_back(arretTemp);
//		} else {
//			mapVoyageArrets.insert(make_pair(arretTemp.getVoyageId(), std::vector<Arret> {arretTemp}));
//		}
//	}
//
//	for (unsigned int i = 0; i < resultsRoutes.size(); i++)	{
//		vectLignes.push_back(Ligne(resultsRoutes[i]));
//	}
//
//	for (unsigned int i = 0; i < resultsTrips.size(); i++)	{
//		for (unsigned int j = 0; j < vectLignes.size(); j++)	{
//			if (std::stoul(resultsTrips[i][0]) == vectLignes[j].getId()){
//				vectVoyages.push_back(Voyage(resultsTrips[i], &vectLignes[j]));
//				vectLignes[j].addVoyage(&vectVoyages.back());
//				if (mapVoyageArrets.find(vectVoyages.back().getId()) != mapVoyageArrets.end()) {
//						vectVoyages.back().setArrets(mapVoyageArrets[vectVoyages.back().getId()]);
//				}
//				break;
//				}
//		}
//	}
//
//	for (unsigned int i = 0; i < resultsStops.size(); i++)	{
//		vectStations.push_back(Station(resultsStops[i]));
//	}
//
//	sort(vectVoyages.begin(), vectVoyages.end());
//	sort(vectLignes.begin(), vectLignes.end(), comparerLignes());
//	sort(vectStations.begin(), vectStations.end(), comparerStations());
//}
//catch (char const* msg)
//{
//	cout << msg << "\n";
//}
//
//
//clkEnd = clock();
//timePassed = (double)(clkEnd - clkStart) / CLOCKS_PER_SEC;
//
//ofstream fichierTexte;
//fichierTexte.open (repertoireDossierCourant + resultatFile);
//
//cout << "Chargement des données terminé en " << timePassed << " secondes" << endl;
//fichierTexte << "Chargement des données terminé en " << timePassed << " secondes" << endl;
//fichierTexte << "======================" << endl;
//fichierTexte << " LIGNES DE LA RTC" << endl;
//fichierTexte << " COMPTE = " <<  vectLignes.size() << endl;
//fichierTexte << "======================" << endl;
//for (unsigned int i = 0; i < vectLignes.size(); i++)	{
//	fichierTexte << vectLignes[i] << endl;
//}
//
//fichierTexte << "======================" << endl;
//fichierTexte << " STATIONS DE LA RTC" << endl;
//fichierTexte << " COMPTE = " <<  vectStations.size() << endl;
//fichierTexte << "======================" << endl;
//for (unsigned int i = 0; i < vectStations.size(); i++)	{
//	fichierTexte << vectStations[i] << endl;
//}
//
//Date* dateCourante = new Date { };
//Date* dateDuTrip;
//Heure* heureCourante = new Heure { };
//Heure* heureDansUneHeure = new Heure {heureCourante->add_secondes(3600)};
//
//fichierTexte << "======================" << endl;
//fichierTexte << " VOYAGES DE LA JOURNÉE DU " << *dateCourante << endl;
//fichierTexte << " " << *heureCourante << " - " << *heureDansUneHeure << endl;
//fichierTexte << " COMPTE = " <<  vectVoyages.size() << endl;
//fichierTexte << "======================" << endl;
//for (unsigned int i = 0; i < vectVoyages.size(); i++)	{
//	if (vectVoyages[i].getHeureDepart() > *heureCourante && vectVoyages[i].getHeureFin() < *heureDansUneHeure){
//		for (unsigned int j = 0; j < resultsCalendarDates.size(); j++) {
//			if (resultsCalendarDates[j][0] == vectVoyages[i].getServiceId()) {
//				dateDuTrip = new Date { stoi(resultsCalendarDates[j][1].substr(0, 4)), stoi(resultsCalendarDates[j][1].substr(4, 2)), stoi(resultsCalendarDates[j][1].substr(6, 2)) };
//				if (*dateDuTrip == *dateCourante)
//					fichierTexte << vectVoyages[i] << endl;
//			}
//		}
//	}
//}
//
//fichierTexte.close();
//delete dateCourante;
//delete heureCourante;
//delete heureDansUneHeure;
//delete dateDuTrip;
//
//cout << "Fin" << endl;
