#include <chrono>
#include <fstream>
#include <iostream>
#include "GraphManager.h"
#include "ParallelBFS.h"
#include "ParallelBFSTester.cpp"
#include "SequentialBFSTester.cpp"

int main() {
    std::cout << "Reading graph from file...\n";
    std::ifstream in_stream(GRAPH_FILE);
    Graph *graph = load_graph(in_stream);

    long long sequential_time = 0;
    for (int i = 0; i < N_TRIALS; i++){
        std:: cout << "Running trial " << (i+1) << "\n";
        sequential_time += test_sequential_bfs(graph);
    }

    long long parallel_time = 0;
    for (int i = 0; i < N_TRIALS; i++){
        std:: cout << "Running trial " << (i+1) << "\n";
        parallel_time += test_parallel_bfs(graph);
    }

    std::cout <<" #################################################################\n";
    std::cout << "Average Sequential time: " << (double)sequential_time / N_TRIALS << "\n";
    std::cout << "Average parallel time:   " << (double)parallel_time / N_TRIALS  << "\n";
    std::cout << "Parallel processing is " << (double)sequential_time / parallel_time << " faster than sequential processing" << "\n";
}