#pragma once
#include <vector>
//A graph class that does everything using an adjacency matrix.

using namespace std;

class Graph{
  public:
    Graph();
    ~Graph();
    bool addVertex(char* label);
    bool addEdge(char* label1, char* label2, int weight); //Will replace if exists
    bool removeVertex(char* label);
    //bool removeEdge(char* label1, char* label2);
  private:
    vector<vector<int>*> adjMatrix;
    vector<char*> labels;
};