/**
 * \file coordonnees.cpp
 * \brief Cette classe permet de représenter les coordonnées GPS d'un endroit
 * \author Slim Ben Yahia
 * \author Alex Gilbert
 * \date octobre 2016
 */

#include "coordonnees.h"
#include <math.h>

const double MinLatitude = -90;
const double MaxLatitude = 90;
const double Minlongitude = -180;
const double Maxlongitude = 180;
const int EarthRadius = 6371;
const double piDivBy180 = 0.017453292519943295; // Math.PI / 180


Coordonnees::Coordonnees(double latitude, double longitude){
  if (is_valide_coord(latitude, longitude))
  {
	  m_latitude = latitude;
	  m_longitude = longitude;
  }
  else
  {
  	  throw "Coordonnées invalides";
  }
}

double Coordonnees::getLatitude() const{
	return m_latitude;
}

void Coordonnees::setLatitude(double latitude){
	if (latitude >= MinLatitude && latitude <= MaxLatitude)
	{
		m_latitude = latitude;
	}
	else
	{
		throw "Latitude invalide";
	}
}

double Coordonnees::getLongitude() const{
	return m_longitude;
}

void Coordonnees::setLongitude(double longitude){
	if (longitude >= Minlongitude && longitude <= Maxlongitude)
	{
		m_longitude = longitude;
	}
	else
	{
		throw "Longitude invalide";
	}
}

bool Coordonnees::is_valide_coord(double p_latitude, double p_longitude){
  return (p_latitude >= MinLatitude && p_latitude <= MaxLatitude &&
		  p_longitude >= Minlongitude && p_longitude <= Maxlongitude);
}

double Coordonnees::operator-(const Coordonnees & other) const{
	double lat1Rad = m_latitude * piDivBy180;
	double lat2Rad = other.m_latitude * piDivBy180;

	double distanceLatRad = (m_latitude - other.m_latitude) * piDivBy180;
	double distanceLongRad = (m_longitude - other.m_longitude) * piDivBy180;
	double varCalcul = (sin(distanceLatRad / 2) * sin(distanceLatRad / 2))
			+ cos(lat2Rad) * cos(lat1Rad) * (sin(distanceLongRad / 2) * sin(distanceLongRad / 2));
	double angle = 2 * atan2(sqrt(varCalcul), sqrt(1 - varCalcul));
    return angle * EarthRadius;
}

std::ostream & operator<<(std::ostream & flux, const Coordonnees & p_coord){
	return flux << "Lattitude: " << p_coord.getLatitude() << " Longitude: " << p_coord.getLongitude();
}
