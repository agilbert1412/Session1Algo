#include <iostream>
#include "coordonnees.h"
#include "reseau.h"
#include <vector>
#include "investigation.h"

using namespace std;

string TrouverNomRepertoire(const string& cheminFichier)
{
     size_t position = cheminFichier.find_last_of("\\/");
     if (string::npos == position)
         return "";
     return cheminFichier.substr(0, position);
}

int main(int argc, char *argv[]) {

	string repertoireDossierCourant = TrouverNomRepertoire(argv[0]) + "/RTC";

    GestionnaireInvestigation rtc(repertoireDossierCourant);

    int nombreDijsktra = 10;
    double tempsDijsktraMicroSec = rtc.tester_n_paires_dijsktra(nombreDijsktra);
    double tempsDijsktraMilliSec = tempsDijsktraMicroSec / 1000;
    double tempsDijsktraSec = tempsDijsktraMilliSec / 1000;

    cout << "Temps pour éxécuter " << nombreDijsktra << " fois Dijsktra: " << (nombreDijsktra * tempsDijsktraSec) << " secondes." << endl;
    cout << "Temps moyen de Dijsktra: " << tempsDijsktraSec << " secondes." << endl;

    int nombreBellman = 10;
    double tempsBellmanMicroSec = rtc.tester_n_paires_bellman(nombreBellman);
	double tempsBellmanMilliSec = tempsBellmanMicroSec / 1000;
	double tempsBellmanSec = tempsBellmanMilliSec / 1000;

	cout << "Temps pour éxécuter " << nombreBellman << " fois Bellman: " << (nombreBellman * tempsBellmanSec) << " secondes." << endl;
    cout << "Temps moyen de Bellman " << tempsBellmanSec << " secondes." << endl;

    int nombreFloyd = 10;

    cout << "Floyd-Warshall ne sera pas éxécuté car il prend des dizaines d'heures à terminer une seule fois." << endl;
    //cout << "Éxécution de " << nombreFloyd << "fois Floyd-Warshall" << endl;

	//double tempsFloydMicroSec = rtc.tester_n_paires_floyd(nombreFloyd);
	//double tempsFloydMilliSec = tempsFloydMicroSec / 1000;
	//double tempsFloydSec = tempsFloydMilliSec / 1000;

	//cout << "Temps pour éxécuter " << nombreFloyd << " fois Floyd: " << (nombreFloyd * tempsFloydSec) << " secondes." << endl;
	//cout << "Temps moyen de Floyd " << tempsFloydSec << " secondes." << endl;

    return 0;
}
