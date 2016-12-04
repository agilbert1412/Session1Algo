#include <iostream>
#include "coordonnees.h"
#include "reseau.h"
#include <vector>
#include "investigation.h"

using namespace std;



int main() {
    GestionnaireInvestigation rtc("googletransit");

    cout << "Temps moyen de dijsktra " << rtc.tester_n_paires_dijsktra(1000) << endl;

    cout << "Temps moyen de bellman " << rtc.tester_n_paires_bellman(1000) << endl;
    return 0;
}

2858 2876 2886 2887 2929 2764