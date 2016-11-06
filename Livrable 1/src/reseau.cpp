/*!
 * \file reseau.cpp
 * \brief Fichier contenant la classe reseau
 * \author Slim Ben Yahia
 * \author Alex Gilbert
 * \date novembre 2016
 */

#include "reseau.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

#define INFINI 999999
#define DEFAULT_TYPE 0


Reseau::Reseau() : m_nbSommets(0), m_nbArcs(0){
}

void Reseau::ajouterSommet(unsigned int numero) throw (std::logic_error){

	if (sommetExiste(numero)){
		throw std::logic_error("Numéro de sommet invalide.");
	}
	else if (numero == m_sommets.size()){
		m_sommets.push_back(numero);
		m_listesAdj.push_back(liste_arcs());
		m_nbSommets++;
	}
	else if (numero > m_sommets.size()){
		m_sommets.resize(numero + 1, -1);
		m_sommets[numero] = numero;
		m_listesAdj.resize(numero + 1);
		m_listesAdj[numero] = liste_arcs();
		m_nbSommets++;
	}
	else {
		m_sommets[numero] = numero;
		m_listesAdj[numero] = liste_arcs();
		m_nbSommets++;
	}
}

void Reseau::enleverSommet(unsigned int numero) throw (std::logic_error){

	if (!sommetExiste(numero)) {
		throw std::logic_error("Numéro de  sommet invalide.");
	}
	else{
		m_sommets[numero] = -1;
		m_listesAdj[numero].clear();

		for (unsigned int i = 0; i < m_sommets.size(); i++)	{
			m_listesAdj[i].erase(numero);
		}

		m_nbSommets--;
	}
}

void Reseau::ajouterArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout, unsigned int type)
				throw (std::logic_error){

	if (!arcExiste(numOrigine, numDest)){
		m_listesAdj[numOrigine].insert(std::make_pair(numDest,std::make_pair(cout, type)));
		m_nbArcs++;
	}
	else{
		throw std::logic_error("L'arc existe déjà.");
	}
}

void Reseau::enleverArc(unsigned int numOrigine, unsigned int numDest) throw (std::logic_error){

	if (!arcExiste(numOrigine, numDest)){
		throw std::logic_error("L'arc n'existe pas.");
	}

	std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>>::const_iterator iterateur =
						m_listesAdj[numOrigine].find(numDest);
	m_listesAdj[numOrigine].erase(iterateur);
	m_nbArcs--;
}

void Reseau::majCoutArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout) throw (std::logic_error){

	if (!arcExiste(numOrigine, numDest)){
		throw std::logic_error("L'arc n'existe pas.");
	}

	std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>>::iterator iterateur =
						m_listesAdj[numOrigine].find(numDest);
	iterateur->second.first = cout;
}

int Reseau::nombreSommets() const{
	return m_nbSommets;
}

int Reseau::nombreArcs() const{
	return m_nbArcs;
}

bool Reseau::estVide() const{
	return m_nbArcs == 0;
}

bool Reseau::sommetExiste(unsigned int numero) const{
	return (numero < m_sommets.size() && m_sommets[numero] != -1);
}

bool Reseau::arcExiste(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error){

	if (!sommetExiste(numOrigine) || !sommetExiste(numDest)) {
		throw std::logic_error("Numéro de  sommet invalide.");
	}

	return !(m_listesAdj[numOrigine].find(numDest) == m_listesAdj[numOrigine].end());
}

int Reseau::getCoutArc(unsigned int numOrigine, unsigned int numDestination) const throw (std::logic_error){

	if (!sommetExiste(numOrigine) || !sommetExiste(numDestination)) {
		throw std::logic_error("Numéro de  sommet invalide.");
	}
	if (!arcExiste(numOrigine, numDestination)){
		throw std::logic_error("L'arc n'existe pas.");
	}

	std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>>::const_iterator iterateur =
					m_listesAdj[numOrigine].find(numDestination);
	return iterateur->second.first;
}

