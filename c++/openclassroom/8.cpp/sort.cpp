#include <thread>
#include <atomic>
#include "8.hpp"
#include <iostream>

std::atomic<bool> running(true);

void timerThread() {
    auto start = timenow();
    while (running) {
        auto now = timenow();
        cout << "Temps écoulé : "
             << std::chrono::duration<double>(now - start).count()
             << " sec\r" << flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    vector<int> tableau(1000000000);
    // soit 1 billion d'éléments soit 4 Go environ
    for (auto &x : tableau) x = rand() % 100;

    std::thread t(timerThread);

    trierTableau(tableau); // tri long

    running = false;
    t.join();

    cout << "\nTri terminé !" << endl;
}