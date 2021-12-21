#include <chrono>
#include <fstream>
#include <iostream>
#include "GraphManager.h"
#include "SequentialBFS.h"
int main(){
    std::cout << "Reading graph from file...\n";
    std::ifstream in_stream(GRAPH_FILE);
    Graph* graph = load_graph(in_stream);

    std::cout << "Visiting graph using sequential BFS...\n";
    Sequential_BFS s_bfs(graph->graph_size);
    std::chrono::time_point start_timestamp = std::chrono::steady_clock::now();
    s_bfs.visit(graph);
    std::chrono::time_point end_timestamp = std::chrono::steady_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_timestamp - start_timestamp).count();
    std::cout << "Verifying that all nodes were visited...\n";
    if (s_bfs.verify() == true)
        std::cout << "OK! in " << duration_ms <<"ms";
    else
        std::cout << "Failed";
    return 0;
}
