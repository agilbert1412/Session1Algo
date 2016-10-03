/**
 * \file station.cpp
 * \brief Classe représentant une station. Une station est un emplacement physique où un bus effectue des arrêts.
 * \author Slim Ben Yahia
 * \author Alex Gilbert
 * \date octobre 2016
 */

#include "station.h"

Station::Station(const std::vector<std::string>& ligne_gtfs)
: m_id(std::stoi(ligne_gtfs[0])), m_nom(ligne_gtfs[1]), m_description(ligne_gtfs[2]),
  m_coords(std::stod(ligne_gtfs[3]), std::stod(ligne_gtfs[4])), m_voyages_passants(){

}

std::ostream & operator<<(std::ostream & flux, const Station & p_station){
	return flux << p_station.getNom();
}

const Coordonnees & Station::getCoords() const{
	return m_coords;
}

void Station::setCoords(const Coordonnees& coords){
	m_coords.setLatitude(coords.getLatitude());
	m_coords.setLongitude(coords.getLongitude());
}

const std::string& Station::getDescription() const{
	return m_description;
}

std::vector<Ligne*> Station::getLignesPassantes() const{
	std::vector<Ligne*> lignes;
	for (unsigned int i = 0; i < m_voyages_passants.size(); i++)
	{
		lignes.push_back(m_voyages_passants[i]->getLigne());
	}
	return lignes;
}

const std::string& Station::getNom() const{
	return m_nom;
}

void Station::setNom(const std::string& nom){
	m_nom = nom;
}

unsigned int Station::getId() const{
	return m_id;
}

void Station::setId(unsigned int stationId){
	m_id = stationId;
}

const std::vector<Voyage*> & Station::getVoyagesPassants() const{
	return m_voyages_passants;
}

void Station::addVoyage(Voyage* ptr_voyage){
	m_voyages_passants.push_back(ptr_voyage);
}

double Station::distance(const Station& p_station) const{
	return m_coords.operator -(p_station.m_coords);
}
