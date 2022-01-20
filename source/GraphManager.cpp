#include "GraphManager.h"

LL find_degree(LL x, LL y, LL z, LL cube_side){
    int degree = 0;

    // vertex at the edge of x-axis
    if (x >= 1)
        degree++;
    if (x < cube_side - 1)
        degree++;

    // vertex at the edge of y-axis
    if (y >= 1)
        degree++;
    if (y < cube_side - 1)
        degree++;

    // vertex at the edge of z-axis
    if (z >= 1)
        degree++;
    if (z < cube_side - 1)
        degree++;

    return degree;
}
LL get_neighbor_index(LL x, LL y, LL z, LL cube_side){
    return x * cube_side * cube_side + y * cube_side + z;
}

void create_graph(LL cube_side, std::ostream &out_stream) {
    /*
     * Creates graph and save it to text file
     * First line contains and integer N; number of vertices in the graph
     * Next N lines contain data describing vertices, each line describe on vertex
     * A vertex is described by an integer M; number of neighbors of the vertex, then M integers representing index of
     * neighbors.
     */
    std::cout<<"Generating graph with side dim = " << cube_side;

    out_stream << cube_side * cube_side * cube_side << std::endl;

    for (LL i = 0; i < cube_side; i++) {
        for (LL j = 0; j < cube_side; j++) {
            for (LL k = 0; k < cube_side; k++) {
                // get number of neighbors
                LL n_neighbors = find_degree(i, j, k, cube_side);

                // describe vertex
                out_stream << n_neighbors;

                if(i+1 < cube_side) out_stream << " " << get_neighbor_index(i + 1, j, k, cube_side);
                if(i-1 >= 0)        out_stream << " " << get_neighbor_index(i - 1, j, k, cube_side);

                if(j+1 < cube_side) out_stream << " " << get_neighbor_index(i, j + 1, k, cube_side);
                if(j-1 >= 0)        out_stream << " " << get_neighbor_index(i, j - 1, k, cube_side);

                if(k+1 < cube_side) out_stream << " " << get_neighbor_index(i, j, k + 1, cube_side);
                if(k-1 >= 0)        out_stream << " " << get_neighbor_index(i, j, k - 1, cube_side);

                out_stream << std::endl;
            }
        }
    }
}

Graph* load_graph(std::ifstream &in_stream){
    /*
     * Load graph from text file
     * return Graph
     */
    auto graph = new Graph();
    in_stream >> graph->graph_size;
    graph->nodes = new Node[graph->graph_size];

    for(LL node_idx = 0; node_idx < graph->graph_size; node_idx++) {
        // read node degree
        LL node_degree; in_stream >> node_degree;
        graph->nodes[node_idx].degree = node_degree;

        // read list of neighbors
        if(node_degree > 0) {
            graph->nodes[node_idx].neighbors = new LL[node_degree];
            for(LL j=0; j < node_degree; ++j) {
                in_stream >> graph->nodes[node_idx].neighbors[j];
            }
        }
    }
    return graph;
}
