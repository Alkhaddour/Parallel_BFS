#ifndef PARALLEL_BFS_OPENMP_SEQUENTIALBFS_H
#define PARALLEL_BFS_OPENMP_SEQUENTIALBFS_H
#include "GraphManager.h"
#include <fstream>
#include <queue>
class Sequential_BFS{
private:
    std::vector<int> distances;
    std::queue<std::pair<LL, int>> wait_queue; // pair <neighbor, source distance>
    std::vector<LL> reached;
public:
    explicit Sequential_BFS(LL graph_size);
    // visit graph
    void visit(const Graph *graph);
    // verify that graph was distances
    bool verify();

    static int get_distance(LL neighbor_idx);
};
#endif //PARALLEL_BFS_OPENMP_SEQUENTIALBFS_H