#include <iostream>
#include <vector>
#include <algorithm> // sort, reverse, count, find, clamp, all_of, any_of
#include <numeric>   // accumulate, iota
#include <utility>   // pair
#include <string>    // to_string

// Cette ligne permet d'éviter d'écrire "std::" partout
using namespace std;

// Petit utilitaire pour afficher proprement les vecteurs
void afficherVecteur(const string& titre, const vector<int>& v) {
    cout << titre << ": { ";
    for (int x : v) { 
        cout << x << " ";
    }
    cout << "}" << endl;
}

// Fonction helper pour la démo des Structured Bindings
pair<int, int> getCoords() {
    return {10, 20};
}

int main() {
    cout << "=== DEMO C++ MODERNE & STL ===" << endl << endl;

    // ====================================================
    // 1. LES "LIFE SAVERS" (Tri, Inverse, Compte)
    // ====================================================
    cout << "--- 1. Life Savers ---" << endl;
    
    vector<int> v = {4, 2, 9, 1, 3, 3};
    afficherVecteur("Original", v);

    // sort : Trie en une ligne
    sort(v.begin(), v.end());
    afficherVecteur("Apres sort", v);

    // reverse : Inverse l'ordre
    reverse(v.begin(), v.end());
    afficherVecteur("Apres reverse", v);

    // count : Compte les occurrences
    int nbTrois = count(v.begin(), v.end(), 3);
    cout << "Nombre de '3' dans le vecteur : " << nbTrois << endl << endl;


    // ====================================================
    // 2. LES MATHEMATIQUES "STYLEES"
    // ====================================================
    cout << "--- 2. Maths Stylees ---" << endl;

    // clamp (C++17) : Force une valeur entre min et max
    int val = 150;
    // Note : Si votre compilateur est trop vieux, clamp plantera ici.
    int safeVal = clamp(val, 0, 100); 
    cout << "clamp(150, 0, 100) -> " << safeVal << endl;

    // accumulate : Somme totale
    int somme = accumulate(v.begin(), v.end(), 0);
    cout << "accumulate (Somme du vecteur) : " << somme << endl;

    // iota : Remplissage automatique
    vector<int> indices(5);
    iota(indices.begin(), indices.end(), 0); // Remplit avec 0, 1, 2, 3, 4
    afficherVecteur("iota (indices)", indices);
    cout << endl;


    // ====================================================
    // 3. RECHERCHE ET VERIFICATION (Booleens)
    // ====================================================
    cout << "--- 3. Recherche et Verification ---" << endl;

    // all_of : Tout le monde respecte la condition ?
    bool tousPositifs = all_of(v.begin(), v.end(), [](int i){ return i > 0; });
    cout << "Tous positifs ? " << (tousPositifs ? "Oui" : "Non") << endl;

    // any_of : Au moins un respecte la condition ?
    bool existePair = any_of(v.begin(), v.end(), [](int i){ return i % 2 == 0; });
    cout << "Existe-t-il un nombre pair ? " << (existePair ? "Oui" : "Non") << endl;

    // find : Trouver un élément spécifique
    int cible = 9;
    auto it = find(v.begin(), v.end(), cible);
    if (it != v.end()) {
        cout << "find : Element " << cible << " trouve !" << endl;
    } else {
        cout << "find : Element " << cible << " non trouve." << endl;
    }
    cout << endl;


    // ====================================================
    // 4. LE "SUCRE SYNTAXIQUE" (C++17)
    // ====================================================
    cout << "--- 4. Modern C++ Features ---" << endl;

    // Structured Bindings : Déballage de paire
    auto [x, y] = getCoords(); 
    
    cout << "Structured Bindings : x=" << x << ", y=" << y << endl;
    
    // to_string 
    string texte = "Coordonnees : " + to_string(x) + "/" + to_string(y);
    cout << "to_string result : " << texte << endl;

    // PAUSE POUR VOIR LE RESULTAT
    cout << "\nAppuyez sur Entree pour quitter...";
    cin.get(); 

    return 0;
}