#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int* return_table(int tab[]){
    for(int i=0; i<5; i++){
        cout << "Element " << i << " : " << tab[i] << endl;
        tab[i] += 10;
    }
    return tab;
}

int main(){
    int my_table[5] = {1,2,3,4,5};
    int* my_table_ref = return_table(my_table);
    int* dernier_element;
    cout << "la taille du tableau est de " << size(my_table) << endl;
    cout << "Table after function call:" << endl;
    for(int i=0; i<5; i++){
        if(i == size(my_table)-1){
            cout << "Element " << i << " : " << my_table_ref[i] << endl;
            dernier_element = &my_table_ref[i];
        }
        else {
            cout << "Element " << i << " : " << my_table_ref[i] << endl;
        }
    }
    cout << "dernier element est :" << *dernier_element << endl;
    return 0;
}

// int main(){
//     int a = 5;
//     int* pA = &a;
//     cout << "Value of a: " << a << endl;
//     cout << "Address of a: " << pA << endl;
// }