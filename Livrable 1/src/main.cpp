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
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

const string agencyFile = "RTC/agency.txt";
const string calendarDatesFile = "RTC/calendar_dates.txt";
const string routesFile = "RTC/routes.txt";
const string shapesFile = "RTC/shapes.txt";
const string stopsFile = "RTC/stops.txt";
const string stopTimesFile = "RTC/stop_times.txt";
const string transfersFile = "RTC/transfers.txt";
const string tripsFile = "RTC/trips.txt";
const string resultatFile = "Resultat.txt";
const char delimiter { ',' };

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
	clock_t clkStart;
	clock_t clkEnd;
	double timePassed;
	vector<Ligne> vectLignes;
	vector<Station> vectStations;
	vector<Voyage> vectVoyages;
	std::unordered_map<std::string, std::vector<Arret>> mapVoyageArrets;
	vector<vector<string>> resultsAgency;
	vector<vector<string>> resultsCalendarDates;
	vector<vector<string>> resultsRoutes;
	vector<vector<string>> resultsShapes;
	vector<vector<string>> resultsStops;
	vector<vector<string>> resultsStopsTimes;
	vector<vector<string>> resultsTransfers;
	vector<vector<string>> resultsTrips;

	clkStart = clock();

    try
    {
    	lireFichier(repertoireDossierCourant + agencyFile, resultsAgency, delimiter, true);
    	lireFichier(repertoireDossierCourant + calendarDatesFile, resultsCalendarDates, delimiter, true);
    	lireFichier(repertoireDossierCourant + routesFile, resultsRoutes, delimiter, true);
    	lireFichier(repertoireDossierCourant + shapesFile, resultsShapes, delimiter, true);
    	lireFichier(repertoireDossierCourant + stopsFile, resultsStops, delimiter, true);
    	lireFichier(repertoireDossierCourant + stopTimesFile, resultsStopsTimes, delimiter, true);
    	lireFichier(repertoireDossierCourant + transfersFile, resultsTransfers, delimiter, true);
    	lireFichier(repertoireDossierCourant + tripsFile, resultsTrips, delimiter, true);

		for (unsigned int i = 0; i < resultsStopsTimes.size(); i++)	{
		    Arret arretTemp = Arret(resultsStopsTimes[i]);
		    if (mapVoyageArrets.find(arretTemp.getVoyageId()) != mapVoyageArrets.end()) {
		    	mapVoyageArrets[arretTemp.getVoyageId()].push_back(arretTemp);
		    } else {
		    	mapVoyageArrets.insert(make_pair(arretTemp.getVoyageId(), std::vector<Arret> {arretTemp}));
		    }
		}

    	for (unsigned int i = 0; i < resultsRoutes.size(); i++)	{
    		vectLignes.push_back(Ligne(resultsRoutes[i]));
    	}

    	for (unsigned int i = 0; i < resultsTrips.size(); i++)	{
    		for (unsigned int j = 0; j < vectLignes.size(); j++)	{
    			if (std::stoul(resultsTrips[i][0]) == vectLignes[j].getId()){
    				vectVoyages.push_back(Voyage(resultsTrips[i], &vectLignes[j]));
    				vectLignes[j].addVoyage(&vectVoyages.back());
    				if (mapVoyageArrets.find(vectVoyages.back().getId()) != mapVoyageArrets.end()) {
    				    	vectVoyages.back().setArrets(mapVoyageArrets[vectVoyages.back().getId()]);
    				}
    				break;
    				}
    		}
    	}

    	for (unsigned int i = 0; i < resultsStops.size(); i++)	{
			vectStations.push_back(Station(resultsStops[i]));
		}

    	sort(vectVoyages.begin(), vectVoyages.end());
    	sort(vectLignes.begin(), vectLignes.end(), comparerLignes());
    	sort(vectStations.begin(), vectStations.end(), comparerStations());
    }
	catch (char const* msg)
	{
	    cout << msg << "\n";
	}


	clkEnd = clock();
	timePassed = (double)(clkEnd - clkStart) / CLOCKS_PER_SEC;

	ofstream fichierTexte;
	fichierTexte.open (repertoireDossierCourant + resultatFile);

	cout << "Chargement des données terminé en " << timePassed << " secondes" << endl;
	fichierTexte << "Chargement des données terminé en " << timePassed << " secondes" << endl;
	fichierTexte << "======================" << endl;
	fichierTexte << " LIGNES DE LA RTC" << endl;
	fichierTexte << " COMPTE = " <<  vectLignes.size() << endl;
	fichierTexte << "======================" << endl;
	for (unsigned int i = 0; i < vectLignes.size(); i++)	{
		fichierTexte << vectLignes[i] << endl;
	}

	fichierTexte << "======================" << endl;
	fichierTexte << " STATIONS DE LA RTC" << endl;
	fichierTexte << " COMPTE = " <<  vectStations.size() << endl;
	fichierTexte << "======================" << endl;
	for (unsigned int i = 0; i < vectStations.size(); i++)	{
		fichierTexte << vectStations[i] << endl;
	}

	Date* dateCourante = new Date { };
	Date* dateDuTrip;
	Heure* heureCourante = new Heure { };
	Heure* heureDansUneHeure = new Heure {heureCourante->add_secondes(3600)};

	fichierTexte << "======================" << endl;
	fichierTexte << " VOYAGES DE LA JOURNÉE DU " << *dateCourante << endl;
	fichierTexte << " " << *heureCourante << " - " << *heureDansUneHeure << endl;
	fichierTexte << " COMPTE = " <<  vectVoyages.size() << endl;
	fichierTexte << "======================" << endl;
	for (unsigned int i = 0; i < vectVoyages.size(); i++)	{
		if (vectVoyages[i].getHeureDepart() > *heureCourante && vectVoyages[i].getHeureFin() < *heureDansUneHeure){
			for (unsigned int j = 0; j < resultsCalendarDates.size(); j++) {
				if (resultsCalendarDates[j][0] == vectVoyages[i].getServiceId()) {
					dateDuTrip = new Date { stoi(resultsCalendarDates[j][1].substr(0, 4)), stoi(resultsCalendarDates[j][1].substr(4, 2)), stoi(resultsCalendarDates[j][1].substr(6, 2)) };
					if (*dateDuTrip == *dateCourante)
						fichierTexte << vectVoyages[i] << endl;
				}
			}
		}
	}

	fichierTexte.close();
	delete dateCourante;
	delete heureCourante;
	delete heureDansUneHeure;
	delete dateDuTrip;

	cout << "Fin" << endl;

	return 0;
}
                                                              
