/*
 * gestionnaire.cpp
 *
 *  Created on: 2016-11-02
 *      Author: Alex
 */

#include "gestionnaire.h"
#include <cmath>

using namespace std;

/*!
* \brief Constructeur de la classe Gestionnaire. C'est ici que vous devez lire et charger les
fichiers gtfs utiles au tp.
* \param chemin_dossier: chemin d'accès vers le dossier gtfs. Dans le cadre du tp, vous
devez vous intéresser aux fichiers
* routes.txt, trips.txt, stop_times.txt, stops.txt, calendar_dates.txt
*
*/
Gestionnaire::Gestionnaire(string chemin_dossier)
{
	try
	{
		clock_t clkStart { };
		clock_t clkEnd { };
		double timePassed { };
		{
			clkStart = clock();
			cout << "0" << endl;
			unordered_map<string, string> mapLignesIds;
			{
				vector<vector<string>> resultsRoutes;
				lireFichier(chemin_dossier + routesFile, resultsRoutes, delimiter, true);

				for (unsigned int i = 0; i < resultsRoutes.size(); i++)	{
					enlever_guillemets(resultsRoutes[i][2]);
					m_lignes.insert(make_pair(resultsRoutes[i][2], Ligne(resultsRoutes[i])));
					mapLignesIds.insert(make_pair(resultsRoutes[i][0], resultsRoutes[i][2]));
				}
			}
			clkEnd = clock();
			timePassed = (double)(clkEnd - clkStart) / CLOCKS_PER_SEC;
			cout << "1: " << timePassed << endl;
			clkStart = clock();
			std::unordered_map<string, vector<Arret>> mapVoyageArrets;
			unordered_map<unsigned int, vector<string>> mapStationVoyage;
			{
				vector<vector<string>> resultsStopsTimes;
				{
					lireFichier(chemin_dossier + stopTimesFile, resultsStopsTimes, delimiter, true);

					for (unsigned int i = 0; i < resultsStopsTimes.size(); i++)
					{
						Arret arretTemp = Arret(resultsStopsTimes[i]);

						mapStationVoyage[arretTemp.getStationId()].push_back(arretTemp.getVoyageId());
						//if (mapVoyageArrets.find(arretTemp.getVoyageId()) != mapVoyageArrets.end()) {
							mapVoyageArrets[arretTemp.getVoyageId()].push_back(arretTemp);
						//} else {
						//	mapVoyageArrets.insert(make_pair(arretTemp.getVoyageId(), vector<Arret> {arretTemp}));
						//}
					}
				}
			}
			clkEnd = clock();
			timePassed = (double)(clkEnd - clkStart) / CLOCKS_PER_SEC;
			cout << "2: " << timePassed << endl;
			clkStart = clock();
			std::unordered_map<std::string, Voyage*> mapVoyage;
			{
				vector<vector<string>> resultsTrips;
				lireFichier(chemin_dossier + tripsFile, resultsTrips, delimiter, true);
				for (unsigned int i = 0; i < resultsTrips.size(); i++)
				{
					Ligne* laLigne = &(m_lignes.find(mapLignesIds.find(resultsTrips[i][0])->second)->second);
					Voyage* voy = new Voyage { resultsTrips[i], laLigne };
					mapVoyage.insert(make_pair(voy->getId(), voy));
					laLigne->addVoyage(voy);
					unordered_map<string, vector<Arret>>::const_iterator iteratorArrets = mapVoyageArrets.find(voy->getId());
					if (iteratorArrets != mapVoyageArrets.end())
					{
						vector<Arret> vectArrets = iteratorArrets->second;
						voy->setArrets(vectArrets);
					}
					m_voyages.push_back(*voy);
				}
			}
			clkEnd = clock();
			timePassed = (double)(clkEnd - clkStart) / CLOCKS_PER_SEC;
			cout << "3: " << timePassed << endl;
			clkStart = clock();
			{
				vector<vector<string>> resultsStops;
				lireFichier(chemin_dossier + stopsFile, resultsStops, delimiter, true);
				for (unsigned int i = 0; i < resultsStops.size(); i++)	{
					Station stat = Station(resultsStops[i]);
					vector<string> voyagesDeLaStation = mapStationVoyage[stat.getId()];
					for (int j = 0; j < voyagesDeLaStation.size(); j++)
					{
						stat.addVoyage(mapVoyage.at(voyagesDeLaStation[j]));
					}
					m_stations.insert(make_pair(stoi(resultsStops[i][0]), stat));
				}
			}
		}
		clkEnd = clock();
		timePassed = (double)(clkEnd - clkStart) / CLOCKS_PER_SEC;
		cout << "4: " << timePassed << endl;
		clkStart = clock();
		{
			vector<vector<string>> resultsCalendarDates;
			lireFichier(chemin_dossier + calendarDatesFile, resultsCalendarDates, delimiter, true);
			for (unsigned int i = 0; i < resultsCalendarDates.size(); i++)
			{

				string dateTemp = resultsCalendarDates[i][1];
				for (unsigned int j = 0; j < m_voyages.size(); j++)
				{
					if (m_voyages[j].getServiceId() == resultsCalendarDates[i][0])
					{
						m_voyages_date[dateTemp].push_back(&m_voyages[j]);
					}
				}
			}
		}

		clkEnd = clock();
		timePassed = (double)(clkEnd - clkStart) / CLOCKS_PER_SEC;
		cout << "5: " << timePassed << endl;

		sort(m_voyages.begin(), m_voyages.end());
	}
	catch (char const* msg)
	{
		cout << msg << "\n";
	}
}

