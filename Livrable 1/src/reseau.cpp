#include "reseau.h"

using namespace std;

/*!
 * \brief constructeur par défaut d'un réseau. Crée un réseau vide.
 *
 */
Reseau::Reseau(): nbSommets(0), nbArcs(0) {}


/*!
 * \brief Trouver le nombre de sommet dans le graphe en O(1)
 * \return nombre de sommet du graphe
 */
int Reseau::nombreSommets() const
{
    return nbSommets;
}

/*!
 * \brief Trouver le nombre d'arcs dans le graphe en O(1)
 * \return nombre d'arcs du graphe
 */
int Reseau::nombreArcs() const
{
	return nbArcs;
}

/*!
 * \brief Déterminer si le graphe est vide ou pas en O(1)
 * \return True ssi le graphe est vide
 */
bool Reseau::estVide() const
{
    return nbSommets == 0;
}

/*!
 * \brief Permet de déterminer si un sommet existe ou pas
 * \param[in] numero: numéro du sommet à valider
 * \return true ssi le sommet existe
 */
bool Reseau::sommetExiste(unsigned int numero) const
{
    return m_arcs.count(numero) != 0;
}

/*!
 * \brief Permet de déterminer si un arc existe ou pas
 * \param[in] numOrigine: numéro du sommet où l'arc part
 * \param[in] numDest: numéro du sommet où l'arc arrive
 * \exception logic_error si un des deux sommet n'existe pas
 * \return true ssi l'arc existe
 */
bool Reseau::arcExiste(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error)
{
    if (!(sommetExiste(numOrigine) && sommetExiste(numDest))) {
    	cout << "Sommets n'existant pas: " << numOrigine << ", " << numDest << endl;
    	throw std::logic_error ("arcExiste: Un des sommets n'existe pas!");
    }
	//cout << "Sommets existants: " << numOrigine << ", " << numDest << endl;
    return m_arcs.find(numOrigine)->second.count(numDest) != 0;
}

/*!
 * \brief Permet d'ajouter un sommet dans le réseau
 * \param[in] p_numero: numéro du sommet à ajouter
 * \exception logic_error si un sommet ayant le même numéro est déjà présent
 * \post le graphe contient un sommet de plus
 */
void Reseau::ajouterSommet(unsigned int p_numero) throw (std::logic_error)
{
    if (sommetExiste(p_numero)) throw std::logic_error("ajouterSommet: Un sommet avec le numero existe!") ;
    m_arcs[p_numero] = liste_arcs();
    nbSommets++;
}

/*!
 * \brief Permet d'ajouter un arc au réseau
 * \param[in] numOrigine: numéro du sommet destiné à émettre l'arc
 * \param[in] numDest: numéro du sommet destiné à recevoir l'arc
 * \param[in] cout: le coût ou poids de l'arc à ajouter
 * \param[in] type: type de l'arc à ajouter
 * \exception logic_error si un des sommets n'existe pas
 * \exception logic_error si l'arc est déjà présent
 * \post le graphe contient un arc de plus entre l'origine et la destination
 */
void Reseau::ajouterArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout, unsigned int type)
throw(std::logic_error)
{
    if ( arcExiste(numOrigine, numDest) ) throw std::logic_error ("ajouterArc: arc déja existant");
    m_arcs[numOrigine].insert({numDest, {cout, type} });
    nbArcs++;
}

/*!
 * \brief Permet d'enlever un sommet dans du réseau, ainsi que tous ces arcs entrants et sortants.
 * \param[in] numero: numéro du sommet à enlever
 * \exception logic_error si aucun sommet ayant le même numéro est déjà présent
 * \post le graphe contient un sommet de moins et peut être plusieurs arcs de moins.
 */
void Reseau::enleverSommet(unsigned int numero) throw (std::logic_error)
{
    if (!sommetExiste(numero)) throw std::logic_error("enleverSommet: le sommet n'existe pas");
    unsigned int origine;

    for(auto kv: m_arcs){
    	origine = kv.first;
        if(arcExiste(origine, numero)){enleverArc(origine, numero);}
    }
    m_arcs.erase(numero);
    nbSommets --;
}

/*!
 * \brief Enlever un arc du réseau
 * \param[in] numOrigine: numéro du sommet supposé émettre l'arc
 * \param[in] numDest: numéro du sommet supposé recevoir l'arc
 * \exception logic_error si un des sommets n'existe pas
 * \exception logic_error si l'arc n'est pas présent dans le graphe
 * \post le graphe contient un arc de moins
 */
void Reseau::enleverArc(unsigned int numOrigine, unsigned int numDest) throw (std::logic_error)
{
    if (!arcExiste(numOrigine, numDest)) throw std::logic_error ("enleverArc: arc non existant");
    m_arcs[numOrigine].erase(numDest);
    nbArcs--;
}

/*!
 * \brief Permet de mettre à jour le coût d'un arc du réseau
 * \param[in] numOrigine: numéro du sommet destiné à émettre l'arc
 * \param[in] numDest: numéro du sommet destiné à recevoir l'arc
 * \param[in] cout: le nouveau coût ou poids de l'arc à mettre à jour
 * \exception logic_error si un des sommets n'existe pas
 * \exception logic_error si l'arc n'est pas déjà présent
 * \post le poids de l'arc a été mis à jour
 */
