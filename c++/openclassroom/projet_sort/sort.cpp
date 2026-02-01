#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <execution>
#include <cstring>
#include <chrono>
#include <iomanip>
#include <sys/stat.h>

using namespace std;

// Configuration optimisée pour 16GB RAM / 4 cores
const size_t CHUNK_SIZE = 100'000'000;     // 100M entiers (~400 MB par chunk)
const size_t READ_BUFFER = 2 * 1024 * 1024;    // 2 MB buffer lecture
const size_t WRITE_BUFFER = 2 * 1024 * 1024;   // 2 MB buffer écriture
const size_t MERGE_BUFFER = 512 * 1024;        // 512 KB par fichier en fusion

// Classe pour les logs avec timestamps
class Logger {
    mutex logMutex;
    chrono::high_resolution_clock::time_point startTime;
    
public:
    Logger() : startTime(chrono::high_resolution_clock::now()) {}
    
    template<typename... Args>
    void log(Args... args) {
        lock_guard<mutex> lock(logMutex);
        auto now = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - startTime).count();
        
        cout << "[" << setw(8) << elapsed / 1000.0 << "s] ";
        (cout << ... << args) << endl;
    }
    
    void progress(const string& task, size_t current, size_t total) {
        lock_guard<mutex> lock(logMutex);
        auto now = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - startTime).count();
        
        double percent = (total > 0) ? (100.0 * current / total) : 0;
        cout << "[" << setw(8) << elapsed / 1000.0 << "s] "
             << task << ": " << current << "/" << total 
             << " (" << fixed << setprecision(1) << percent << "%)" << endl;
    }
};

Logger logger;

// Parser ultra-rapide
inline int fastParseInt(const char*& p) {
    int val = 0;
    bool neg = false;
    
    if (*p == '-') {
        neg = true;
        ++p;
    }
    
    while (*p >= '0' && *p <= '9') {
        val = val * 10 + (*p - '0');
        ++p;
    }
    
    return neg ? -val : val;
}

// Obtenir la taille du fichier
size_t getFileSize(const string& filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) == 0) {
        return st.st_size;
    }
    return 0;
}

// Lecture et parsing optimisés
vector<int> readChunkOptimized(ifstream& in, size_t maxSize, size_t& totalBytesRead, size_t fileSize) {
    vector<int> data;
    data.reserve(maxSize);
    
    vector<char> buffer(READ_BUFFER);
    string leftover;
    
    size_t bytesReadThisChunk = 0;
    
    while (data.size() < maxSize && in) {
        in.read(buffer.data(), READ_BUFFER);
        size_t bytesRead = in.gcount();
        
        if (bytesRead == 0) break;
        
        bytesReadThisChunk += bytesRead;
        totalBytesRead += bytesRead;
        
        const char* start = buffer.data();
        const char* end = start + bytesRead;
        const char* p = start;
        
        if (!leftover.empty()) {
            while (p < end && *p != '\n') ++p;
            if (p < end) {
                leftover.append(start, p - start);
                const char* tmp = leftover.c_str();
                data.push_back(fastParseInt(tmp));
                leftover.clear();
                ++p;
            } else {
                leftover.append(start, bytesRead);
                continue;
            }
        }
        
        while (p < end && data.size() < maxSize) {
            const char* lineStart = p;
            while (p < end && *p != '\n') ++p;
            
            if (p < end) {
                data.push_back(fastParseInt(lineStart));
                ++p;
            } else {
                leftover.assign(lineStart, end - lineStart);
            }
        }
    }
    
    if (!leftover.empty() && data.size() < maxSize) {
        const char* tmp = leftover.c_str();
        data.push_back(fastParseInt(tmp));
    }
    
    return data;
}

// Écriture bufferisée optimisée
void writeChunkOptimized(const vector<int>& data, const string& filename) {
    ofstream out(filename, ios::binary);
    vector<char> buffer;
    buffer.reserve(WRITE_BUFFER);
    
    for (int val : data) {
        string s = to_string(val) + '\n';
        
        if (buffer.size() + s.size() > WRITE_BUFFER) {
            out.write(buffer.data(), buffer.size());
            buffer.clear();
        }
        
        buffer.insert(buffer.end(), s.begin(), s.end());
    }
    
    if (!buffer.empty()) {
        out.write(buffer.data(), buffer.size());
    }
}

// Structure pour la fusion k-way avec buffer
struct BufferedStream {
    ifstream file;
    vector<int> buffer;
    size_t pos = 0;
    bool eof = false;
    
    BufferedStream(const string& filename) : file(filename) {
        refillBuffer();
    }
    
