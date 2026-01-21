#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int jeu_hasard(int nombre,int nombre_demander){
    if (nombre_demander == nombre){
        cout << "t'es trop fort(e) bravo " << endl;
        return 0;
    }
    else if (nombre_demander < nombre){
        cout << "donner un nombre a nouveau entre " << nombre_demander << " et 20 :"; 
        cin >> nombre_demander;
        jeu_hasard(nombre, nombre_demander);
    }
    else {
        cout << "donner un nombre a nouveau entre 0 et " << nombre_demander << " : ";
        cin >> nombre_demander;
        jeu_hasard(nombre, nombre_demander);
    }
}


int main() {
    srand(time(NULL));   
    cout << "c'est parti pour jouer" << endl ;
    int nombre = rand()%20;
    int nombre_demander(0);
    cout << "Entrez un nombre entre 0 et 20 : ";
    cin >> nombre_demander;
    jeu_hasard(nombre, nombre_demander);
    return 0; 
}