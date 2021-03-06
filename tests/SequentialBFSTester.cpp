#include <chrono>
#include <fstream>
#include <iostream>
#include "GraphManager.h"
#include "SequentialBFS.h"
#include <cassert>

long long test_sequential_bfs(Graph* graph){
    std::cout << "Visiting graph using Sequential BFS...\n";
    Sequential_BFS s_bfs(graph->graph_size);
    std::chrono::time_point start_timestamp = std::chrono::steady_clock::now();
    s_bfs.visit(graph);
    std::chrono::time_point end_timestamp = std::chrono::steady_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_timestamp - start_timestamp).count();
    std::cout << "Verifying that all nodes were visited...\n";

    if (s_bfs.verify())
        std::cout << "OK! in " << duration_ms <<"ms" <<"\n";
    else
        assert("Failed to visit all nodes");

    return duration_ms;
}