    void refillBuffer() {
        buffer.clear();
        pos = 0;
        
        vector<char> readBuf(MERGE_BUFFER);
        string leftover;
        
        while (buffer.size() < MERGE_BUFFER / 8 && file) {
            file.read(readBuf.data(), MERGE_BUFFER);
            size_t bytesRead = file.gcount();
            
            if (bytesRead == 0) break;
            
            const char* start = readBuf.data();
            const char* end = start + bytesRead;
            const char* p = start;
            
            if (!leftover.empty()) {
                while (p < end && *p != '\n') ++p;
                if (p < end) {
                    leftover.append(start, p - start);
                    const char* tmp = leftover.c_str();
                    buffer.push_back(fastParseInt(tmp));
                    leftover.clear();
                    ++p;
                } else {
                    leftover.append(start, bytesRead);
                    continue;
                }
            }
            
            while (p < end) {
                const char* lineStart = p;
                while (p < end && *p != '\n') ++p;
                
                if (p < end) {
                    buffer.push_back(fastParseInt(lineStart));
                    ++p;
                } else {
                    leftover.assign(lineStart, end - lineStart);
                }
            }
        }
        
        if (!leftover.empty() && buffer.empty()) {
            const char* tmp = leftover.c_str();
            buffer.push_back(fastParseInt(tmp));
        }
        
        if (buffer.empty()) {
            eof = true;
        }
    }
    
    bool hasValue() const {
        return pos < buffer.size();
    }
    
    int current() const {
        return buffer[pos];
    }
    
    void advance() {
        ++pos;
        if (pos >= buffer.size() && !eof) {
            refillBuffer();
        }
    }
};

// Découpage et tri parallèle avec logs détaillés
vector<string> splitAndSortParallel(const string& inputFile) {
    logger.log("┌─ PHASE 1: DÉCOUPAGE ET TRI DES CHUNKS");
    
    size_t fileSize = getFileSize(inputFile);
    logger.log("│ Taille du fichier: ", fileSize / (1024.0 * 1024.0 * 1024.0), " GB");
    
    ifstream in(inputFile);
    if (!in) {
        logger.log("│ ✗ ERREUR: Impossible d'ouvrir ", inputFile);
        return {};
    }
    
    vector<string> chunkFiles;
    mutex chunkMutex;
    size_t chunkIndex = 0;
    size_t totalBytesRead = 0;
    
    vector<thread> threads;
    const size_t numThreads = 4; // Fixé à 4 cores
    
    logger.log("│ Configuration: ", numThreads, " threads, chunks de ", 
               CHUNK_SIZE / 1'000'000, "M entiers (~", 
               CHUNK_SIZE * 4 / (1024 * 1024), " MB)");
    
    auto phaseStart = chrono::high_resolution_clock::now();
    
    while (in) {
        auto readStart = chrono::high_resolution_clock::now();
        vector<int> buffer = readChunkOptimized(in, CHUNK_SIZE, totalBytesRead, fileSize);
        auto readEnd = chrono::high_resolution_clock::now();
        
        if (buffer.empty()) break;
        
        double readTime = chrono::duration_cast<chrono::milliseconds>(readEnd - readStart).count() / 1000.0;
        
        // Attendre qu'un thread soit disponible
        if (threads.size() >= numThreads) {
            threads[0].join();
            threads.erase(threads.begin());
        }
        
        size_t currentChunk = chunkIndex++;
        double progress = fileSize > 0 ? (100.0 * totalBytesRead / fileSize) : 0;
        
        logger.log("│ Chunk ", currentChunk, " lu: ", buffer.size(), " valeurs en ", 
                   fixed, setprecision(2), readTime, "s (", progress, "% du fichier)");
        
        threads.emplace_back([buffer = move(buffer), currentChunk, &chunkFiles, &chunkMutex]() mutable {
            auto sortStart = chrono::high_resolution_clock::now();
            
            logger.log("│   ├─ Tri du chunk ", currentChunk, " (", 
                      buffer.size(), " valeurs)...");
            
            // Tri parallèle
            sort(execution::par_unseq, buffer.begin(), buffer.end());
            
            auto sortEnd = chrono::high_resolution_clock::now();
            double sortTime = chrono::duration_cast<chrono::milliseconds>(sortEnd - sortStart).count() / 1000.0;
            
            logger.log("│   ├─ Chunk ", currentChunk, " trié en ", 
                      fixed, setprecision(2), sortTime, "s");
            
            auto writeStart = chrono::high_resolution_clock::now();
            string chunkName = "chunk_" + to_string(currentChunk) + ".txt";
            writeChunkOptimized(buffer, chunkName);
            auto writeEnd = chrono::high_resolution_clock::now();
            
            double writeTime = chrono::duration_cast<chrono::milliseconds>(writeEnd - writeStart).count() / 1000.0;
            
            logger.log("│   └─ Chunk ", currentChunk, " écrit en ", 
                      fixed, setprecision(2), writeTime, "s");
            
            lock_guard<mutex> lock(chunkMutex);
            chunkFiles.push_back(chunkName);
        });
    }
    
    logger.log("│ Attente de la fin des threads de tri...");
    for (auto& t : threads) {
        t.join();
    }
    
    sort(chunkFiles.begin(), chunkFiles.end());
    
    auto phaseEnd = chrono::high_resolution_clock::now();
    double phaseTime = chrono::duration_cast<chrono::seconds>(phaseEnd - phaseStart).count();
    
    logger.log("└─ PHASE 1 TERMINÉE: ", chunkFiles.size(), " chunks en ", 
               phaseTime, "s");
    logger.log("");
    
    return chunkFiles;
}

