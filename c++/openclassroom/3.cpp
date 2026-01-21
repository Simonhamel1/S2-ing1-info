#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void echanger(int a, int b){
    cout << "(a,b) : " << "(" << a << "," << b << ")" << endl;
    swap(a,b);
    cout << "(a,b) : " << "(" <<a << "," << b << ")" << endl;
}

int main(){
    string str;
    cout << "Enter a string: ";
    getline(cin, str);
    string& ref = str;
    cout << "Renter encore a string: ";
    getline(cin, ref);
    cout << "le string renter est " << str << endl ;
    cout << "le string rentrer (ref) " << ref << endl;
    
    echanger(5,12);

    return 0;
}