void Reseau::majCoutArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout) throw (std::logic_error)
{
	if (!arcExiste(numOrigine, numDest)) throw std::logic_error ("majCoutArc: arc non existant");
    m_arcs[numOrigine][numDest].first = cout;
}

/*!
 * \brief Trouver le coût d'un arc du réseau
 * \param[in] numOrigine: numéro du sommet supposé émettre l'arc
 * \param[in] numDest: numéro du sommet supposé recevoir l'arc
 * \exception logic_error si un des sommets n'existe pas
 * \exception logic_error si l'arc n'est pas présent dans le graphe
 * \return le cout de l'arc
 */
int Reseau::getCoutArc(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error){
	if (!arcExiste(numOrigine, numDest) ) throw std::logic_error ("getCoutArc: arc non existant");
    return m_arcs.find(numOrigine)->second.find(numDest)->second.first;
}

/*!
 * \brief Trouver le type d'un arc du réseau
 * \param[in] numOrigine: numéro du sommet supposé émettre l'arc
 * \param[in] numDest: numéro du sommet supposé recevoir l'arc
 * \exception logic_error si un des sommets n'existe pas
 * \exception logic_error si l'arc n'est pas présent dans le graphe
 * \return le type de l'arc
 */
int Reseau::getTypeArc(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error){
	if (!arcExiste(numOrigine, numDest) ) throw std::logic_error ("getTypeArc: arc non existant");
    return m_arcs.find(numOrigine)->second.find(numDest)->second.second;
}

/*!
 * \brief Algorithme de Dijkstra en O(n*n)  permettant de trouver le plus court chemin entre deux noeuds du graphe
 * \param[in] numOrigine: le sommet d'où le chemin part
 * \param[in] numDest: le sommet que le chemin est censé atteindre
 * \param[out] chemin:  le vecteur contenant le chemin trouvé s'il y en existe un
 * \exception logic_error si un des sommets n'existe pas
 * \return la longueur du chemin (= numeric_limits<int>::max() si p_destination n'est pas atteignable)
 */
int Reseau::dijkstra(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin) throw (std::logic_error)
{
    if ( !sommetExiste(numOrigine) || !sommetExiste(numDest) ) throw std::logic_error ("dijkstra: Un des sommets n'existe pas!");
    std::unordered_map<unsigned int, int> distances;
    std::unordered_map<unsigned int, int> predecesseurs;
    std::unordered_set<unsigned int> Q;
    unsigned int max_poids = std::numeric_limits<int>::max();
    unsigned int noeud_min;
    int temp;

    for(auto kv: m_arcs){
    	distances[kv.first] = max_poids;
    	predecesseurs[kv.first] = -1;
    	Q.insert(kv.first);
    }

    distances[numOrigine] = 0;
    for(int i = 0; i < nbSommets; i++){
    	noeud_min = *(Q.begin());
    	for(auto noeud: Q){
    		if(distances[noeud] < distances[noeud_min]){
    			noeud_min = noeud;
    		}
    	}
    	Q.erase(noeud_min);
    	if(noeud_min == numDest){
    		break;
    	}

    	for(auto voisin: m_arcs[noeud_min]){
    		if(Q.count(voisin.first) != 0){
    			temp = voisin.second.first + distances[noeud_min];
    			if(temp < distances[voisin.first]) {
    				distances[voisin.first] = temp;
    				predecesseurs[voisin.first] = noeud_min;
    			}
    		}
    	}
    }

    chemin.clear();
    if(predecesseurs[numDest] != -1){
    	std::vector<unsigned int> chemin_inverse;
		int courant = numDest;
		while(courant!=-1){
			chemin_inverse.push_back(courant);
			courant = predecesseurs[courant];
		}
		for(int i=chemin_inverse.size() -1; i >= 0; i--){
			chemin.push_back(chemin_inverse[i]);
		}
    }
    return distances[numDest];
}

/*!
 * \brief Algorithme de Dijkstra en O(nlogn)  permettant de trouver le plus court chemin entre deux noeuds du graphe
 * \param[in] numOrigine: le sommet d'où le chemin part
 * \param[in] numDest: le sommet que le chemin est censé atteindre
 * \param[out] chemin:  le vecteur contenant le chemin trouvé s'il y en existe un
 * \exception logic_error si un des sommets n'existe pas
 * \return la longueur du chemin (= numeric_limits<int>::max() si p_destination n'est pas atteignable)
 */
int Reseau::meilleurPlusCourtChemin(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin) throw (std::logic_error)
{
    //TODO À completer
	return 0;
}

/*!
 * \brief Algorithme de BellmanFord en O(n*m)  permettant de trouver le plus court chemin entre deux noeuds du graphe
 * \param[in] numOrigine: le sommet d'où le chemin part
 * \param[in] numDest: le sommet que le chemin est censé atteindre
 * \param[out] chemin:  le vecteur contenant le chemin trouvé s'il y en existe un
 * \exception logic_error si un des sommets n'existe pas
 * \return la longueur du chemin (= numeric_limits<int>::max() si p_destination n'est pas atteignable)
 */