int Reseau::getTypeArc(unsigned int numOrigine, unsigned int numDestination) const throw (std::logic_error){

	if (!sommetExiste(numOrigine) || !sommetExiste(numDestination)) {
		throw std::logic_error("Numéro de  sommet invalide.");
	}
	if (!arcExiste(numOrigine, numDestination)){
		throw std::logic_error("L'arc n'existe pas.");
	}

	std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>>::const_iterator iterateur =
					m_listesAdj[numOrigine].find(numDestination);
	return iterateur->second.second;
}

int Reseau::dijkstra(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin)
				throw (std::logic_error){
	if (!sommetExiste(numOrigine) || !sommetExiste(numDest)) {
			throw std::logic_error("Numéro de  sommet invalide.");
	}

	// Vecteur de tuples qui contiennent les 3 éléments suivant :
	// Un bool qui permet de savoir si le sommet a été solutionné
	// La distance entre l'origine et le sommet en question
	// Le numéro du sommet précédent
	std::vector<std::tuple<bool, unsigned int, int>> vectSoluDistPred;
	vectSoluDistPred.resize(m_sommets.size());

	int numTemp = numOrigine;
	unsigned int coutTemp;
	unsigned int indiceSommetAtraiter;
	std::vector<unsigned int> sommetATraiter;
	bool sommetDestTraite = false;

	std::fill(vectSoluDistPred.begin(),vectSoluDistPred.end(),std::make_tuple(false,INFINI,-1));
	std::get<1>(vectSoluDistPred[numOrigine]) = 0;

	while(!sommetDestTraite) {
		for (auto it : m_listesAdj[numTemp]) {
			if (!std::get<0>(vectSoluDistPred[it.first])) {

				if (std::get<1>(vectSoluDistPred[it.first]) > std::get<1>(vectSoluDistPred[numTemp]) + it.second.first){
					std::get<1>(vectSoluDistPred[it.first]) =  std::get<1>(vectSoluDistPred[numTemp]) + it.second.first;
					std::get<2>(vectSoluDistPred[it.first]) =  numTemp;
				}

				if(std::find(sommetATraiter.begin(), sommetATraiter.end(), it.first) == sommetATraiter.end()) {
					sommetATraiter.push_back(it.first);
				}
			}

		}
		std::get<0>(vectSoluDistPred[numTemp]) = true;
		if (numTemp == numDest) {
			sommetDestTraite = true;
		}

		if (sommetATraiter.size() == 0 && !sommetDestTraite) {
			throw std::logic_error("Aucun chemin possible");
		}
		coutTemp = INFINI;
		for (unsigned int i = 0; i < sommetATraiter.size(); i++){
			if (coutTemp > std::get<1>(vectSoluDistPred[sommetATraiter[i]])) {
				coutTemp = std::get<1>(vectSoluDistPred[sommetATraiter[i]]);
				indiceSommetAtraiter = i;
			}
		}
		numTemp = sommetATraiter[indiceSommetAtraiter];
		sommetATraiter.erase(sommetATraiter.begin() + indiceSommetAtraiter);
	}

	// On retrace le chemin le plus court
	numTemp = numDest;
	while(numTemp != -1){
		chemin.push_back(numTemp);
		numTemp = std::get<2>(vectSoluDistPred[numTemp]);
	}
	std::reverse(chemin.begin(),chemin.end());

	return std::get<1>(vectSoluDistPred[numDest]);
}

int Reseau::bellmanFord(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin)
				throw (std::logic_error){
	if (!sommetExiste(numOrigine) || !sommetExiste(numDest)) {
			throw std::logic_error("Numéro de  sommet invalide.");
	}

	// Vecteur de pair qui contiennent les 2 éléments suivant :
	// La distance entre l'origine et le sommet en question
	// Le numéro du sommet précédent
	std::vector<std::pair<unsigned int, int>> vectDistPred;
	vectDistPred.resize(m_sommets.size());

	bool reductionEffectue;

	std::fill(vectDistPred.begin(),vectDistPred.end(),std::make_pair(INFINI, -1));
	vectDistPred[numOrigine].first = 0;

	for(unsigned int i = 0; i < m_sommets.size(); i++)  {
		reductionEffectue = false;
		for (unsigned int j = 0; j < m_listesAdj.size(); j++){
			if  (m_sommets[j] != -1){
				for (auto it : m_listesAdj[j]) {
					if (vectDistPred[it.first].first > vectDistPred[j].first  + it.second.first){
						vectDistPred[it.first].first =  vectDistPred[j].first  + it.second.first;
						vectDistPred[it.first].second =  j;
						reductionEffectue = true;
					}
				}
			}
		}

		if (!reductionEffectue) {
			break;
		}
	}

	if (vectDistPred[numDest].second == -1){
		throw std::logic_error("Aucun chemin possible");
	}
	// On retrace le chemin le plus court
	int numTemp = numDest;
	while(numTemp != -1){
		chemin.push_back(numTemp);
		numTemp = vectDistPred[numTemp].second;
	}
	std::reverse(chemin.begin(),chemin.end());

	return vectDistPred[numDest].first;
}

