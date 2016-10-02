/*!
 * \file arret.cpp
 * \brief Fichier contenant la classe arret
 * \author Slim Ben Yahia
 * \author Alex Gilbert
 * \date octobre 2016
 */

#include "arret.h"

Arret::Arret(const std::vector<std::string>& ligne_gtfs)
: m_station_id(std::stoi(ligne_gtfs[3])), m_heure_arrivee(ligne_gtfs[1]), m_heure_depart(ligne_gtfs[2]),
  m_numero_sequence(std::stoi(ligne_gtfs[4])), m_voyage_id(ligne_gtfs[0])
{
	// il faut transformer les string en objet de la classe Heure qui se trouvent dans auxiliaires.h
}
