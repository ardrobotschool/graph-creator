#include <iostream>
#include "Graph.hpp"

using namespace std;

int main(){
    Graph graph;
    graph.addVertex("1");
    graph.addVertex("2");
    graph.addVertex("3");
    graph.addVertex("6");
    graph.addVertex("4");
    graph.addVertex("5");
    graph.addBothEdges("1", "6", 14);
    graph.addBothEdges("5", "6", 9);
    graph.addBothEdges("3", "6", 2);
    graph.addBothEdges("1", "3", 9);
    graph.addBothEdges("1", "2", 7);
    graph.addBothEdges("3", "2", 10);
    graph.addBothEdges("5", "4", 6);
    graph.addBothEdges("3", "4", 11);
    graph.addBothEdges("2", "4", 15);
    //graph.printAdjMatrix();
    vector<char*> path = graph.findPath("1", "5").first;
    cout << path[0];
    for(int i = 1; i < path.size(); i++){
        cout << "->" << path[i];
    }
    cout << endl;
    return 0;
}