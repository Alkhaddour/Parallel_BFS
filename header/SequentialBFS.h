#ifndef PARALLEL_BFS_OPENMP_SEQUENTIALBFS_H
#define PARALLEL_BFS_OPENMP_SEQUENTIALBFS_H
#include "GraphManager.h"
#include <fstream>
#include <queue>
class Sequential_BFS{
private:
    std::vector<bool> visited;
    std::queue<LL> wait_queue;
public:
    explicit Sequential_BFS(LL graph_size);
    // visit graph
    void visit(const Graph *graph);
    // verify that graph was visited
    bool verify();
};
#endif //PARALLEL_BFS_OPENMP_SEQUENTIALBFS_H
