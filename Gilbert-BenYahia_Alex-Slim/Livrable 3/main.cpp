#include <iostream>
#include "coordonnees.h"
#include <stdio.h>
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
	vector<unsigned int> cheminPlusCourt = rtc.plus_court_chemin_meilleur(stationDepart, stationArrivee);

	cout << "Noeuds Dijsktra: " << cheminDijsktra.size() << endl;
	cout << "Noeuds Bellman-Ford: " << cheminBellman.size() << endl;
	cout << "Noeuds A*: " << cheminAStar.size() << endl;
	cout << "Noeuds Dijsktra avec Monceau: " << cheminDijsktraMonceau.size() << endl;
	cout << "Noeuds Meilleur: " << cheminPlusCourt.size() << endl << endl;

	cout << "Arrets pour: " << endl;
	cout << "Dijsktra\tBellman_Ford\tA*\tDijsktraMonceau\tMeilleur" << endl;
	for (unsigned int i = 0; i < cheminDijsktra.size(); i++) {
		cout << cheminDijsktra[i] << "\t\t" << cheminBellman[i] << "\t\t" << cheminAStar[i] << "\t" << cheminDijsktraMonceau[i] << "\t\t" << cheminPlusCourt[i] << endl;
	}

	cout << endl;

//	FILE *file;
//	file =fopen("résultat.txt", "w");
//	string noIteration;
//	int nombreDijsktra = 1000;
//	int nombreBellman = 1000;
//	int nombreAStar = 1000;
//	int nombreDijsktraMonceau = 1000;
//	string nombre = "1000";
//	double tempsDijsktraMicroSec;
//	double tempsDijsktraMilliSec;
//	double tempsDijsktraSec;
//	double tempsBellmanMicroSec;
//	double tempsBellmanMilliSec;
//	double tempsBellmanSec;
//	double tempsAStarMicroSec;
//	double tempsAStarMilliSec;
//	double tempsAStarSec;
//	double tempsDijsktraMonceauMicroSec;
//	double tempsDijsktraMonceauMilliSec;
//	double tempsDijsktraMonceauSec;
//
//	if (!file) {
//		cout << "Le fichier \"résultat.txt\" est introuvable.";
//		return 0;
//	}
//
//	for(int i = 0; i <  20; i++){
//		noIteration = std::to_string(i+1);
//		fprintf(file, ("Résultat du test numéro " + noIteration + " :").c_str());
//		cout << "Résultat du test numéro " << noIteration << " :" << endl << endl;
//		fprintf(file, "\n\n");
//
//		fprintf(file, ("Éxécution de " + nombre + " fois Dijsktra" + "\n").c_str());
//		cout << "Éxécution de " << nombre << " fois Dijsktra" << endl;
//		tempsDijsktraMicroSec = rtc.tester_n_paires_dijsktra(nombreDijsktra);
//		tempsDijsktraMilliSec = tempsDijsktraMicroSec / 1000;
//		tempsDijsktraSec = tempsDijsktraMilliSec / 1000;
//
//		fprintf(file, ("Temps pour éxécuter " + nombre + " fois Dijsktra: " + std::to_string(nombreDijsktra * tempsDijsktraSec) + " secondes." + "\n").c_str());
//		cout << "Temps pour éxécuter " << nombre << " fois Dijsktra: " << to_string(nombreDijsktra * tempsDijsktraSec) << " secondes." << endl;
//		fprintf(file, ("Temps moyen de Dijsktra: " + std::to_string(tempsDijsktraSec) + " secondes." + "\n\n").c_str());
//		cout << "Temps moyen de Dijsktra: " << tempsDijsktraSec << " secondes." << endl << endl;
//
//		fprintf(file, ("Éxécution de " + nombre + " fois Bellman" + "\n").c_str());
//		cout << "Éxécution de " << nombre << " fois Bellman" << endl;
//		tempsBellmanMicroSec = rtc.tester_n_paires_bellman(nombreBellman);
//		tempsBellmanMilliSec = tempsBellmanMicroSec / 1000;
//		tempsBellmanSec = tempsBellmanMilliSec / 1000;
//
//		fprintf(file, ("Temps pour éxécuter " + nombre + " fois Bellman: " + std::to_string(nombreBellman * tempsBellmanSec) + " secondes." + "\n").c_str());
//		cout << "Temps pour éxécuter " << nombre << " fois Bellman: " << to_string(nombreBellman * tempsBellmanSec) << " secondes." << endl;
//		fprintf(file, ("Temps moyen de Bellman: " + std::to_string(tempsBellmanSec) + " secondes." + "\n\n").c_str());
//		cout << "Temps moyen de Dijsktra: " << tempsBellmanSec << " secondes." << endl << endl;
//
//		fprintf(file, ("Éxécution de " + nombre + " fois A*" + "\n").c_str());
//		cout << "Éxécution de " << nombre << " fois A*" << endl;
//		tempsAStarMicroSec = rtc.tester_n_paires_a_star(nombreAStar);
//		tempsAStarMilliSec = tempsAStarMicroSec / 1000;
//		tempsAStarSec = tempsAStarMilliSec / 1000;
//
//		fprintf(file, ("Temps pour éxécuter " + nombre + " fois A*: " + std::to_string(nombreAStar * tempsAStarSec) + " secondes." + "\n").c_str());
//		cout << "Temps pour éxécuter " << nombre << " fois A*: " << to_string(nombreAStar * tempsAStarSec) << " secondes." << endl;
//		fprintf(file, ("Temps moyen de A*: " + std::to_string(tempsAStarSec) + " secondes." + "\n\n").c_str());
//		cout << "Temps moyen de A*: " << tempsAStarSec << " secondes." << endl << endl;
//
//		fprintf(file, ("Éxécution de " + nombre + " fois Dijkstra avec un monceau" + "\n").c_str());
//		cout << "Éxécution de " << nombre << " fois Dijkstra avec un monceau" << endl;
//		tempsDijsktraMonceauMicroSec = rtc.tester_n_paires_dijsktra_monceau(nombreDijsktraMonceau);
//		tempsDijsktraMonceauMilliSec = tempsDijsktraMonceauMicroSec / 1000;
//		tempsDijsktraMonceauSec = tempsDijsktraMonceauMilliSec / 1000;
//
//		fprintf(file, ("Temps pour éxécuter " + nombre + " fois Dijkstra avec un monceau: " + std::to_string(nombreDijsktraMonceau * tempsDijsktraMonceauSec) + " secondes." + "\n").c_str());
//		cout << "Temps pour éxécuter " << nombre << " fois Dijkstra avec un monceau: " << to_string(nombreDijsktraMonceau * tempsDijsktraMonceauSec) << " secondes." << endl;
//		fprintf(file, ("Temps moyen de Dijkstra avec un monceau: " + std::to_string(tempsDijsktraMonceauSec) + " secondes." + "\n\n").c_str());
//		cout << "Temps moyen de Dijkstra avec un monceau: " << tempsDijsktraMonceauSec << " secondes." << endl << endl;
//
//		fprintf(file, "\n\n");
//		cout << endl << endl;
//	}
//
//	fclose(file);