/*!
* \brief Permet de vérifier si une date est prise en charge dans l'ensemble des dates dans l'application.
* \param date: la date d'intérêt
* \return True ssi la date est prise en charge dans l'application
*/
bool Gestionnaire::date_est_prise_en_charge(const Date& date)
{
	string dateString = to_string(date.getAn()) + string(2 - to_string(date.getMois()).length(), '0').append(to_string(date.getMois())) + string(2 - to_string(date.getJour()).length(), '0').append(to_string(date.getJour()));

	return (m_voyages_date.find(dateString) != m_voyages_date.end());
}

void Gestionnaire::enlever_guillemets(string & champ)
{
	if (champ.front() == '"')
		if (champ.back() == '"')
			champ = champ.substr(1, champ.length() - 2);
	//return champ;
}

/*!
* \brief Permet de vérifier si une ligne avec un certain numéro existe dans l’ensemble des
lignes chargées dans le constructeur.
* \param num_ligne: le numéro de la ligne d'intérêt
* \return True ssi le numéro est pris en charge
*/
bool Gestionnaire::bus_existe(string num_ligne)
{
	enlever_guillemets(num_ligne);
	return (m_lignes.find(num_ligne) != m_lignes.end());
}

/*!
* \brief Permet de vérifier si un numéro de station existe dans l’ensemble des stations
chargées dans le constructeur.
* \param station_id: l'identifiant de la station d'intérêt
* \return True ssi la station est prise en charge
*/
bool Gestionnaire::station_existe(int station_id)
{
	return (m_stations.find(station_id) != m_stations.end());
}

/*!
* \brief Accès à une ligne à partir de son numéro
* \param num_ligne: le numéro de la ligne d'intérêt
* \return objet Ligne correspondant au numéro d'intérêt
* \exception Il n’existe pas de ligne ayant ce numéro
*/
Ligne Gestionnaire::getLigne(string num_ligne)
{
	enlever_guillemets(num_ligne);
	unordered_map<string, Ligne>::const_iterator ligne = m_lignes.find(num_ligne);
	if (ligne == m_lignes.end())
		throw "Il n’existe pas de ligne ayant ce numéro";
	return ligne->second;
}

/*!
* \brief Accès à une station à partir de son id
* \param station_id: l'identifiant de la station d'intéret
* \return objet Station correspondant à l'id d'intérêt
* \exception Il n’existe pas de station ayant cet identifiant
*/
Station Gestionnaire::getStation(int station_id)
{
	unordered_map<unsigned int, Station>::const_iterator station = m_stations.find(station_id);
	if (station == m_stations.end())
		throw "Il n’existe pas de station ayant cet identifiant";
	return station->second;
}

