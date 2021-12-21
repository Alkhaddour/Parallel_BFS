#ifndef PARALLEL_BFS_OPENMP_UTILS_H
#define PARALLEL_BFS_OPENMP_UTILS_H
#include <string>

// Defined types
typedef int LL;

// Constants
extern LL CUBE_SIDE_DIM;
extern std::string GRAPH_FILE;
extern LL N_THREADS;
// DS
struct Node {
    LL degree;
    LL *neighbors;
};

struct Graph{
    LL graph_size;
    Node* nodes;
};
#endif
