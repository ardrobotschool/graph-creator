#include <iostream>
#include "Graph.hpp"
#include <cstring>

using namespace std;

int indexOf(vector<char*> &vect, const char* label);
char* heapCopy(char* str);
void pathCpy(vector<char*> &destination, vector<char*> &source);

Graph::Graph() : infty(numeric_limits<int>::max()){}

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
    return true;
}

bool Graph::addEdge(const char* label1, const char* label2, int weight){
    int index1 = indexOf(labels, label1), index2 = indexOf(labels, label2);
    if(index1 == -1 || index2 == -1){
        return false;
    }
    (*adjMatrix[index1])[index2] = weight;
    return true;
}

bool Graph::addBothEdges(const char* label1, const char* label2, int weight){
    return addEdge(label1, label2, weight) && addEdge(label2, label1, weight);
}

bool Graph::removeVertex(char* label){
    int index = indexOf(labels, label);
    if(index == -1){//Vertex not there?
        return false;
    }
    delete[] labels[index];
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
    //Get max label length:
    int maxlength = 0;
    for(int i = 0; i < labels.size(); i++){
        int len = strlen(labels[i]);
        if(len > maxlength){
            maxlength = len;
        }
    }
    //Top row:
    for(int i = 0; i < maxlength + 1; i++){
        cout << ' ';
    }
    for(int i=0; i < labels.size(); i++){
        cout << labels[i] << ' ';
    }
    cout << endl;
    //The rest:
    for(int i = 0; i < adjMatrix.size(); i++){
        cout << labels[i];
        for(int k=0; k < maxlength - strlen(labels[i]) + 1; k++){
            cout << ' ';
        }
        for(int j = 0; j < labels.size(); j++){
            if((*adjMatrix[i])[j] >= 0){
                cout << (*adjMatrix[i])[j];
            }
            else{
                cout << 'X';
            }
            for(int k = 0; k < strlen(labels[j]); k++){
                cout << ' ';
            }
        }
        cout << endl;
    }
}

pair<vector<char*>, int> Graph::findPath(const char* label1, const char* label2){
    //Returns shortest path (sequence of vertex labels) along with the "distance travelled."
    //If vertices don't exist, second will be -1
    //If no path exists between the vertices, second will be infty.
    pair<vector<char*>, int> result;
    int index1 = indexOf(labels, label1), index2 = indexOf(labels, label2);
    if(index1 == -1 || index2 == -1){//At least one of the labels doesn't exist.
        result.second = -1;
        return result;
    }
    //For each node, we will set a tentative distance, initially infinity;
    //We will also keep track of the paths whereby shortest distances are achieved.
    //We also need to keep track of whether we've visited a node already.
    int unvisited[labels.size()];
    vector< pair<vector<char*>, int> > nodes; //Same order as labels.
    for(int i = 0; i < labels.size(); i++){
        unvisited[i] = true;
        nodes.push_back(pair<vector<char*>, int>());
        nodes[nodes.size()-1].second = infty;
    }
    //Our starting point has distance 0
    unvisited[index1] = false;
    nodes[index1].second = 0;
    nodes[index1].first.push_back(heapCopy(labels[index1]));
    int current = index1;
    while(true){
        //Calculate tentative distances and paths for nodes connected to current.
        for(int i = 0; i < labels.size(); i++){
            if((*adjMatrix[current])[i] != -1 && unvisited[i]){
                int distance = nodes[current].second + (*adjMatrix[current])[i];
                if(distance < nodes[i].second){
                    nodes[i].second = distance;
                    pathCpy(nodes[i].first, nodes[current].first);
                    nodes[i].first.push_back(heapCopy(labels[i]));
                }
            }
        }
        unvisited[current] = false;
        if(unvisited[index2] == false){
            //Deallocate everything but the returned stuff.
            for(int i = 0; i < labels.size(); i++){
                if(i != index2){
                    for(int j=0; j<nodes[i].first.size(); j++){
                        delete[] (nodes[i].first)[j];
                    }
                }
            }
            return nodes[index2];
        }
        bool noPath = true;
        for(int i = 0; i < labels.size(); i++){
            if(unvisited[i] && nodes[i].second != infty){
                noPath = false;
                break;
            }
        }
        if(noPath){
            //Deallocate everything.
            for(int i = 0; i < labels.size(); i++){
                for(int j=0; j<nodes[i].first.size(); j++){
                    delete[] (nodes[i].first)[j];
                }
            }
            return nodes[index2];
        }
        int smallest = infty;
        for(int i = 0; i < labels.size(); i++){
            if(unvisited[i] && nodes[i].second < smallest){
                smallest = nodes[i].second;
                current = i;
            }
        }
    }
}

void Graph::printPathDetails(const char* label1, const char* label2){
    pair<vector<char*>, int> result = findPath(label1, label2);
    if(result.second == -1){
        cout << "Could not find both vertices." << endl;
        return;
    }
    if(result.second == infty){
        cout << "No path exists between the vertices." << endl;
        return;
    }
    cout << "Path: " << result.first[0];
    delete[] result.first[0];
    for(int i = 1; i < result.first.size(); i++){
        cout << "->" << result.first[i];
        delete[] result.first[i];
    }
    cout << ";" << endl;
    cout << "Distance travelled: " << result.second << '.' << endl;
}

void Graph::clear(){
    while(!labels.empty()){
        removeVertex(labels[0]);
    }
}

char* heapCopy(char* str){
    return strcpy(new char[strlen(str)+1], str);
}

void pathCpy(vector<char*> &destination, vector<char*> &source){
    for(int i = 0; i < destination.size(); i++){
        delete[] destination[i];
    }
    destination.clear();
    for(int i = 0; i < source.size(); i++){
        destination.push_back(heapCopy(source[i]));
    }
}