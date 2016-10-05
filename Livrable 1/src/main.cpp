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

using namespace std;

const string agencyFile = "/agency.txt";
const string calendarDatesFile = "/calendar_dates.txt";
const string routesFile = "/routes.txt";
const string shapesFile = "/shapes.txt";
const string stopsFile = "/stops.txt";
const string stopTimesFile = "/stop_times.txt";
const string transfersFile = "/transfers.txt";
const string tripsFile = "/trips.txt";
const string resultatFile = "/Resultat.txt";
const char delimiter = ',';

string TrouverNomRepertoire(const string& cheminFichier)
{
     size_t position = cheminFichier.find_last_of("\\/");
     if (string::npos == position)
         return "";
     return cheminFichier.substr(0, position);
}

int main(int argc, char *argv[]) {

	string repertoireDossierRTC = TrouverNomRepertoire(argv[0]) + "/RTC/";
	clock_t clkStart;
	clock_t clkEnd;
	clock_t clk1;
	clock_t clk2;
	clock_t clk3;
	clock_t clk4;
	clock_t clk5;
	clock_t clk6;
	clock_t clk7;
	clock_t clk8;
	clock_t clk9;
	clock_t clk10;
	clock_t clk11;
	clock_t clk12;
	clock_t clk13;
	clock_t clk14;
	clock_t clk15;
	clock_t clk16;
	clock_t clk17;
	clock_t clk18;
	clock_t clk19;
	clock_t clk20;
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
    	clk1 = clock();

    	lireFichier(repertoireDossierRTC + agencyFile, resultsAgency, delimiter, true);

    	clk2 = clock();
    	timePassed = (double)(clk2 - clk1) / CLOCKS_PER_SEC;
		cout << "Agency lu en " << timePassed << " secondes (" << resultsAgency.size() << " lignes)" << endl;

    	lireFichier(repertoireDossierRTC + calendarDatesFile, resultsCalendarDates, delimiter, true);

    	clk3 = clock();
    	timePassed = (double)(clk3 - clk2) / CLOCKS_PER_SEC;
		cout << "CalendarDates lu en " << timePassed << " secondes (" << resultsCalendarDates.size() << " lignes)" << endl;

    	lireFichier(repertoireDossierRTC + routesFile, resultsRoutes, delimiter, true);

    	clk4 = clock();
    	timePassed = (double)(clk4 - clk3) / CLOCKS_PER_SEC;
		cout << "Routes lu en " << timePassed << " secondes (" << resultsRoutes.size() << " lignes)" << endl;

    	lireFichier(repertoireDossierRTC + shapesFile, resultsShapes, delimiter, true);

    	clk5 = clock();
    	timePassed = (double)(clk5 - clk4) / CLOCKS_PER_SEC;
		cout << "Shapes lu en " << timePassed << " secondes (" << resultsShapes.size() << " lignes)" << endl;

    	lireFichier(repertoireDossierRTC + stopsFile, resultsStops, delimiter, true);

    	clk6 = clock();
    	timePassed = (double)(clk6 - clk5) / CLOCKS_PER_SEC;
		cout << "Stops lu en " << timePassed << " secondes (" << resultsStops.size() << " lignes)" << endl;

    	lireFichier(repertoireDossierRTC + stopTimesFile, resultsStopsTimes, delimiter, true);

    	clk7 = clock();
    	timePassed = (double)(clk7 - clk6) / CLOCKS_PER_SEC;
		cout << "StopsTimes lu en " << timePassed << " secondes (" << resultsStopsTimes.size() << " lignes)" << endl;

    	lireFichier(repertoireDossierRTC + transfersFile, resultsTransfers, delimiter, true);

    	clk8 = clock();
    	timePassed = (double)(clk8 - clk7) / CLOCKS_PER_SEC;
		cout << "Transfers lu en " << timePassed << " secondes (" << resultsTransfers.size() << " lignes)" << endl;

    	lireFichier(repertoireDossierRTC + tripsFile, resultsTrips, delimiter, true);

    	clk9 = clock();
    	timePassed = (double)(clk9 - clk8) / CLOCKS_PER_SEC;
		cout << "Trips lu en " << timePassed << " secondes (" << resultsTrips.size() << " lignes)" << endl;

		for (unsigned int i = 0; i < resultsStopsTimes.size(); i++)	{
		    Arret arretTemp = Arret(resultsStopsTimes[i]);
		    if (mapVoyageArrets.find(arretTemp.getVoyageId()) != mapVoyageArrets.end()) {
		    	mapVoyageArrets[arretTemp.getVoyageId()].push_back(arretTemp);
		    } else {
		    	mapVoyageArrets.insert(make_pair(arretTemp.getVoyageId(), std::vector<Arret> {arretTemp}));
		    }
		}

    	clk10 = clock();
		timePassed = (double)(clk10 - clk9) / CLOCKS_PER_SEC;
		cout << "VectArrets rempli en " << timePassed << " secondes (" << resultsStopsTimes.size() << " arrets)" << endl;

    	clk11 = clock();
		timePassed = (double)(clk11 - clk10) / CLOCKS_PER_SEC;
		cout << "VectArrets trié en " << timePassed << " secondes (" << resultsStopsTimes.size() << " arrets)" << endl;

    	for (unsigned int i = 0; i < resultsRoutes.size(); i++)	{
    		vectLignes.push_back(Ligne(resultsRoutes[i]));
    	}

    	clk12 = clock();
		timePassed = (double)(clk12 - clk11) / CLOCKS_PER_SEC;
		cout << "vectLignes rempli en " << timePassed << " secondes (" << resultsRoutes.size() << " arrets)" << endl;

    	for (unsigned int i = 0; i < resultsTrips.size() * 0 + 1; i++)	{
    		clk13 = clock();
    		for (unsigned int j = 0; j < vectLignes.size(); j++)	{
    			if (std::stoul(resultsTrips[i][0]) == vectLignes[j].getId()){
    				clk17 = clock();
    				vectVoyages.push_back(Voyage(resultsTrips[i], &vectLignes[j]));
    				clk18 = clock();
    				vectLignes[j].addVoyage(&vectVoyages.back());
    				clk19 = clock();
    				if (mapVoyageArrets.find(vectVoyages.back().getId()) != mapVoyageArrets.end()) {
    				    	vectVoyages.back().setArrets(mapVoyageArrets[vectVoyages.back().getId()]);
    				}
    				clk20 = clock();
    				break;
    				}
    		}
    		clk14 = clock();
    		timePassed = (double)(clk14 - clk13) / CLOCKS_PER_SEC;
    		cout << "itération " << i << " sur " << resultsTrips.size() << " complétée en " << timePassed << " secondes (" << vectLignes.size() << " sous-itérations)" << endl;
    		timePassed = (double)(clk18 - clk17) / CLOCKS_PER_SEC;
    		cout << "Temps commande 1: " << timePassed << endl;
    		timePassed = (double)(clk19 - clk18) / CLOCKS_PER_SEC;
    		cout << "Temps commande 2: " << timePassed << endl;
    		timePassed = (double)(clk20 - clk19) / CLOCKS_PER_SEC;
    		cout << "Temps commande 3: " << timePassed << endl;
    	}

    	clk15 = clock();
		timePassed = (double)(clk15 - clk14) / CLOCKS_PER_SEC;
		cout << "bigStuff rempli en " << timePassed << " secondes (" << (resultsTrips.size() * vectLignes.size()) << " iterations)" << endl;

    	for (unsigned int i = 0; i < resultsStops.size(); i++)	{
			vectStations.push_back(Station(resultsStops[i]));
		}

    	clk16 = clock();
    	timePassed = (double)(clk16 - clk15) / CLOCKS_PER_SEC;
		cout << "vectStations rempli en " << timePassed << " resultsStops" << endl;
    }
	catch (char const* msg)
	{
	    cout << msg << "\n";
	}


	clkEnd = clock();
	timePassed = (double)(clkEnd - clkStart) / CLOCKS_PER_SEC;

	ofstream fichierTexte;
	fichierTexte.open (repertoireDossierRTC + resultatFile);

	fichierTexte << "Chargement des données terminé en " << timePassed << " secondes" << endl;
	fichierTexte << "======================" << endl;
	fichierTexte << "LIGNES DE LA RTC" << endl;
	fichierTexte << "COMPTE = " <<  vectLignes.size() << endl;
	fichierTexte << "======================" << endl;
	for (unsigned int i = 0; i < vectLignes.size(); i++)	{
		fichierTexte << vectLignes[i] << endl;
	}

	fichierTexte << "======================" << endl;
	fichierTexte << "STATIONS DE LA RTC" << endl;
	fichierTexte << "COMPTE = " <<  vectStations.size() << endl;
	fichierTexte << "======================" << endl;
	for (unsigned int i = 0; i < vectStations.size(); i++)	{
		fichierTexte << vectStations[i] << endl;
	}

	time_t t = time(0);
	struct tm * now = localtime( & t );

	fichierTexte << "----------------------" << endl;
	fichierTexte << "VOYAGES DE LA JOURNÉE DU " << now->tm_year + 1900 << '-' << now->tm_mon + 1
			<< '-' << now->tm_mday << endl;
	fichierTexte << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << " - "
			<< now->tm_hour + 1 << ':' << now->tm_min << ':' << now->tm_sec << endl;
	fichierTexte << "COMPTE = " <<  vectVoyages.size() << endl;
	fichierTexte << "----------------------" << endl;
	for (unsigned int i = 0; i < vectVoyages.size(); i++)	{
		fichierTexte << vectVoyages[i] << endl;
	}

	cout << vectVoyages.size() << endl;
	cout << vectStations.size() << endl;

	fichierTexte.close();

	return 0;
}
