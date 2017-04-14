#include <iostream>
#include "Graph.hpp"
#include <cstring>

using namespace std;

int indexOf(vector<char*> &vect, const char* label);

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

bool Graph::addVertex(const char* label){
    if(indexOf(labels, label) != -1){//Check if vertex with same label exists
        return false;
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

bool Graph::addEdge(char* label1, char* label2, int weight){
    int index1 = indexOf(labels, label1), index2 = indexOf(labels, label2);
    if(index1 == -1 || index2 == -1){
        return false;
    }
    (*adjMatrix[index1])[index2] = weight;
    return true;
}

bool Graph::removeVertex(char* label){
    int index = indexOf(labels, label);
    if(index == -1){//Vertex not there?
        return false;
    }
    delete labels[index];
    labels.erase(labels.begin() + index);
    for(int i=0; i < adjMatrix.size(); i++){//Erase connections of all vertices to this vertex.
        adjMatrix[i]->erase(adjMatrix[i]->begin() + index);
    }
    //Now erase this vertex's row:
    delete adjMatrix[index];
    adjMatrix.erase(adjMatrix.begin() + index);
    return true;
}

bool Graph::removeEdge(char* label1, char* label2){
    //Will return false if cannot find labels or edge doesn't exist:
    int index1 = indexOf(labels, label1), index2 = indexOf(labels, label2);
    if(index1 == -1 || index2 == -1 || (*adjMatrix[index1])[index2] == -1){
        return false;
    }
    (*adjMatrix[index1])[index2] = -1;
    return true;
}

int indexOf(vector<char*> &vect, const char* element){
    for(int i = 0; i < vect.size(); i++){
        if(strcmp(vect[i], element) == 0){
            return i;
        }
    }
    return -1;
}

void Graph::printAdjMatrix(){
    //Top row:
    cout << "  ";
    for(int i=0; i < labels.size(); i++){
        cout << labels[i] << ' ';
    }
    cout << endl;
    //The rest:
    for(int i = 0; i < adjMatrix.size(); i++){
        cout << labels[i] << ' ';
        for(int j = 0; j < labels.size(); j++){
            if((*adjMatrix[i])[j] >= 0){
                cout << (*adjMatrix[i])[j];
            }
            else{
                cout << 'X';
            }
            cout << ' ';
        }
        cout << endl;
    }
}