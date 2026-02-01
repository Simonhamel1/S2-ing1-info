#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

float moyenne(const vector<int>& tab){
    int somme = 0;
    for(size_t i = 0; i < tab.size(); i++){
        somme += tab[i];
    }
    return static_cast<float>(somme) / tab.size();
}

int main(){
    vector<int> tableau(100, rand() % 100);
    tableau.push_back(42);
    cout << "Taille du tableau : " << tableau.size() << endl;
    cout << "Dernier element : " << tableau.back() << endl;
    float result = moyenne(tableau);
    cout << "Moyenne des elements : " << result << endl;
    return 0;
}