// Fusion k-way optimisée avec logs
void mergeChunksOptimized(const vector<string>& chunks, const string& outputFile) {
    logger.log("┌─ PHASE 2: FUSION K-WAY");
    logger.log("│ Fusion de ", chunks.size(), " chunks...");
    
    struct HeapNode {
        int value;
        size_t streamIndex;
        
        bool operator>(const HeapNode& other) const {
            return value > other.value;
        }
    };
    
    auto phaseStart = chrono::high_resolution_clock::now();
    
    logger.log("│ Ouverture des ", chunks.size(), " fichiers triés...");
    
    priority_queue<HeapNode, vector<HeapNode>, greater<HeapNode>> pq;
    vector<unique_ptr<BufferedStream>> streams;
    
    for (size_t i = 0; i < chunks.size(); i++) {
        auto stream = make_unique<BufferedStream>(chunks[i]);
        if (stream->hasValue()) {
            pq.push({stream->current(), i});
            streams.push_back(move(stream));
        }
    }
    
    logger.log("│ Début de la fusion...");
    
    ofstream out(outputFile, ios::binary);
    vector<char> writeBuffer;
    writeBuffer.reserve(WRITE_BUFFER);
    
    size_t count = 0;
    size_t lastLog = 0;
    const size_t LOG_INTERVAL = 10'000'000; // Log tous les 10M
    
    auto lastLogTime = chrono::high_resolution_clock::now();
    
    while (!pq.empty()) {
        HeapNode node = pq.top();
        pq.pop();
        
        string s = to_string(node.value) + '\n';
        
        if (writeBuffer.size() + s.size() > WRITE_BUFFER) {
            out.write(writeBuffer.data(), writeBuffer.size());
            writeBuffer.clear();
        }
        
        writeBuffer.insert(writeBuffer.end(), s.begin(), s.end());
        
        streams[node.streamIndex]->advance();
        
        if (streams[node.streamIndex]->hasValue()) {
            pq.push({streams[node.streamIndex]->current(), node.streamIndex});
        }
        
        count++;
        
        if (count - lastLog >= LOG_INTERVAL) {
            auto now = chrono::high_resolution_clock::now();
            double elapsed = chrono::duration_cast<chrono::milliseconds>(now - lastLogTime).count() / 1000.0;
            double rate = LOG_INTERVAL / elapsed / 1'000'000.0;
            
            logger.log("│ Fusionné: ", count / 1'000'000, "M valeurs (", 
                      fixed, setprecision(2), rate, "M/s)");
            
            lastLog = count;
            lastLogTime = now;
        }
    }
    
    if (!writeBuffer.empty()) {
        out.write(writeBuffer.data(), writeBuffer.size());
    }
    
    auto phaseEnd = chrono::high_resolution_clock::now();
    double phaseTime = chrono::duration_cast<chrono::seconds>(phaseEnd - phaseStart).count();
    double avgRate = count / phaseTime / 1'000'000.0;
    
    logger.log("└─ PHASE 2 TERMINÉE: ", count / 1'000'000, "M valeurs fusionnées en ", 
               phaseTime, "s (", fixed, setprecision(2), avgRate, "M/s)");
    logger.log("");
}

int main() {
    string input = "fichier.csv";
    string output = "sorted.txt";
    
    logger.log("╔═══════════════════════════════════════════╗");
    logger.log("║   TRI EXTERNE ULTRA-OPTIMISÉ - 100GB     ║");
    logger.log("╚═══════════════════════════════════════════╝");
    logger.log("");
    
    auto totalStart = chrono::high_resolution_clock::now();
    
    vector<string> chunks = splitAndSortParallel(input);
    
    if (chunks.empty()) {
        logger.log("✗ ERREUR: Aucun chunk créé");
        return 1;
    }
    
    mergeChunksOptimized(chunks, output);
    
    auto totalEnd = chrono::high_resolution_clock::now();
    double totalTime = chrono::duration_cast<chrono::seconds>(totalEnd - totalStart).count();
    
    logger.log("╔═══════════════════════════════════════════╗");
    logger.log("║            TRI TERMINÉ !                  ║");
    logger.log("╠═══════════════════════════════════════════╣");
    logger.log("║ Temps total: ", setw(8), totalTime, " secondes      ║");
    logger.log("║ Fichier de sortie: ", output, "           ");
    logger.log("╚═══════════════════════════════════════════╝");
    
    return 0;
}