/**
 * \file coordonnees.cpp
 * \brief Cette classe permet de représenter les coordonnées GPS d'un endroit
 * \author Slim Ben Yahia
 * \author Alex Gilbert
 * \date octobre 2016
 */

#include "auxiliaires.h"
#include <ctime>

using namespace std;

vector<string> split(const string& s, char delim) {

	size_t prochainDelimPos = s.find_first_of(delim);
	int debut = 0;

	vector<string> retour;
	while (prochainDelimPos <= string::npos)
	{
		retour.emplace_back(s.substr(debut, prochainDelimPos - debut));

		if (prochainDelimPos == string::npos)
			break;

		debut = prochainDelimPos + 1;
		prochainDelimPos = s.find_first_of(delim, debut);
	}

	return retour;
}

/*!
 * \brief Permet de lire un fichier au format gtfs
 * \param[in] nomFichier: chemin d'acces au fichier qui est suposé contennir plusieurs lignes et plusieurs colonnes
 * \param[out] resultats: vecteur 2D destiné à contenir le fichier, l'élement [i][j] représente la ième ligne et la jème colonne du fichier
 * \param[in] delimiteur: le caractère délimiteur des colonnes dans ce fichier.
 * \param[in] rm_entete: un booléen qui spécifie s'il faut supprimer ou pas la première ligne du fichier.
 * \pre Le fichier existe.
 * \exception logic_error s'il y a un problème lors de l'ouverture du fichier.
 */
void lireFichier(string nomFichier, vector<vector<string>>& resultats, char delimiteur, bool rm_entete) {
	string ligne;
	ifstream fichier(nomFichier);

	//resultats.reserve(100);  // On aura pas plus de 5 millions de lignes (?)

	if (rm_entete)
		getline(fichier, ligne);

	while (getline(fichier, ligne))
	{
		resultats.emplace_back();
	    vector<string>& rangee = resultats.back();
	    rangee = split(ligne, delimiteur);
//	    rangee.reserve(1000); // On aura pas plus de 1000 elements par ligne (?)
//	    istringstream buffer(ligne);
//	    string element;
//	    while (buffer >> element)
//	    {
//	    	rangee.push_back(element);
//	    }
	}
}

Date::Date(){
	time_t t = time(NULL);
	tm* ptrTemps = localtime(&t);
	m_an = ptrTemps->tm_year + 1900;
	m_mois = ptrTemps->tm_mon;
	m_jour = ptrTemps->tm_mday;
}

Date::Date(unsigned int an, unsigned int mois, unsigned int jour){
	if (mois > 12 || mois < 1)
		throw "Le mois doit être entre 1 et 12";
	if (jour > 31 || jour < 1)
		throw "Le jour doit être entre 1 et 31";
	m_an = an;
	m_mois = mois;
	m_jour = jour;
}

bool Date::operator==(const Date & other) const {
	if (this->m_an != other.m_an)
		return false;
	if (this->m_jour != other.m_jour)
		return false;
	if (this->m_mois != other.m_mois)
		return false;
	return true;
}

bool Date::operator<(const Date & other) const {
	if (this->m_an < other.m_an)
		return true;
	if (this-> m_an > other.m_an)
		return false;
	if (this->m_mois < other.m_mois)
		return true;
	if (this->m_mois > other.m_mois)
		return false;
	if (this->m_jour < other.m_jour)
		return true;
	return false;
}

bool Date::operator>(const Date & other) const {
	if (this->m_an > other.m_an)
		return true;
	if (this-> m_an < other.m_an)
		return false;
	if (this->m_mois > other.m_mois)
		return true;
	if (this->m_mois < other.m_mois)
		return false;
	if (this->m_jour > other.m_jour)
		return true;
	return false;
}

std::ostream & operator<<(std::ostream & flux, const Date & p_date) {
	return flux << p_date.m_jour << "-" << p_date.m_mois << "-" << p_date.m_an;
}

Heure::Heure() {
	time_t t = time(NULL);
	tm* ptrTemps = localtime(&t);
	m_heure = ptrTemps->tm_hour;
	m_min = ptrTemps->tm_min;
	m_sec = ptrTemps->tm_sec;
}

Heure::Heure(unsigned int heure, unsigned int min, unsigned int sec) {
	if (heure >= 30)
		throw "L'heure doit être inférieure à 30";
	if (min >= 60)
		throw "Les minutes doivent être inférieures à 60";
	if (sec >= 60)
		throw "Les secondess doivent être inférieures à 60";
	m_heure = heure;
	m_min = min;
	m_sec = sec;
}

Heure Heure::add_secondes(unsigned int secs) const {
	Heure nouvelleHeure = Heure(*this);
	nouvelleHeure.m_sec = nouvelleHeure.m_sec + secs;
	while (nouvelleHeure.m_sec >= 60) {
		nouvelleHeure.m_sec = nouvelleHeure.m_sec - 60;
		nouvelleHeure.m_min = nouvelleHeure.m_min + 1;
	}
	while (nouvelleHeure.m_min >= 60) {
		nouvelleHeure.m_min = nouvelleHeure.m_min - 60;
		nouvelleHeure.m_heure = nouvelleHeure.m_heure + 1;
	}
	while (nouvelleHeure.m_heure >= 30) {
		nouvelleHeure.m_heure = nouvelleHeure.m_heure - 24;
	}
	return nouvelleHeure;
}

bool Heure::operator==(const Heure & other) const {
	if (this->m_heure != other.m_heure)
		return false;
	if (this->m_min != other.m_min)
		return false;
	if (this->m_sec != other.m_sec)
		return false;
	return true;
}

bool Heure::operator<(const Heure & other) const {
	if (this->m_heure < other.m_heure)
		return true;
	if (this-> m_heure > other.m_heure)
		return false;
	if (this->m_min < other.m_min)
		return true;
	if (this->m_min > other.m_min)
		return false;
	if (this->m_sec < other.m_sec)
		return true;
	return false;
}

bool Heure::operator>(const Heure & other) const {
	if (this->m_heure > other.m_heure)
		return true;
	if (this-> m_heure < other.m_heure)
		return false;
	if (this->m_min > other.m_min)
		return true;
	if (this->m_min < other.m_min)
		return false;
	if (this->m_sec > other.m_sec)
		return true;
	return false;
}

bool Heure::operator<= (const Heure & other) const {
	return (*this == other || *this < other);
}

bool Heure::operator>= (const Heure & other) const {
	return (*this == other || *this > other);
}

int Heure::operator- (const Heure & other) const {
	return (this->m_sec - other.m_sec) + ((this->m_min - other.m_min) * 60) + ((this->m_heure - other.m_heure) * 3600);
}

std::ostream& operator<<(std::ostream& flux, const Heure& p_heure) {
	return flux << p_heure.m_heure << ":" << p_heure.m_min << ":" << p_heure.m_sec;
}
