#include <iostream>
#include "Graph.hpp"

using namespace std;

int main(){
    Graph graph;
    graph.addVertex("B");
    graph.addVertex("N");
    graph.addVertex("T");
    graph.addVertex("P");
    graph.addEdge("T", "N", 7);
    graph.printAdjMatrix();
    return 0;
}