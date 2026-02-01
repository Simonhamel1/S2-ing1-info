#ifndef HPP_8
#define HPP_8

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;

// Temps courant en steady_clock
std::chrono::steady_clock::time_point timenow();

// Affiche tout le tableau
void afficherTableau(vector<int> tableau);

// Affiche une tranche [begin, end)
void afficherTableau(vector<int>::const_iterator begin, vector<int>::const_iterator end);

int moyenneTableau(vector<int> tableau);
int maximumTableau(vector<int> tableau);
int minimumTableau(vector<int> tableau);
void trierTableau(vector<int>& tableau);

#endif // HPP_8