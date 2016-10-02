/*!
 * \file arret.cpp
 * \brief Fichier contenant la classe arret
 * \author Slim Ben Yahia
 * \author Alex Gilbert
 * \date octobre 2016
 */

#include "arret.h"

Arret::Arret(const std::vector<std::string>& ligne_gtfs)
: m_station_id(std::stoi(ligne_gtfs[0])),
  m_heure_arrivee(std::stoi(ligne_gtfs[1].substr(0,2)), std::stoi(ligne_gtfs[1].substr(3,2)), std::stoi(ligne_gtfs[1].substr(6,2))),
  m_heure_depart(std::stoi(ligne_gtfs[2].substr(0,2)), std::stoi(ligne_gtfs[2].substr(3,2)), std::stoi(ligne_gtfs[2].substr(6,2))),
  m_numero_sequence(std::stoi(ligne_gtfs[3])), m_voyage_id(ligne_gtfs[4])
{
}

const Heure& Arret::getHeureArrivee() const
{
	return m_heure_arrivee;
}

void Arret::setHeureArrivee(const Heure& p_heureArrivee)
{
	m_heure_arrivee = p_heureArrivee;
}

const Heure& Arret::getHeureDepart() const
{
	return m_heure_depart;
}

void Arret::setHeureDepart(const Heure& p_heureDepart)
{
	m_heure_arrivee = p_heureDepart;
}

unsigned int Arret::getNumeroSequence() const
{
	return m_numero_sequence;
}

void Arret::setNumeroSequence(unsigned int p_numeroSequence)
{
	m_numero_sequence = p_numeroSequence;
}

unsigned int Arret::getStationId() const
{
	return m_station_id;
}

void Arret::setStationId(unsigned int stationId)
{
	m_station_id = stationId;
}

std::string Arret::getVoyageId() const
{
	return m_voyage_id;
}

void Arret::setVoyageId(const std::string& voyageId)
{
	m_voyage_id = voyageId;
}

bool Arret::operator< (const Arret & p_other) const
{
	return getNumeroSequence() < p_other.getNumeroSequence();
}

bool Arret::operator> (const Arret & p_other) const
{
	return getNumeroSequence() > p_other.getNumeroSequence();
}

std::ostream & operator<<(std::ostream & flux, const Arret & p_arret)
{
	return flux << "Satation ID: " << p_arret.getStationId() << " Voyage ID: " << p_arret.getVoyageId();
}

