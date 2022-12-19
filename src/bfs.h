#ifndef CPPBFS_BFS_H
#define CPPBFS_BFS_H


#include <iostream>
#include <vector>
#include <deque>

#include "../parlay/parallel.h"
#include "../parlay/primitives.h"
#include "../parlay/sequence.h"
#include "graph.h"

using namespace std;

namespace bfs {
    vector<int> seq(CubeGraph &graph) {
        int nodes_count = graph.nodes_count();
        vector<bool> visited(nodes_count, false);
        vector<int> distances(nodes_count, -1);
        deque<pair<int, int>> frontier{};
        frontier.emplace_back(0, 0);
        while (!frontier.empty()) {
            auto distance_node = frontier.front();
            frontier.pop_front();
            distances[distance_node.second] = distance_node.first;
            auto neighbours = graph.get_neighbours_of(distance_node.second);
            for (int node: neighbours) {
                if (!visited[node]) {
                    visited[node] = true;
                    frontier.emplace_back(distance_node.first + 1, node);
                }
            }
        }
        return distances;
    }

    parlay::sequence<int> par(CubeGraph &graph) {
        int nodes_count = graph.nodes_count();
        auto visited = new std::atomic<bool>[nodes_count];
        for(int i = 0; i < nodes_count; i++) {
            visited[i] = false;
        }
        parlay::sequence<int> distances(nodes_count, -1);
        parlay::sequence<int> frontier(1, 0);
        for (int distance = 0; !frontier.empty(); distance++) {
            parlay::for_each(
                    frontier,
                    [&] (int node) { distances[node] = distance; }
            );
            auto neighbours_nested = parlay::map(
                    frontier,
                    [&] (int node) {
                        return graph.get_neighbours_of(node);
                    }
            );
            auto neighbours = parlay::flatten(neighbours_nested);

            frontier = parlay::filter(
                    neighbours,
                    [&] (int node) {
                        bool expected = false;
                        return !visited[node] && visited[node].compare_exchange_strong(expected, true);
                    }
            );
        }
        delete []visited;
        return distances;
    }
}
#endif //CPPBFS_BFS_H
