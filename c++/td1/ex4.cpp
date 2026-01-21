#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iomanip>

using namespace std;

int appartenance(){
    float x = (rand() / (float)RAND_MAX) * 2 - 1;
    float y = (rand() / (float)RAND_MAX) * 2 - 1;
    if (sqrt(pow(x,2) + pow(y,2)) < 1){
        return 1;
    }
    return 0;
}

double approximation_pi(int precision){
    float pi(0);
    for (int i=0; i<precision ;i++){
        pi += appartenance();
    }
    float estimation_pi = pi/precision * 4;
    return estimation_pi;
}

int main(){
    srand(time(NULL));
    int precision(1000000);

    float pi_approx = approximation_pi(precision);
    cout << fixed << setprecision(8);
    cout << "Approximation of Pi with precision 8 decimal is " << pi_approx << endl;

    return 0;
}