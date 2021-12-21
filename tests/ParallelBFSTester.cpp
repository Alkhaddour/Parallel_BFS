#include <chrono>
#include <iostream>
#include "ParallelBFS.h"
#include <cassert>

long long test_parallel_bfs(Graph* graph){
    std::cout << "Visiting graph using Parallel BFS...\n";
    Parallel_BFS p_bfs(graph->graph_size);
    std::chrono::time_point start_timestamp = std::chrono::steady_clock::now();
    p_bfs.visit(graph);
    std::chrono::time_point end_timestamp = std::chrono::steady_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_timestamp - start_timestamp).count();
    std::cout << "Verifying that all nodes were visited...\n";

    if (p_bfs.verify())
        std::cout << "OK! in " << duration_ms <<"ms" <<"\n";
    else
        assert("Failed to visit all nodes");

    return duration_ms;
}

