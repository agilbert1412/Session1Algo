/**
 * \file Tas.hpp
 * \brief Implémentation des méthodes de la classe Tas
 * \author Slim Ben Yahia
 * \date décembre 2016
 *
 */
#include "tas.h"

Tas::Tas(std::unordered_map<unsigned int, int> mapSommets) {
	int dernierParent = mapSommets.size() / 2 - 1;
	int index = 0;
	for(auto sommet: mapSommets){
		m_vectSommets.push_back(std::make_pair(sommet.first, sommet.second));
		m_sommetsIndex.insert(std::make_pair(sommet.first, index));
		index ++;
	}
	for (int i = dernierParent; i >= 0; i--) {
		percDown(i);
	}
}

void Tas::MAJsommet(unsigned int numSommet, int value) throw (std::logic_error){
	int index;

	std::unordered_map<unsigned int, int>::iterator it = m_sommetsIndex.find(numSommet);
	if(it != m_sommetsIndex.end()){
		index = m_sommetsIndex[numSommet];
	} else {
		throw std::logic_error ("Numéro du sommet invalide");
	}

	int oldValue = m_vectSommets[index].second;
	m_vectSommets[index].second = value;
	if (value > oldValue) {
		percDown(index);
	}else if (value < oldValue) {
		percUp(index);
	}
}

std::pair<unsigned int, int> Tas::AvoirPlusPetit() throw (std::logic_error){
	if (m_vectSommets.size() == 0) throw std::logic_error ("Aucun élément dans le tableau");
	return m_vectSommets[0];
}

void Tas::SupprimerPlusPetit() throw (std::logic_error){
	if (m_vectSommets.size() == 0) throw std::logic_error ("Aucun élément dans le tableau");

	m_sommetsIndex.erase(m_vectSommets[0].first);
	for(auto sommet: m_sommetsIndex){
		sommet.second -- ;
	}
	m_vectSommets[0] = m_vectSommets[m_vectSommets.size() - 1];
	m_vectSommets.pop_back();

	percDown(0);
}

void Tas::percDown(int index){
	if (m_vectSommets.size() < index) return;
	int indexEnfantDroit = 2 * index + 2;
	int indexEnfantGauche = 2 * index + 1;
	std::pair<int, int> indexValue = std::make_pair(index,m_vectSommets[index].second);
	std::pair<unsigned int, int> sommetTemp;

	if (m_vectSommets.size() < indexEnfantGauche) {
		return;
	} else if (m_vectSommets[indexEnfantGauche].second < indexValue.second) {
		indexValue.first = indexEnfantGauche;
		indexValue.second = m_vectSommets[indexEnfantGauche].second;
	}

	if (!m_vectSommets.size() < indexEnfantDroit &&
			m_vectSommets[indexEnfantDroit].second < indexValue.second) {
		indexValue.first = indexEnfantDroit;
		indexValue.second = m_vectSommets[indexEnfantDroit].second;
	}

	if (indexValue.first != index) {
		sommetTemp = m_vectSommets[index];
		m_vectSommets[index] = m_vectSommets[indexValue.first];
		m_vectSommets[indexValue.first] = sommetTemp;
		m_sommetsIndex[m_vectSommets[index].first] = indexValue.first;
		m_sommetsIndex[m_vectSommets[indexValue.first].first] = index;
		percDown(indexValue.first);
	}
}

void Tas::percUp(int index){
	std::pair<unsigned int, int> sommetTemp;
	int indexParent = (index - 1)/2;

	if (index == 0) {
		return;
	}

	if (m_vectSommets[index].second < m_vectSommets[indexParent].second) {
		sommetTemp = m_vectSommets[index];
		m_vectSommets[index] = m_vectSommets[indexParent];
		m_vectSommets[indexParent] = sommetTemp;
		m_sommetsIndex[m_vectSommets[index].first] = indexParent;
		m_sommetsIndex[m_vectSommets[indexParent].first] = index;
		percUp(indexParent);
	}
}
