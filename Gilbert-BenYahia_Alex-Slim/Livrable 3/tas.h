/**
 * \file Tas.h
 * \brief Classe générique d'un tas
 * \author Slim Ben Yahia
 * \date décembre 2016
 *
 * Definition de la classe Tas et de ses méthodes de parcours
 */

#include <stdexcept>
#include <iostream>
#include <vector>

/**
 * \class Tas
 *
 * \brief classe représentant un tas de sommets
 *
 *  La classe gère un tas. L'implémentation se fait par vecteur.
 */
class Tas {
public:;
	Tas(std::vector<std::pair<unsigned int, int>> vecSommets);
	void MAJsommet(unsigned int numSommet, int value) throw (std::logic_error);
	std::pair<unsigned int, int> SupprimerPlusPetit() throw (std::logic_error);


private:
	std::vector<std::pair<unsigned int, int>> m_vectSommets;
	void percDown(int index);
	void percUp(int index);
};

