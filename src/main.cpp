#include <iostream>
#include "graph.h"
#include "bfs.h"

using namespace std;
using namespace std::chrono;
using namespace bfs;

const int S = 500;

void check(vector<int> distances);

void checkPar(parlay::sequence<int> sequence1);

int main() {
    CubeGraph graph(S);

    auto start = high_resolution_clock::now();
    vector<int> distances_seq = seq(graph);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Seq: " << duration.count() / 1000 << "ms" << endl;
    check(distances_seq);

    start = high_resolution_clock::now();
    parlay::sequence<int> distances_par = par(graph);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Par: " << duration.count() / 1000 << "ms" << endl;
    checkPar(distances_par);
}

void check(vector<int> distances) {
    for (int i = 0; i < distances.size(); i++) {
        if (distances[i] != (i % S) + ((i / S) % S) + ((i / S) / S)) {
            cout << "Incorrect!" << endl;
            break;
        } else if (i == distances.size() - 1) {
            cout << "Correct!" << endl;
        }
    }
}

void checkPar(parlay::sequence<int> distances) {
    for (int i = 0; i < distances.size(); i++) {
        if (distances[i] != (i % S) + ((i / S) % S) + ((i / S) / S)) {
            cout << "Incorrect!" << endl;
            break;
        } else if (i == distances.size() - 1) {
            cout << "Correct!" << endl;
        }
    }
}