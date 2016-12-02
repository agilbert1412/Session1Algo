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

    unsigned int stationDepart = 2009;
    unsigned int stationArrivee = 3473;

    vector<unsigned int> cheminDijsktra = rtc.plus_court_chemin_dijsktra(stationDepart, stationArrivee);
    vector<unsigned int> cheminBellman = rtc.plus_court_chemin_bellman(stationDepart, stationArrivee);
    vector<unsigned int> cheminAStar = rtc.plus_court_chemin_a_star(stationDepart, stationArrivee);
    vector<unsigned int> cheminDijsktraMonceau = rtc.plus_court_chemin_dijsktra_monceau(stationDepart, stationArrivee);

    cout << "Noeuds Dijsktra: " << cheminDijsktra.size() << endl;
    cout << "Noeuds Bellman-Ford: " << cheminBellman.size() << endl;
    cout << "Noeuds A*: " << cheminAStar.size() << endl;
    cout << "Noeuds Dijsktra avec Monceau: " << cheminDijsktraMonceau.size() << endl << endl;

    cout << "Arrets pour: " << endl;
    cout << "Dijsktra\tBellman_Ford\tA*\tDijsktraMonceau" << endl;
    for (unsigned int i = 0; i < cheminDijsktra.size(); i++) {
    	//cout << cheminDijsktra[i] << "\t\t" << cheminBellman[i] << "\t\t" << cheminAStar[i] << "\t" << cheminDijsktraMonceau[i] << endl;
    }

    cout << endl;

    //vector<unsigned int> cheminFloyd = rtc.plus_court_chemin_floyd(1412, 2822);

    int nombreDijsktra = 10;
    cout << "Éxécution de " << nombreDijsktra << " fois Dijsktra" << endl;
    double tempsDijsktraMicroSec = rtc.tester_n_paires_dijsktra(nombreDijsktra);
    double tempsDijsktraMilliSec = tempsDijsktraMicroSec / 1000;
    double tempsDijsktraSec = tempsDijsktraMilliSec / 1000;

    cout << "Temps pour éxécuter " << nombreDijsktra << " fois Dijsktra: " << (nombreDijsktra * tempsDijsktraSec) << " secondes." << endl;
    cout << "Temps moyen de Dijsktra: " << tempsDijsktraSec << " secondes." << endl << endl;



    int nombreBellman = 10;
    cout << "Éxécution de " << nombreBellman << " fois Bellman" << endl;
    double tempsBellmanMicroSec = rtc.tester_n_paires_bellman(nombreBellman);
	double tempsBellmanMilliSec = tempsBellmanMicroSec / 1000;
	double tempsBellmanSec = tempsBellmanMilliSec / 1000;

	cout << "Temps pour éxécuter " << nombreBellman << " fois Bellman: " << (nombreBellman * tempsBellmanSec) << " secondes." << endl;
    cout << "Temps moyen de Bellman " << tempsBellmanSec << " secondes." << endl << endl;

    int nombreAStar = 10;
	cout << "Éxécution de " << nombreAStar << " fois A*" << endl;
	double tempsAStarMicroSec = rtc.tester_n_paires_a_star(nombreAStar);
	double tempsAStarMilliSec = tempsAStarMicroSec / 1000;
	double tempsAStarSec = tempsAStarMilliSec / 1000;

	cout << "Temps pour éxécuter " << nombreAStar << " fois A*: " << (nombreAStar * tempsAStarSec) << " secondes." << endl;
	cout << "Temps moyen de A* " << tempsAStarSec << " secondes." << endl << endl;

	int nombreDijsktraMonceau = 10;
	cout << "Éxécution de " << nombreDijsktraMonceau << " fois A*" << endl;
	double tempsDijsktraMonceauMicroSec = rtc.tester_n_paires_dijsktra_monceau(nombreDijsktraMonceau);
	double tempsDijsktraMonceauMilliSec = tempsDijsktraMonceauMicroSec / 1000;
	double tempsDijsktraMonceauSec = tempsDijsktraMonceauMilliSec / 1000;

	cout << "Temps pour éxécuter " << nombreDijsktraMonceau << " fois A*: " << (nombreDijsktraMonceau * tempsDijsktraMonceauSec) << " secondes." << endl;
	cout << "Temps moyen de A* " << tempsDijsktraMonceauSec << " secondes." << endl << endl;

    int nombreFloyd = 1;

    cout << "Floyd-Warshall ne sera pas éxécuté car il prend des dizaines d'heures à terminer une seule fois." << endl;
    //cout << "Éxécution de " << nombreFloyd << " fois Floyd-Warshall" << endl;

	//double tempsFloydMicroSec = rtc.tester_n_paires_floyd(nombreFloyd);
	//double tempsFloydMilliSec = tempsFloydMicroSec / 1000;
	//double tempsFloydSec = tempsFloydMilliSec / 1000;

	//cout << "Temps pour éxécuter " << nombreFloyd << " fois Floyd: " << (nombreFloyd * tempsFloydSec) << " secondes." << endl;
	//cout << "Temps moyen de Floyd " << tempsFloydSec << " secondes." << endl << endl;

    int nombreBellmanAcyclique = 1;

	cout << "Bellman-Ford pour graphe acyclique ne sera pas éxécuté car notre graphe contient plusieurs cycles" << endl;
	//cout << "Éxécution de " << nombreBellmanAcyclique << " fois Floyd-Warshall" << endl;

	//double tempsBellmanAcycliqueMicroSec = rtc.tester_n_paires_bellman_acyclique(nombreBellmanAcyclique);
	//double tempsBellmanAcycliqueMilliSec = tempsBellmanAcycliqueMicroSec / 1000;
	//double tempsBellmanAcycliqueSec = tempsBellmanAcycliqueMilliSec / 1000;

	//cout << "Temps pour éxécuter " << nombreBellmanAcyclique << " fois Floyd: " << (nombreBellmanAcyclique * tempsBellmanAcycliqueSec) << " secondes." << endl;
	//cout << "Temps moyen de Floyd " << tempsBellmanAcycliqueSec << " secondes." << endl << endl;

    return 0;
}
