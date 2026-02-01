#include <fstream>
#include <random>
#include <iostream>

int main() {
    std::ofstream file("fichier.csv");
    
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }
    
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, 1000000);
    
    for (int i = 0; i < 100000000; ++i) {
        // 100 000 000 000 lines may take a very long time and require significant disk space.
        file << dis(gen) << "\n";
    }
    
    file.close();
    std::cout << "File written successfully\n";
    return 0;
}