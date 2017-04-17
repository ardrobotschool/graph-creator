#include <iostream>
#include "Graph.hpp"
#include <cstring>

using namespace std;

int main(){
    Graph graph;
    char input[32];
    while(true){
        cout << "Choose an option:" << endl;
        cout << "(1)Add a vertex." << endl;
        cout << "(2)Add or replace an edge." << endl;
        cout << "(3)Remove a vertex." << endl;
        cout << "(4)Remove an edge." << endl;
        cout << "(5)Print the details of the shortest path between two vertices." << endl;
        cout << "(c)Clear graph." << endl;
        cout << "(q)Quit" << endl;
        cout << "(0)Do science." << endl;
        cin.getline(input, 32);
        if(strlen(input) > 1){
            cout << "Command not recognized." << endl;
            continue;
        }
        input[0] = tolower(input[0]);
        if(input[0] == '1'){
            char label[32];
            cout << "Enter vertex label: ";
            cin.getline(label, 32);
            if(graph.addVertex(label)){
                cout << "Vertex added." << endl;
            }
            else{
                cout << "A vertex with that label already exists." << endl;
            }
        }
        else if(input[0] == '2'){
            char label1[32], label2[32];
            int weight;
            cout << "Enter label of first vertex: ";
            cin.getline(label1, 32);
            cout << "Enter label of second vertex: ";
            cin.getline(label2, 32);
            cout << "Enter an integer weight: " << endl;
            cin >> weight;
            if(graph.addEdge(label1, label2, weight)){
                cout << "Done." << endl;
            }
            else{
                cout << "At least one of the vertices could not be found." << endl;
            }
        }
        else if(input[0] == '3'){
            char label[32];
            cout << "Enter vertex label: ";
            cin.getline(label, 32);
            if(graph.removeVertex(label)){
                cout << "Vertex removed." << endl;
            }
            else{
                cout << "Vertex could not be found." << endl;
            }
        }
        else if(input[0] == '4'){
            char label1[32], label2[32];
            cout << "Enter label of first vertex: ";
            cin.getline(label1, 32);
            cout << "Enter label of second vertex: ";
            cin.getline(label2, 32);
            if(graph.removeEdge(label1, label2)){
                cout << "Done." << endl;
            }
            else{
                cout << "The edge or the vertices could not be found." << endl;
            }
        }
        else if(input[0] == '5'){
            char label1[32], label2[32];
            cout << "Enter label of starting vertex: ";
            cin.getline(label1, 32);
            cout << "Enter label of destination vertex: ";
            cin.getline(label2, 32);
            graph.printPathDetails(label1, label2);
        }
        else if(input[0] == 'c'){
            graph.clear();
            cout << "Graph cleared." << endl;
        }
        else if(input[0] == 'q'){
            break;
        }
        else if(input[0] == '0'){
            cout << "What Descartes did was a good step. You have added much several ways, and especially in taking the colors of thin plates into philosophical consideration.\nIf I have seen further it is by standing on the shoulders of giants.\n-- Isaac Newton" << endl;
        }
        else{
            cout << "Command not recognized." << endl;
        }
        cout << "Press enter to continue.";
        cout << endl;
        cin.ignore();
        cin.get();
    }
    return 0;
}