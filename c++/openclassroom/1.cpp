#include <iostream>

using namespace std;

int ageUtilisateur(15);

int test(){
    int a = 42;
    return a*2;
}

int age_Utilisateur(int age){
    return age + 1;
}

int main(){
    cout << "Hello world!" << " et bienvenue a cergy" << endl;
    cout << "\"" << endl;
    cout << "\\" << endl;
    cout << "The answer is: of test() function is " << test() << endl;
    cout << "Next year, you will be " << age_Utilisateur(ageUtilisateur) << " years old." << endl;
    return 0;
}