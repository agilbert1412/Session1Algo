/**
 * \file TAs.hpp
 * \brief Implémantation des méthodes de la classe Tas
 * \author Slim Ben Yahia
 * \date décembre 2016
 *
 */
#include "tas.h"

Tas::Tas(std::vector<std::pair<unsigned int, int>> vecSommets): m_vectSommets(vecSommets) {
	int dernierParent = m_vectSommets.size() / 2 - 1;
	for (int i = m_vectSommets.size() - 1; i >= 0; i--) {
		percDown(i);
	}
}

void Tas::MAJsommet(unsigned int numSommet, int value) throw (std::logic_error){
	for(int i = 0; i <  m_vectSommets.size(); i++){
		if (m_vectSommets[i].first == numSommet) {
			int oldValue = m_vectSommets[i].second;
			m_vectSommets[i].second = value;
			if (value > oldValue) {
				percDown(i);
			}else if (value < oldValue) {
				percUp(i);
			}
			return;
		}
	}

	throw std::logic_error ("Numéro du sommet invalide");
}


std::pair<unsigned int, int> Tas::SupprimerPlusPetit() throw (std::logic_error){
	if (m_vectSommets.size() == 0) throw std::logic_error ("Aucun élément dans le tableau");

	std::pair<unsigned int, int> sommetSupprime = m_vectSommets[0];

	m_vectSommets[0] = m_vectSommets[m_vectSommets.size() - 1];

	if (m_vectSommets[m_vectSommets.size() - 1].first == 6123){
			int a = 0;
		}
	m_vectSommets.pop_back();

	percDown(0);

	return sommetSupprime;
}

void Tas::percDown(int index){
	if (m_vectSommets.size() < index) return;
	int indexEnfantDroit = 2 * index + 2;
	int indexEnfantGauche = 2 * index + 1;
	std::pair<int, int> indexValue = std::make_pair(index,m_vectSommets[index].second);
	std::pair<unsigned int, int> sommetTemp;

	if (m_vectSommets.size() <= indexEnfantGauche) {
		return;
	} else if (m_vectSommets[indexEnfantGauche].second < indexValue.second) {
		indexValue.first = indexEnfantGauche;
		indexValue.second = m_vectSommets[indexEnfantGauche].second;
	}

	if (!(m_vectSommets.size() <= indexEnfantDroit) &&
			m_vectSommets[indexEnfantDroit].second < indexValue.second) {
		indexValue.first = indexEnfantDroit;
		indexValue.second = m_vectSommets[indexEnfantDroit].second;
	}

	if (indexValue.first != index) {
		sommetTemp = m_vectSommets[index];
		m_vectSommets[index] = m_vectSommets[indexValue.first];
		m_vectSommets[indexValue.first] = sommetTemp;
		percDown(indexValue.first);
	}
}

void Tas::percUp(int index){
	std::pair<unsigned int, int> sommetTemp;

	if (index == 0) {
			return;
		}

	int indexParent = (index - 1)/2;

	if (m_vectSommets[index].second < m_vectSommets[indexParent].second) {
		sommetTemp = m_vectSommets[index];
		m_vectSommets[index] = m_vectSommets[indexParent];
		m_vectSommets[indexParent] = sommetTemp;;
		percUp(indexParent);
	}
}
