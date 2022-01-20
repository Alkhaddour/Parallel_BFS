#include <iostream>
#include <chrono>
#include <cassert>
#include "ParallelComputations.h"
#include "ParallelBFS.h"
#include "GraphManager.h"

// initializer
Parallel_BFS::Parallel_BFS(LL graph_size) {
    this->graph_size = graph_size;

    front_nodes = new int[graph_size];
    front_nodes_degree = new LL[graph_size];

    next_front = new int[graph_size];
    next_front_cum_degree = new LL[graph_size];
    nf_marked = new LL[graph_size];
    nf_marked_cum = new LL[graph_size];

    visited = new bool[graph_size];
    distances = new int[graph_size];
    for (int i =0;i< graph_size;i++)
        distances[i]=-1;
}

// visitor
void Parallel_BFS::visit(const Graph* graph) {
    front_nodes[0] = 0;
    distances[0]=0;
    visited[0] = true;
    LL front_size = 1;

    // define get degree function for map
    std::function<LL(int)> map_function = [graph](int x) -> LL { return graph->nodes[x].degree; };

    while (front_size > 0) {
        // get degree of front_nodes nodes
        map(front_nodes, front_nodes_degree, 0, front_size, map_function);
        // scan front_nodes_degree
        LL size = scan(front_nodes_degree, next_front_cum_degree, 0, front_size);
        // visit front
        #pragma omp parallel for num_threads(N_THREADS) default(none) shared(front_size, graph,visited, distances)
        for(LL i = 0; i < front_size; i++) {
            for(LL j = 0; j < graph->nodes[front_nodes[i]].degree; j++) {
                LL neighbor = graph->nodes[front_nodes[i]].neighbors[j];

                bool is_visited;
                int dist;
                #pragma omp atomic capture
                {
                    is_visited = visited[neighbor];
                    visited[neighbor] = true;
                }
                if (distances[neighbor] == -1 || !is_visited ){
                    distances[neighbor] = distances[front_nodes[i]]+1;
                    next_front[next_front_cum_degree[i] + j] = neighbor;
                }
                else
                    next_front[next_front_cum_degree[i] + j] = -1;



            }
        }
        // update front to move to next step
        std::function<LL(int)> filter_function = [](int x) -> LL { return x >= 0 ? 1 : 0; };
        front_size = filter(next_front, front_nodes, nf_marked, nf_marked_cum, 0, size, filter_function);
    }
//    return const_cast<Graph *>(graph);
}

bool Parallel_BFS::verify(Graph* graph) {
    for(auto i = 0; i < this->graph_size; i++)
        if (distances[i] != get_distance(i)) {
            std::cout << "index " << i << " -> ";
            std::cout << distances[i]<< " -> ";
            std::cout << get_distance(i) << " -> ";
            std::cout << (visited[i] ? "visited" : "Not visited") << std::endl;
            assert((false));
        }
    return true;
}

int Parallel_BFS::get_distance(LL neighbor_idx){
    int x=0;
    int y=0;
    int z=0;
    if (neighbor_idx < CUBE_SIDE_DIM)
        z = neighbor_idx;
    else if(neighbor_idx < CUBE_SIDE_DIM*CUBE_SIDE_DIM){
        y = int(neighbor_idx / CUBE_SIDE_DIM);
        z = neighbor_idx - CUBE_SIDE_DIM * y;
    }
    else{
        x = int(neighbor_idx / (CUBE_SIDE_DIM * CUBE_SIDE_DIM));
        y = int((neighbor_idx - CUBE_SIDE_DIM*CUBE_SIDE_DIM * x)/CUBE_SIDE_DIM);
        z = neighbor_idx - CUBE_SIDE_DIM * y - CUBE_SIDE_DIM*CUBE_SIDE_DIM * x;
    }

    return  x+y+z;
}
