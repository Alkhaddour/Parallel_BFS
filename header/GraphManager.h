#ifndef PARALLEL_BFS_OPENMP_GRAPHMANAGER_H
#define PARALLEL_BFS_OPENMP_GRAPHMANAGER_H

#include <iostream>
#include <fstream>
#include "utils.h"
LL find_degree(LL x, LL y, LL z, LL cube_side);
LL get_neighbor_index(LL x, LL y, LL z, LL cube_side);
void create_graph(LL cube_side, std::ostream &out_stream);
Graph* load_graph(std::ifstream &in_stream);

#endif //PARALLEL_BFS_OPENMP_GRAPHMANAGER_H
