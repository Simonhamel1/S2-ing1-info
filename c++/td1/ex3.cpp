#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool estPremier(int nombre){
    for (int i = 2; i<nombre-1; i++){
        if ((nombre % i)==0){
            return false;
        }
    }
    return true;
}

int main(){
    cout << "donner un nombre : ";
    int nombre;
    cin >> nombre;
    cout << "est ce que le chiffre est premier ? " << (estPremier(nombre) ? "oui" : "non") << endl;
    return 0;
}