int Reseau::bellmanFord(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin) throw (std::logic_error)
{
    if ( !sommetExiste(numOrigine) || !sommetExiste(numDest) ) throw std::logic_error ("bellmanFord: Un des sommets n'existe pas!");

    unsigned int noeud_courant;
    int temp;
    std::unordered_map<unsigned int, int> distances;
    std::unordered_map<unsigned int, int> predecesseurs;
    int max_poids = std::numeric_limits<int>::max();
    for(auto kv: m_arcs){
    	distances[kv.first] = max_poids;
    	predecesseurs[kv.first] = -1;
    }
    bool estInstable = true;

    distances[numOrigine] = 0;
    for(int i = 1; (i <  nbSommets) && estInstable ; i++){
    	estInstable = false;
    	for(auto kv: m_arcs){
    		noeud_courant = kv.first;
    		if(distances[noeud_courant] < max_poids){
				for(auto voisin: kv.second){
					temp = voisin.second.first + distances[noeud_courant];
					if(temp < distances[voisin.first] && temp >= 0) {
						distances[voisin.first] = temp;
						predecesseurs[voisin.first] = noeud_courant;
						estInstable = true;
					}
				}
    		}
    	}
    }
    chemin.clear();

    if(predecesseurs[numDest] != -1){
    	std::vector<unsigned int> chemin_inverse;
		int courant = numDest;
		int cpt = 0;
		while(courant!=-1){
			chemin_inverse.push_back(courant);
			courant = predecesseurs[courant];
		}

		for(int i=chemin_inverse.size() -1; i >= 0; i--){
			chemin.push_back(chemin_inverse[i]);
		}
    }

    return distances[numDest];
}


/*!
 * \brief Algorithme de Floyd-Warshall en Θ(n³)  permettant de trouver le plus court chemin entre deux noeuds du graphe
 * \param[in] numOrigine: le sommet d'où le chemin part
 * \param[in] numDest: le sommet que le chemin est censé atteindre
 * \param[out] chemin:  le vecteur contenant le chemin trouvé s'il y en existe un
 * \exception logic_error si un des sommets n'existe pas
 * \return la longueur du chemin (= numeric_limits<int>::max() si p_destination n'est pas atteignable)
 */
int Reseau::floydwarshall(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin) throw (std::logic_error)
{
    if ( !sommetExiste(numOrigine) || !sommetExiste(numDest) ) throw std::logic_error ("Floyd-Warshall: Un des sommets n'existe pas!");

	unordered_map<unsigned int, unordered_map<unsigned int, int>> D;
	unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>> P;

	int nbIterations = m_arcs.size();

	//cout << "Avant première boucle (" << (nbIterations * nbIterations) << " itérations)" << endl;
	for(auto kv1: m_arcs){
    	unordered_map<unsigned int, int> map1;
    	unordered_map<unsigned int, unsigned int> map2;
    	//cout << "test2: " << kv1.first << endl;
		for(auto kv2: m_arcs){
    		if (arcExiste(kv1.first, kv2.first)) {
    			map1.insert(make_pair(kv2.first, getCoutArc(kv1.first, kv2.first)));
    		} else {
    			map1.insert(make_pair(kv2.first, numeric_limits<int>::max()));
    		}

    		if (kv1.first != kv2.first && map1[kv2.first] != numeric_limits<int>::max()) {
    			map2.insert(make_pair(kv2.first, kv1.first));
    		} else {
    			map2.insert(make_pair(kv2.first, 0));
    		}
    	}
		D.insert(make_pair(kv1.first, map1));
		P.insert(make_pair(kv1.first, map2));
    }

	//cout << "Entre les boucles (" << (nbIterations * nbIterations * nbIterations) << " itérations)" << endl;
	int cpt = 1;
	for(auto kv3: m_arcs){
    	for(auto kv1: m_arcs){
    		for(auto kv2: m_arcs){
    			cpt++;
    			//cout << "Itération " << cpt << " sur " << (nbIterations * nbIterations * nbIterations) << endl;
    			int temp = D[kv1.first][kv3.first] + D[kv3.first][kv2.first];
    			if (temp < D[kv1.first][kv2.first]) {
    				D[kv1.first][kv2.first] = temp;
    				P[kv1.first][kv2.first] = P[kv3.first][kv2.first];
    			}
    		}
    	}
    }

	//cout << "Chemin final" << endl;
    chemin.clear();

    if(P[numOrigine][numDest] != 0){
    	std::vector<unsigned int> chemin_inverse;
		int courant = numDest;
		while(courant != 0){
			chemin_inverse.push_back(courant);
			courant = P[numOrigine][courant];
		}

		for(int i=chemin_inverse.size() -1; i >= 0; i--){
			chemin.push_back(chemin_inverse[i]);
		}
    }

	//cout << "Fini Floyd" << endl;
    return D[numOrigine][numDest];
}