/*!
* \brief Permet de trouver les voyages d'une ligne qui passe par une station
* \param station_id: l'identifiant de la station d'intérêt
* \param num_ligne: le numéro de la ligne d'intérêt
* \return un vecteur contenant des pointeurs vers les voyages trouvés
* \exception logic_error si la station est inexistante
* \exception logic_error si la ligne est inexistante
*/
vector<Voyage*> Gestionnaire::trouver_voyages(int station_id, string num_ligne)
{
	if (!bus_existe(num_ligne))
		throw logic_error("Il n’existe pas de ligne ayant ce numéro");
	if (!station_existe(station_id))
		throw logic_error("Il n’existe pas de station ayant cet identifiant");
	vector<Voyage*> voyages;
	Station station = getStation(station_id);
	vector<Voyage*> voyagesDeLaStation = station.getVoyagesPassants();
	for (unsigned int i = 0; i < voyagesDeLaStation.size(); i++)
	{
		if (voyagesDeLaStation[i]->getLigne()->getNumero() == num_ligne)
		{
			voyages.push_back(voyagesDeLaStation[i]);
		}
	}
	return voyages;
}

/*!
 * \brief Permet d'obtenir les destinations des voyages d'une ligne s’arrêtant à une station.
 * Notez qu'une ligne de bus ne peut pas avoir plus de deux destinations possibles: une pour
 l'aller et l'autre pour le retour.
 * Dans le cas de certains bus (ex: couche-tard), une seule destination est possible.
 * \param num_ligne: numéro de la ligne d'intérêt
 * \param station_id: numéro de la station d'intérêt
 * \return Une paire de chaîne de caractères.
 * Si le bus ne passe pas par la station, alors une paire de chaîne vide est retournée. \n
 * Sinon Si le bus a deux destinations possibles les deux éléments de la paire doivent être
 différents de la chaîne vide.
 * Si le bus a une seule destination possible, le dernier élément de la paire seulement est
 égal à une chaîne vide.
 *
 */
pair<string, string> Gestionnaire::get_bus_destinations(int station_id, string num_ligne)
{
	pair<string, string> dests { };
	dests.first = "";
	dests.second = "";
	if (!bus_existe(num_ligne) || !station_existe(station_id))
		return dests;
	Station station = getStation(station_id);
	vector<Voyage*> voyagesDeLaStation = station.getVoyagesPassants();
	for (unsigned int i = 0; i < voyagesDeLaStation.size(); i++)
	{
		if (voyagesDeLaStation[i]->getLigne()->getNumero() == num_ligne)
		{
			dests = getLigne(num_ligne).getDestinations();
		}
	}
	if (dests.first.empty() || dests.first == " " || dests.first == "  ")
	{
		dests.first = dests.second;
		dests.second = "";
	}
	if (dests.first.empty() || dests.first == " " || dests.first == "  ")
	{
		dests.first = "";
	}
	return dests;
}

struct comparerStationsEnvironnantes
{
    inline bool operator() (const pair<double, Station*>& p_station1, const pair<double, Station*>& p_station2)
    {
        return (p_station1.first < p_station2.first);
    }
};

/*
* \brief Trouver des stations environnantes étant donnée une coordonnée gps et un rayon
* \param coord: Coordonnée gps d'intérêt
* \param rayon: cette distance défini la circonférence a l'intérieure de laquelle on se trouve
les stations que l'on cherche
* \return un vecteur de paires (distance, pointeur vers une station) trié par distance
*/
vector<pair<double, Station*>> Gestionnaire::trouver_stations_environnantes(Coordonnees coord, double rayon)
{

	vector<pair<double, Station*>> vectResult;

	for(auto i : m_stations)
	{
		double distance = abs(coord - i.second.getCoords());

		if (distance <= rayon)
		{
			vectResult.push_back(make_pair(distance, &(m_stations.at(i.second.getId()))));
		}
	}

	sort(vectResult.begin(), vectResult.end());

	return vectResult;
}

