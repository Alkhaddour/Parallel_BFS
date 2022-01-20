#include "SequentialBFS.h"
#include <cassert>
// initializer
Sequential_BFS::Sequential_BFS(LL graph_size) {
    this->distances.resize(graph_size, -1);
    this->reached.resize(graph_size, -1);
}

void Sequential_BFS::visit(const Graph* graph) {
    this->wait_queue.push(std::make_pair(0,-1));
    this->reached[0]=1;
    // repeat process until the graph is distances
    while(!this->wait_queue.empty()) {
        // std::cout<< this->wait_queue.size() <<std::endl;
        // read node and remove from queue
        LL node_idx = this->wait_queue.front().first;
        LL node_dist = this->wait_queue.front().second + 1;
        this->wait_queue.pop();
        // visit node
        this->distances[node_idx] = node_dist;
        // add unvisited neighbors to wait queue in order to be visited
        Node cur_node = graph->nodes[node_idx];
        for(LL i=0; i < cur_node.degree; i++) {
            LL neighbor_idx = cur_node.neighbors[i];
            if(this->reached[neighbor_idx] == -1) {
                this->wait_queue.push(std::make_pair(neighbor_idx, node_dist));
                this->reached[neighbor_idx]=1;
            }
        }
    }
}

bool Sequential_BFS::verify() {
    std::cout << "Verifying...";
    for(auto i = 0; i < this->distances.size(); i++)
        if(this->distances[i] != get_distance(i))
            assert((this->distances[i] == get_distance(i))); // OK

    return true;
}

int Sequential_BFS::get_distance(LL neighbor_idx){
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