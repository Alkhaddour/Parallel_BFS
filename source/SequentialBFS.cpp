#include "SequentialBFS.h"

// initializer
Sequential_BFS::Sequential_BFS(LL graph_size) {
    this->visited.resize(graph_size, false);
}

void Sequential_BFS::visit(const Graph* graph) {
    // start with node at origin, visit it
    // visit could be any other operation, for now we will just mark it as visited using boolean value, and push all
    // of its neighbors to queue to be visited
    this->wait_queue.push(0);
    this->visited[0] = true;

    // repeat process until the graph is visited
    while(!this->wait_queue.empty()) {
        // read node and remove from queue
        Node cur_node = graph->nodes[this->wait_queue.front()];
        this->wait_queue.pop();
        // add unvisited neighbors to wait queue in order to be visited
        for(LL i=0; i < cur_node.degree; i++) {
            LL neighbor = cur_node.neighbors[i];
            if(!visited[neighbor]) {
                wait_queue.push(cur_node.neighbors[i]);
                visited[neighbor] = true;
            }
        }
    }
}

bool Sequential_BFS::verify() {
    for(auto i = 0; i < this->visited.size(); i++)
        if(!this->visited[i])
            return false;

    return true;
}