/*!
* \brief trouver l'horaire d'un bus à une station
* \param date: la date d'intérêt
* \param heure: l'heure à partir de laquelle on veut l'horaire
* \param numero_ligne: numéro de la ligne dont on cherche l'horaire
* \param station_id: l'identifiant de la station où on veut connaitre l'horaire de passage du
bus
* \param destination: permet de spécifier dans quelle direction on veut l'horaire.
* Ceci est pertinent car à certaines stations, la même ligne de bus peut passer dans les deux
sens.
* \return un vecteur contenant les heures d'arrivée (en ordre croissant) du bus à la station
d'intérêt
* \exception logic_error si la station est inexistante
* \exception logic_error si la ligne est inexistante
*/
vector<Heure> Gestionnaire::trouver_horaire(Date date, Heure heure, string
numero_ligne, int station_id, string destination)
{
	vector<Heure> horaire;
	if (!bus_existe(numero_ligne))
		throw logic_error("Il n’existe pas de ligne ayant ce numéro");
	if (!station_existe(station_id))
		throw logic_error("Il n’existe pas de station ayant cet identifiant");
	if (!date_est_prise_en_charge(date))
		return horaire;

	string dateString = to_string(date.getAn()) + string(2 - to_string(date.getMois()).length(), '0').append(to_string(date.getMois())) + string(2 - to_string(date.getJour()).length(), '0').append(to_string(date.getJour()));
	vector<Voyage*> voyagesCeJourLa = m_voyages_date.at(dateString);

	Station station = getStation(station_id);
	Ligne ligne = getLigne(numero_ligne);
	for (unsigned int i = 0; i < voyagesCeJourLa.size(); i++)
	{
		if (voyagesCeJourLa[i]->getLigne()->getId() == ligne.getId())
		{
			if (voyagesCeJourLa[i]->getDestination() == destination)
			{
				vector<Arret> arrets = voyagesCeJourLa[i]->getArrets();
				for (unsigned int j = 0; j < arrets.size(); j++)
				{
					if (arrets[j].getHeureArrivee() > heure)
					{
						if (arrets[j].getStationId() == station_id)
						{
							horaire.push_back(arrets[j].getHeureArrivee());
						}
					}
				}
			}
		}
	}
	return horaire;
}

