#include <iostream>
#include "Graph.hpp"
#include <cstring>

using namespace std;

Graph::Graph(){}

Graph::~Graph(){
    //Deallocate stuff:
    for(int i = 0; i < labels.size(); i++){
        delete[] labels[i];
        labels[i] = 0;
    }
    for(int i = 0; i < adjMatrix.size(); i++){
        delete adjMatrix[i];
        adjMatrix[i] = 0;
    }
}

bool Graph::addVertex(char* label){
    for(int i = 0; i < labels.size(); i++){//Check if vertex with same label exists
        if(strcmp(label, labels[i]) == 0){
            return false;
        }
    }
    
    labels.push_back(strcpy(new char[strlen(label)+1], label));
    for(int i = 0; i < adjMatrix.size(); i++){
        //Old vertices don't connect to new vertex.
        adjMatrix[i]->push_back(-1);
    }
    //New vertex's connections.
    adjMatrix.push_back(new vector<int>);
    for(int i = 0; i < adjMatrix.size(); i++){//Initially not connected to anything.
        adjMatrix[adjMatrix.size()-1]->push_back(-1);
    }
}