//	return  0;


    //vector<unsigned int> cheminFloyd = rtc.plus_court_chemin_floyd(1412, 2822);

    int nombreDijsktra = 1000;
    cout << "Éxécution de " << nombreDijsktra << " fois Dijsktra" << endl;
    double tempsDijsktraMicroSec = rtc.tester_n_paires_dijsktra(nombreDijsktra);
    double tempsDijsktraMilliSec = tempsDijsktraMicroSec / 1000;
    double tempsDijsktraSec = tempsDijsktraMilliSec / 1000;

    cout << "Temps pour éxécuter " << nombreDijsktra << " fois Dijsktra: " << (nombreDijsktra * tempsDijsktraSec) << " secondes." << endl;
    cout << "Temps moyen de Dijsktra: " << tempsDijsktraSec << " secondes." << endl << endl;



    int nombreBellman = 1000;
    cout << "Éxécution de " << nombreBellman << " fois Bellman" << endl;
    double tempsBellmanMicroSec = rtc.tester_n_paires_bellman(nombreBellman);
	double tempsBellmanMilliSec = tempsBellmanMicroSec / 1000;
	double tempsBellmanSec = tempsBellmanMilliSec / 1000;

	cout << "Temps pour éxécuter " << nombreBellman << " fois Bellman: " << (nombreBellman * tempsBellmanSec) << " secondes." << endl;
    cout << "Temps moyen de Bellman " << tempsBellmanSec << " secondes." << endl << endl;

    int nombreAStar = 1000;
	cout << "Éxécution de " << nombreAStar << " fois A*" << endl;
	double tempsAStarMicroSec = rtc.tester_n_paires_a_star(nombreAStar);
	double tempsAStarMilliSec = tempsAStarMicroSec / 1000;
	double tempsAStarSec = tempsAStarMilliSec / 1000;

	cout << "Temps pour éxécuter " << nombreAStar << " fois A*: " << (nombreAStar * tempsAStarSec) << " secondes." << endl;
	cout << "Temps moyen de A* " << tempsAStarSec << " secondes." << endl << endl;

	int nombreDijsktraMonceau = 1000;
	cout << "Éxécution de " << nombreDijsktraMonceau << " fois Dijkstra avec un monceau" << endl;
	double tempsDijsktraMonceauMicroSec = rtc.tester_n_paires_dijsktra_monceau(nombreDijsktraMonceau);
	double tempsDijsktraMonceauMilliSec = tempsDijsktraMonceauMicroSec / 1000;
	double tempsDijsktraMonceauSec = tempsDijsktraMonceauMilliSec / 1000;

	cout << "Temps pour éxécuter " << nombreDijsktraMonceau << " fois Dijkstra avec un monceau: " << (nombreDijsktraMonceau * tempsDijsktraMonceauSec) << " secondes." << endl;
	cout << "Temps moyen de Dijkstra avec un monceau " << tempsDijsktraMonceauSec << " secondes." << endl << endl;

	int nombreMeilleur = 1000;
	cout << "Éxécution de " << nombreMeilleur << " fois Le meilleur algorithme" << endl;
	double tempsMeilleurMicroSec = rtc.tester_n_paires_meilleur(nombreMeilleur);
	double tempsMeilleurMilliSec = tempsMeilleurMicroSec / 1000;
	double tempsMeilleurSec = tempsMeilleurMilliSec / 1000;

	cout << "Temps pour éxécuter " << nombreMeilleur << " fois Dijkstra avec un monceau: " << (nombreMeilleur * tempsMeilleurSec) << " secondes." << endl;
	cout << "Temps moyen de meilleur algorithme " << tempsMeilleurSec << " secondes." << endl << endl;

    int nombreFloyd = 1;

    cout << "Floyd-Warshall ne sera pas éxécuté car il prend des dizaines d'heures à terminer une seule fois." << endl;
    //cout << "Éxécution de " << nombreFloyd << " fois Floyd-Warshall" << endl;

	//double tempsFloydMicroSec = rtc.tester_n_paires_floyd(nombreFloyd);
	//double tempsFloydMilliSec = tempsFloydMicroSec / 1000;
	//double tempsFloydSec = tempsFloydMilliSec / 1000;

	//cout << "Temps pour éxécuter " << nombreFloyd << " fois Floyd: " << (nombreFloyd * tempsFloydSec) << " secondes." << endl;
	//cout << "Temps moyen de Floyd " << tempsFloydSec << " secondes." << endl << endl;

    //int nombreBellmanAcyclique = 1;

	cout << "Bellman-Ford pour graphe acyclique ne sera pas éxécuté car notre graphe contient plusieurs cycles" << endl;
	//cout << "Éxécution de " << nombreBellmanAcyclique << " fois Floyd-Warshall" << endl;

	//double tempsBellmanAcycliqueMicroSec = rtc.tester_n_paires_bellman_acyclique(nombreBellmanAcyclique);
	//double tempsBellmanAcycliqueMilliSec = tempsBellmanAcycliqueMicroSec / 1000;
	//double tempsBellmanAcycliqueSec = tempsBellmanAcycliqueMilliSec / 1000;

	//cout << "Temps pour éxécuter " << nombreBellmanAcyclique << " fois Floyd: " << (nombreBellmanAcyclique * tempsBellmanAcycliqueSec) << " secondes." << endl;
	//cout << "Temps moyen de Floyd " << tempsBellmanAcycliqueSec << " secondes." << endl << endl;

    return 0;
}
