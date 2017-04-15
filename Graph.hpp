#pragma once
#include <vector>
#include <utility>
#include <limits>
//A graph class that does everything using an adjacency matrix.

using namespace std;

class Graph{
  public:
    Graph();
    ~Graph();
    bool addVertex(const char* label);
    bool addEdge(const char* label1, const char* label2, int weight); //Will replace if exists
    bool removeVertex(char* label);
    bool removeEdge(char* label1, char* label2);
    bool addBothEdges(const char* label1, const char* label2, int weight);
    void printAdjMatrix();
    pair<vector<char*>, int> findPath(const char* label1, const char* label2);
    const int infty;
  private:
    vector<vector<int>*> adjMatrix;
    vector<char*> labels;
};