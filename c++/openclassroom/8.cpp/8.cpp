#include "8.hpp"

void afficherTableau(vector<int> tableau) {
    for (size_t i = 0; i < tableau.size(); ++i) {
        cout << "Element " << i << ": " << tableau[i] << endl;
    }
}

void afficherTableau(vector<int>::const_iterator begin, vector<int>::const_iterator end) {
    size_t idx = 0;
    for (auto it = begin; it != end; ++it, ++idx) {
        cout << "Element " << idx << ": " << *it << endl;
    }
}

int moyenneTableau(vector<int> tableau) {
    int somme = 0;
    for (size_t i = 0; i < tableau.size(); ++i) {
        somme += tableau[i];
    }
    return somme / tableau.size();
}

int maximumTableau(vector<int> tableau) {
    int max = tableau[0];
    for (size_t i = 1; i < tableau.size(); ++i) {
        if (tableau[i] > max) {
            max = tableau[i];
        }
    }
    return max;
}

int minimumTableau(vector<int> tableau) {
    int min = tableau[0];
    for (size_t i = 1; i < tableau.size(); ++i) {
        if (tableau[i] < min) {
            min = tableau[i];
        }
    }
    return min;
}

void trierTableau(vector<int>& tableau) {
    sort(tableau.begin(), tableau.end());
}

std::chrono::steady_clock::time_point timenow() {
    return std::chrono::steady_clock::now();
}