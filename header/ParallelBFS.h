#ifndef PARALLEL_BFS_OPENMP_PARALLELBFS_H
#define PARALLEL_BFS_OPENMP_PARALLELBFS_H

#include <deque>
#include <queue>
#include "utils.h"

class Parallel_BFS{
    private:
        LL graph_size;

        int* front_nodes;
        LL * front_nodes_degree;

        int* next_front;
        LL * next_front_cum_degree;
        LL * nf_marked;
        LL * nf_marked_cum;

        bool* visited;
        int* distances;

    public:
        explicit Parallel_BFS(LL graph_size);
        void  visit(const Graph *graph);
        bool verify(Graph* graph);
        static int get_distance(LL neighbor_idx);
};
#endif //PARALLEL_BFS_OPENMP_PARALLELBFS_H