bool Reseau::estFortementConnexe() const{
	std::vector<std::vector<unsigned int> > composantes;
	return getComposantesFortementConnexes(composantes) == 1;
}

int Reseau::getComposantesFortementConnexes(std::vector<std::vector<unsigned int> > & composantes) const{
	std::stack<unsigned int> pileSommetTraite;
	std::stack<unsigned int> pileParcoursProfondeur;
	unsigned int sommetTemp;
	unsigned int nbSommetTraiter = 0;
	int nbComposantesFortementConnexes = 0;

	std::vector<bool> sommetsTraites;
	sommetsTraites.resize(m_sommets.size());
	std::fill(sommetsTraites.begin(),sommetsTraites.end(), false);

	std::vector<liste_arcs> listesAdjInverse;
	listesAdjInverse.resize(m_listesAdj.size());

	for(unsigned int i = 0; i < m_listesAdj.size(); i++)  {
		for (auto it : m_listesAdj[i]) {
			listesAdjInverse[it.first].insert(std::make_pair(i,std::make_pair(it.second.first, it.second.second)));
		}
	}

	// Parcours en profondeur du graphe inverse
	while(nbSommetTraiter < m_nbSommets){
		if (pileParcoursProfondeur.size() == 0){
			for(unsigned int i = 0; i < m_sommets.size(); i++)  {
				if (m_sommets[i] != -1 && !sommetsTraites[i]) {
					pileParcoursProfondeur.push(i);
					sommetsTraites[i] = true;
					break;
				}
			}
		}

		while(pileParcoursProfondeur.size() > 0){
				sommetTemp = pileParcoursProfondeur.top();
				pileParcoursProfondeur.pop();
				pileSommetTraite.push(sommetTemp);
				nbSommetTraiter++;

				for (auto it : listesAdjInverse[sommetTemp]) {
					if (!sommetsTraites[it.first]){
						sommetsTraites[it.first] = true;
						pileParcoursProfondeur.push(it.first);
					}
				}
		}
	}

	// Parcours en profondeur du graphe original
	nbSommetTraiter = 0;
	std::stack<unsigned int>().swap(pileParcoursProfondeur); // Permet de vider la pile
	std::vector<bool>().swap(sommetsTraites); // Permet de vider le vecteur
	sommetsTraites.resize(m_sommets.size());
	while(nbSommetTraiter < m_nbSommets){
		composantes.push_back(std::vector<unsigned int>());

		while (pileParcoursProfondeur.size() == 0){
			sommetTemp = pileSommetTraite.top();
			pileSommetTraite.pop();
			if (!sommetsTraites[sommetTemp]) {
				pileParcoursProfondeur.push(sommetTemp);
				sommetsTraites[sommetTemp] = true;
				composantes[nbComposantesFortementConnexes].push_back(sommetTemp);
				break;
			}
		}

		while(pileParcoursProfondeur.size() > 0){
				sommetTemp = pileParcoursProfondeur.top();
				pileParcoursProfondeur.pop();
				nbSommetTraiter++;

				for (auto it : m_listesAdj[sommetTemp]) {
					if (!sommetsTraites[it.first]){
						sommetsTraites[it.first] = true;
						pileParcoursProfondeur.push(it.first);
						composantes[nbComposantesFortementConnexes].push_back(it.first);
					}
				}
		}
		nbComposantesFortementConnexes ++;
	}

	return nbComposantesFortementConnexes;
}
