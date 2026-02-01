#include <iostream>
#include "8.hpp"

int main() {
    srand(time(NULL));
    auto time_start = timenow();
    vector<int> tableau;
    for (size_t i = 0; i < 100000000; ++i) {
        tableau.push_back(rand() % 100); // Remplir avec des valeurs aléatoires entre 0 et 99
    }

    cout << "Tableau initial:" << endl;
    afficherTableau(tableau.begin(), tableau.begin() + 10); // Afficher les 10 premiers éléments

    cout << "\nMinimum: " << minimumTableau(tableau) << endl;
    cout << "Moyenne: " << moyenneTableau(tableau) << endl;
    cout << "Maximum: " << maximumTableau(tableau) << endl;

    trierTableau(tableau);
    cout << "\nTableau trié:" << endl;
    afficherTableau(tableau.begin(), tableau.begin() + 10); // Afficher les 10 premiers éléments

    auto elapsed = std::chrono::duration<double>(timenow() - time_start).count();
    cout << "\nLe temps d'exécution est de : " << elapsed << " secondes." << endl;
    return 0;
}