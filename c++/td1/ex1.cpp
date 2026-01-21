#include <iostream>
#include <cstdlib>

using namespace std;

int factoriel(int nombre){
    if (nombre == 2){
        return nombre;
    }
    else{ 
        nombre *= factoriel(nombre-1);
    }
}

int main(){
    int nombre(15);
    cout << "la factoriel de " << nombre << " est de " << factoriel(nombre) << endl;
    return 0;
}