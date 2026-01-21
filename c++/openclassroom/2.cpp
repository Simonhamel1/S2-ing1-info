#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void affichage_style(int taille){
    for(int i = 0; i < taille; i++){
        for(int j = 0; j < taille; j++){
            cout << alphabet[rand() % alphabet.size()] << " ";           
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    int taille(15);
    affichage_style(taille);

    cout << &alphabet << endl;
    cout << alphabet << endl;

    return 0;
}