/*!
* \brief initialiser ou réinitialiser l'attribut m_reseau en fonction des paramètres.
* La date et l'interval de temps spécifié par l'utilisateur servent à trouver les arcs empruntés
par les bus dans le réseau.
* Les coordonnées de départ et de destination servent à ajouter des stations fictives ayant
respectivement les numéros 0 et 1.
La dist_de_marche sert à ajouter les arcs entre ces stations fictives et toutes les autres
stations dans un rayon de dist_de_marche.
* La dist_transfert permet d'ajouter des arcs de transfert entre les stations qui sont à une
distance l'une de l'autre inférieure à dist_transfert
* \param date: la date d'intérêt
* \param heure_depart: l'heure de début.
* \param heure_fin: l'heure de fin.
* \param depart: coordonnées gps du point de départ du déplacement pour lequel on
initialise le réseau
* \param dest: coordonnées gps du point de d'arrivée du déplacement pour lequel on
initialise le réseau
* \param dist_de_marche: permet de spécifier qu’on ne veut pas marcher plus de cette
distance avant de prendre le bus à partir du point de départ, ou pour se rendre au point de
destination à partir de la sortie du bus.
7
* \param dist_transfert: distance maximale de marche pour un transfert de bus
*/
void Gestionnaire::initialiser_reseau(Date date, Heure heure_depart, Heure heure_fin,
Coordonnees depart, Coordonnees dest, double dist_de_marche, double dist_transfert)
{
	m_reseau = Reseau();
	bool considererDepart = (depart.getLatitude() != -1 && depart.getLongitude() != -1);
	bool considererArrivee = (dest.getLatitude() != -1 && dest.getLongitude() != -1);
	if (considererDepart)
	{
		m_reseau.ajouterSommet(num_depart);
	}
	if (considererArrivee)
	{
		m_reseau.ajouterSommet(num_dest);
	}
	if (considererArrivee && considererDepart)
	{
		double distanceDepartArrivee = abs(depart - dest);
		if (distanceDepartArrivee < dist_de_marche)
		{
			double tempsSec = distanceDepartArrivee / vitesse_de_marche * 60 * 60;
			m_reseau.ajouterArc(num_depart, num_dest, tempsSec, (int)MoyenDeplacement::PIEDS);
		}
	}

	for (auto i : m_stations)
	{
		m_reseau.ajouterSommet(i.first);
		if (considererDepart)
		{
			double distance1 = abs(depart - i.second.getCoords());
			if (distance1 < dist_de_marche)
			{
				double tempsSec = distance1 / vitesse_de_marche * 60 * 60;
				m_reseau.ajouterArc(num_depart, i.first, tempsSec, (int)MoyenDeplacement::PIEDS);
			}
		}
		if (considererArrivee)
		{
			double distance2 = abs(i.second.getCoords() - dest);
			if (distance2 < dist_de_marche)
			{
				double tempsSec = distance2 / vitesse_de_marche * 60 * 60;
				m_reseau.ajouterArc(i.first, num_dest, tempsSec, (int)MoyenDeplacement::PIEDS);
			}
		}
	}
	if (dist_transfert > 0)
	{
		for (auto i : m_stations)
		{
			for (auto j : m_stations)
			{
				if (i.first != j.first)
				{
					if (i.first == 1515 && j.first == 1787)
						cout << "now" << endl;
					double distance = abs(i.second.distance(j.second));
					if (distance < dist_transfert)
					{
						double tempsSec = distance / vitesse_de_marche * 60 * 60;
						m_reseau.ajouterArc(i.first, j.first, tempsSec, (int)MoyenDeplacement::PIEDS);
					}
				}
			}
		}
	}

	if (!date_est_prise_en_charge(date))
		return;

	string dateString = to_string(date.getAn()) + string(2 - to_string(date.getMois()).length(), '0').append(to_string(date.getMois())) + string(2 - to_string(date.getJour()).length(), '0').append(to_string(date.getJour()));
	vector<Voyage*> voyagesCeJourLa = m_voyages_date.at(dateString);

	for (unsigned int i = 0; i < voyagesCeJourLa.size(); i++)
	{
		//cout << voyagesCeJourLa[i]->getLigne()->getNumero() << endl;;
		if ((voyagesCeJourLa[i]->getLigne()->getNumero() == "800" || voyagesCeJourLa[i]->getLigne()->getNumero() == "801") && voyagesCeJourLa[i]->getHeureDepart() > heure_depart)
		{
			cout << "normal: " << i << " en direction de " << voyagesCeJourLa[i]->getDestination() << " à " << voyagesCeJourLa[i]->getHeureDepart() << endl;
		}
	}

	for (unsigned int i = 0; i < voyagesCeJourLa.size(); i++)
	{
		vector<Arret> arrets = voyagesCeJourLa[i]->getArrets();
		for (unsigned int j = 1; j < arrets.size(); j++)
		{
			int Id1 = arrets[j - 1].getStationId();
			int Id2 = arrets[j].getStationId();
			if (arrets[j - 1].getHeureDepart() > heure_depart && arrets[j].getHeureArrivee() < heure_fin)
			{
				if ((voyagesCeJourLa[i]->getLigne()->getNumero() == "800" || voyagesCeJourLa[i]->getLigne()->getNumero() == "801") && voyagesCeJourLa[i]->getHeureDepart() > heure_depart)
				{
					cout << "special: " << i << " en direction de " << voyagesCeJourLa[i]->getDestination() << " à " << voyagesCeJourLa[i]->getHeureDepart() << endl;
					cout << "Arrets: " << Id1 << " - " << Id2 << endl;
				}
				//int distance = abs(m_stations.at(arrets[j].getStationId()).distance(m_stations.at(arrets[j - 1].getStationId())));
				int temps = (arrets[j].getHeureArrivee() - arrets[j - 1].getHeureDepart());
				if (m_reseau.arcExiste(Id1, Id2))
				{
					int temps2 = m_reseau.getCoutArc(Id1, Id2);
					if (temps < temps2)
					{
						m_reseau.majCoutArc(Id1, Id2, temps);
					}
				}
				else
				{
					m_reseau.ajouterArc(Id1, Id2, temps, (int)MoyenDeplacement::BUS);
				}
			}
		}
	}
}



