#include "GraphManager.h"
#include <iostream>
#include <fstream>

int main(){
    std::ofstream out_stream(GRAPH_FILE);
    create_graph(CUBE_SIDE_DIM, out_stream);
    return 0;
}