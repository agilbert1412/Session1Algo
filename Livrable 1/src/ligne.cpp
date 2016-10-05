/**
 * \file ligne.cpp
 * \brief Cette classe représente une ligne d'autobus du réseau de transport contenues dans le fichier routes.txt
 * \author Slim Ben Yahia
 * \author Alex Gilbert
 * \date octobre 2016
 */

#include "ligne.h"
#include <string.h>


Ligne::Ligne(const std::vector<std::string> & ligne_gtfs)
: m_id(std::stoul(ligne_gtfs[0])), m_numero(ligne_gtfs[2]), m_description(ligne_gtfs[4]),
  m_categorie(couleurToCategorie(ligne_gtfs[7])), m_voyages(){
}

CategorieBus Ligne::couleurToCategorie(std::string couleur){
	if (couleur == "97BF0D")
	{
		return CategorieBus::METRO_BUS;
	}
	else if (couleur == "013888")
	{
		return CategorieBus::LEBUS;
	}
	else if (couleur == "E04503")
	{
		return CategorieBus::EXPRESS;
	}
	else if(couleur == "1A171B" || couleur == "003888")
	{
		return CategorieBus::COUCHE_TARD;
	}
	else
	{
		throw "Numéro de catégorie invalide";
	}
}

CategorieBus Ligne::getCategorie() const{
	return m_categorie;
}

void Ligne::setCategorie(CategorieBus categorie){
	m_categorie = categorie;
}

std::pair<std::string, std::string> Ligne::getDestinations() const{
	std::pair<std::string,std::string> destinations;

	destinations = std::make_pair(
			this->getVoyages().front()->getDestination(),
			this->getVoyages().back()->getDestination()
	);

	return destinations;
}

unsigned int Ligne::getId() const{
	return m_id;
}

void Ligne::setId(unsigned int id){
	m_id = id;
}

const std::string& Ligne::getNumero() const{
	return m_numero;
}

void Ligne::setNumero(const std::string& numero){
	m_numero = numero;
}

const std::vector<Voyage*>& Ligne::getVoyages() const{
	return m_voyages;
}

void Ligne::setVoyages(const std::vector<Voyage*>& voyages){
	m_voyages = voyages;
}

void Ligne::addVoyage(Voyage* ptr_voyage){
	m_voyages.push_back(ptr_voyage);
}

const std::string& Ligne::getDescription() const{
	return m_description;
}

void Ligne::setDescription(const std::string& description){
	m_description = description;
}

std::ostream& operator <<(std::ostream& f, const Ligne& p_ligne){
	return f << "LEBUS " <<  p_ligne.getNumero() << " " <<  p_ligne.getDestinations().first
					+  p_ligne.getDestinations().second << "\n";
}
