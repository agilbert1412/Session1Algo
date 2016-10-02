/**
 * \file voyage.cpp
 * \brief Classe permettant de décrire un voyage
 * \author Slim Ben Yahia
 * \author Alex Gilbert
 * \date octobre 2016
 */

#include "voyage.h"
#include <algorithm>

Voyage::Voyage(const std::vector<std::string>& ligne_gtfs, Ligne* p_ligne)
: m_id(ligne_gtfs[0]), m_service_id(ligne_gtfs[1]), m_destination(ligne_gtfs[2]), m_ligne(p_ligne)
{
}

Arret & Voyage::arretDeLaStation(unsigned int p_num_station)
{
	for (unsigned int i = 0; i < m_arrets.size(); i++)
	{
		if (m_arrets[i].getStationId() == p_num_station)
		{
			return m_arrets[i];
		}
	}

	throw ("Numéro de sation invalide.");
}

std::vector<Arret> Voyage::getArrets() const
{
	return m_arrets;
}

const std::string& Voyage::getDestination() const
{
	return m_destination;
}

void Voyage::setDestination(const std::string& p_destination)
{
	m_destination = p_destination;
}

std::string Voyage::getId() const
{
	return m_id;
}

void Voyage::setId(std::string p_id)
{
	m_id = p_id;
}

Ligne* Voyage::getLigne() const
{
	return m_ligne;
}

void Voyage::setLigne(Ligne* p_ligne)
{
	m_ligne = p_ligne;
}

std::string Voyage::getServiceId() const
{
	return m_service_id;
}

void Voyage::setServiceId(std::string p_service_id)
{
	m_service_id = p_service_id;
}

Heure Voyage::getHeureDepart() const
{
	if (m_arrets.size() > 0)
	{
		return m_arrets[0].getHeureDepart();
	}
	else
	{
		throw "Les arrêts du voyage ne sont pas enregistrés";
	}
}

Heure Voyage::getHeureFin() const
{
	if (m_arrets.size() > 0)
	{
		return m_arrets.back().getHeureDepart();
	}
	else
	{
		throw "Les arrêts du voyage ne sont pas enregistrés";
	}
}

void Voyage::setArrets(std::vector<Arret>& resultat)
{
	sort(resultat.begin(), resultat.end());
	for (unsigned int i = 0; i < resultat.size() - 1; i++)
	{
		if (resultat[i].getHeureArrivee() == resultat[i+1].getHeureArrivee())
		{
			resultat[i+1].getHeureArrivee().add_secondes(30);
			resultat[i+1].getHeureDepart().add_secondes(30);
		}
	}
	m_arrets = resultat;
}

bool Voyage::operator< (const Voyage & p_other) const
{
	return getHeureDepart() < p_other.getHeureDepart();

}

bool Voyage::operator> (const Voyage & p_other) const
{
	return getHeureDepart() > p_other.getHeureDepart();

}

std::ostream & operator<<(std::ostream & flux, const Voyage & p_voyage)
{
	return flux << "ID: " << p_voyage.getId();

}

