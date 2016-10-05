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
#include <algorithm>

using namespace std;

const string directoryFilesPath = "/home/etudiant/Bureau/RTC";
const string agencyFile = "/agency.txt";
const string calendarDatesFile = "/calendar_dates.txt";
const string routesFile = "/routes.txt";
const string shapesFile = "/shapes.txt";
const string stopsFile = "/stops.txt";
const string stopTimesFile = "/stop_times.txt";
const string transfersFile = "/transfers.txt";
const string tripsFile = "/trips.txt";
const char delimiter = ',';

int main() {

	clock_t clkStart;
	clock_t clkEnd;
	double timePassed;
	vector<Ligne> vectLignes;
	vector<Station> vectStations;
	vector<Voyage> vectVoyages;
	vector<Arret> vectArrets;
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
    	lireFichier(directoryFilesPath + agencyFile, resultsAgency, delimiter, true);


    	lireFichier(directoryFilesPath + calendarDatesFile, resultsCalendarDates, delimiter, true);


    	lireFichier(directoryFilesPath + routesFile, resultsRoutes, delimiter, true);


    	lireFichier(directoryFilesPath + shapesFile, resultsShapes, delimiter, true);


    	lireFichier(directoryFilesPath + stopsFile, resultsStops, delimiter, true);


    	lireFichier(directoryFilesPath + stopTimesFile, resultsStopsTimes, delimiter, true);


    	lireFichier(directoryFilesPath + transfersFile, resultsTransfers, delimiter, true);


    	lireFichier(directoryFilesPath + tripsFile, resultsTrips, delimiter, true);

    	for (unsigned int i = 0; i < resultsStopsTimes.size(); i++)	{
    		vectArrets.push_back(Arret(resultsStopsTimes[i]));
    	}
    	sort(vectArrets.begin(), vectArrets.end());

    	for (unsigned int i = 0; i < resultsRoutes.size(); i++)	{
    		vectLignes.push_back(Ligne(resultsRoutes[i]));
    	}

    	for (unsigned int i = 0; i < resultsTrips.size(); i++)	{
    		for (unsigned int j = 0; j < vectLignes.size(); j++)	{
    			if (std::stoul(resultsTrips[i][0]) == vectLignes[j].getId()){
    				vectVoyages.push_back(Voyage(resultsTrips[i], &vectLignes[j]));
    				vectLignes[j].addVoyage(&vectVoyages.back());
    				vectVoyages.back().setArrets(vectArrets);
    				break;
    				}
    		}
    	}

    	for (unsigned int i = 0; i < resultsStops.size(); i++)	{
    			vectStations.push_back(Station(resultsStops[i]));
    		}
    }
	catch (char const* msg)
	{
	    cout << msg << "\n";
	}


	clkEnd = clock();
	timePassed = (double)(clkEnd - clkStart) / CLOCKS_PER_SEC;

	cout << "Chargement des données terminé en " << time << " secondes\n";
	//cout << "----------------------\n";
	//cout << "LIGNES DE LA RTC\n";
	//cout << "COMPTE = " <<  vectLignes.size() << "\n";
	//cout << "----------------------\n";
	//for (unsigned int i = 0; i < vectLignes.size(); i++)	{
	//	cout << vectLignes[i];
	//}

	//cout << "----------------------\n";
	//cout << "STATIONS DE LA RTC\n";
	//cout << "COMPTE = " <<  vectStations.size() << "\n";
	//cout << "----------------------\n";
	//for (unsigned int i = 0; i < vectStations.size(); i++)	{
	//	cout << vectStations[i];
	//}

	time_t t = time(0);
	struct tm * now = localtime( & t );

	cout << "----------------------\n";
	cout << "VOYAGES DE LA JOURNÉE DU " << now->tm_year + 1900 << '-' << now->tm_mon + 1
			<< '-' << now->tm_mday << "\n";
	cout << now->tm_hour<< ':' << now->tm_min << ':' << now->tm_sec << ' - '
			<< now->tm_hour + 1<< ':' << now->tm_min << ':' << now->tm_sec << "\n";
	cout << "COMPTE = " <<  vectVoyages.size() << "\n";
	cout << "----------------------\n";
	for (unsigned int i = 0; i < vectVoyages.size(); i++)	{
		cout << vectVoyages[i];
	}

	cout << vectArrets.size() << "\n";
	cout << vectVoyages.size() << "\n";
	cout << vectStations.size() << "\n";
	return 0;
}