/*!
* \brief permet de déterminer si le réseau de transport est fortement connexe.
* \param date: la date d'intérêt
* \param heure: l'heure à partir de laquelle on veut faire le calcul
* \param[in] considerer_transfert: indique si vous devez considérer ou pas les arcs de
transfert dans votre calcul
* \return true ssi à partir de n'importe quelle station du réseau on peut atteindre n'importe
quelle autre.
*/
bool Gestionnaire::reseau_est_fortement_connexe(Date date, Heure heure_deb, bool
considerer_transfert)
{
	double distance_transfert = distance_max_transfert;
	double distance_initiale = distance_max_initiale;
	if (!considerer_transfert)
	{
		distance_transfert = 0;
	}
	Heure maxHeure = Heure { 29, 59, 59 };
	initialiser_reseau(date, heure_deb, maxHeure, Coordonnees { -1, -1 }, Coordonnees { -1, -1 }, distance_initiale, distance_transfert);
	return m_reseau.estFortementConnexe();
}

/*!
* \brief permet de déterminer les composantes fortement connexes du réseau de transport.
* \param date: la date d'intérêt
* \param heure: l'heure à partir de laquelle on veut faire le calcul
* \param[in] considerer_transfert: indique si vous devez considérer ou pas les arcs de
transfert dans votre calcul
* \param[out] composantes: vecteur pour stocker les différentes composantes fortement
connexes.
*/
void Gestionnaire::composantes_fortement_connexes(Date date, Heure heure_deb,
		vector<vector<unsigned int> >& composantes, bool considerer_transfert)
{
	double distance_transfert = distance_max_transfert;
	double distance_initiale = distance_max_initiale;
	if (!considerer_transfert)
	{
		distance_transfert = 0;
	}
	Heure maxHeure = Heure { 29, 59, 59 };
	initialiser_reseau(date, heure_deb, maxHeure, Coordonnees { -1, -1 }, Coordonnees { -1, -1 }, distance_initiale, distance_transfert);
	m_reseau.getComposantesFortementConnexes(composantes);
}

/*!
* \brief Trouver le plus court chemin en autobus pour aller d'un point A vers un point B
dans l’interval de temps défini par interval_planification_en_secondes
* à partir d'une heure de départ et pour une date donnée
* Pour ce faire, il faut initialiser le réseau, puis faire appel à ses routines de plus courts
chemin
* \param date: la date de planification
* \param heure_depart: l'heure de début de planification
* \param depart: coordonnées gps du point de départ de votre déplacement
* \param destination: coordonnées gps du point de d'arrivée de votre déplacement
* \return Un vecteur contenant les stations du chemin trouvé, le vecteur est vide si aucun
chemin n’est trouvé
*/
vector<unsigned int> Gestionnaire::plus_court_chemin(Date date, Heure heure_depart,
Coordonnees depart, Coordonnees destination)
{
	double distance_transfert = distance_max_transfert;
	double distance_initiale = distance_max_initiale;
	Heure maxHeure = Heure { 29, 59, 59 };
	initialiser_reseau(date, heure_depart, maxHeure, depart, destination, distance_initiale, distance_transfert);
	cout << "0: " << m_reseau.getCoutArc(0, 1515) << endl;
	cout << "1515: " << m_reseau.getCoutArc(1515, 1787) << endl;
	cout << "1787: " << m_reseau.getCoutArc(1787, 1776) << endl;
	cout << "1776: " << m_reseau.getCoutArc(1776, 1790) << endl;
	cout << "1790: " << m_reseau.getCoutArc(1790, 1791) << endl;
	cout << "1791: " << m_reseau.getCoutArc(1791, 2000) << endl;
	cout << "2000: " << m_reseau.getCoutArc(2000, 2001) << endl;
	cout << "2001: " << m_reseau.getCoutArc(2001, 2003) << endl;
	cout << "2003: " << m_reseau.getCoutArc(2003, 2006) << endl;
	cout << "2006: " << m_reseau.getCoutArc(2006, 1434) << endl;
	cout << "1434: " << m_reseau.getCoutArc(1434, 2007) << endl;
	cout << "2007: " << m_reseau.getCoutArc(2007, 4144) << endl;
	cout << "4144: " << m_reseau.getCoutArc(4144, 3099) << endl;
	cout << "3099: " << m_reseau.getCoutArc(3099, 1) << endl;
	vector<unsigned int> resultat;
	m_reseau.dijkstra(num_depart, num_dest, resultat);
	return resultat;
}
