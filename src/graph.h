#ifndef CPPBFS_GRAPH_H
#define CPPBFS_GRAPH_H

#include <vector>

struct CubeGraph {
    int size = 0;

    explicit CubeGraph(int size) {
        this->size = size;
    }

    [[nodiscard]] int nodes_count() const {
        return size * size * size;
    }

public:
    std::vector<int> get_neighbours_of(int node) {
        int x = node % size;
        int y = (node / size) % size;
        int z = (node / size) / size;
        std::vector<int> neighbours(0);
        if (x < size - 1) {
            neighbours.push_back(n_node(x + 1, y, z));
        }
        if (y < size - 1) {
            neighbours.push_back(n_node(x, y + 1, z));
        }
        if (z < size - 1) {
            neighbours.push_back(n_node(x, y, z + 1));
        }
        return neighbours;
    }

private:
    [[nodiscard]] int n_node(int x, int y, int z) const {
        return x + (size * z + y) * size;
    }
};

#endif //CPPBFS_GRAPH_H
