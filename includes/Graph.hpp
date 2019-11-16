#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.hpp"

class Graph {
private:
    VertexList graph;

    bool isCycleUtil(int, bool *, int);
public:

    void    addEdge(int, int);
    void    removeEdge(int, int);
    void    addVertex(int);
    void    removeVertex(int);
    bool    isTree();
    void    print();
};

void    Graph::addVertex(int value) {
    graph.addVertex(value);
}

void    Graph::addEdge(int source, int destination) {
    if (graph.contains(source)) {
        if (graph.contains(destination)) {
            graph.getVertex(source)->edgeList.addEdge(destination);
            graph.getVertex(destination)->edgeList.addEdge(source);
        }
        else {
            cerr << "No such destination : { " << destination << " }\n";
            return ; 
        }
    }
    else {
        cerr << "No such source : { " << source << " }\n";
        return ; 
    }
}

void Graph::removeVertex(int value) {
    if ( !(this->graph.isEmpty()) && (this->graph.contains(value) ) ) {
        Vertex* crt = this->graph.vertex;
        Vertex* prev = this->graph.vertex;
        while (crt != nullptr && crt->value != value) {
            prev = crt;
            crt = crt->nVertex;
        }
        if (crt == this->graph.vertex) {
            this->graph.vertex->edgeList.popFront();
        }
        else {
            prev->nVertex = crt->nVertex;
        }
        crt->nVertex = nullptr;
        // EdgeList toRemove;
        while ( !(crt->edgeList.isEmpty()) ) {
            this->graph.getVertex(crt->edgeList.popFront())->edgeList.removeEdge(value);
        }
        delete crt;
        this->graph.size--;
    }
    else {
        cerr << "No vertex with value : { " << value << " }\n";
    }
}

void    Graph::print() {
    cout << this->graph;
}

bool    Graph::isCycleUtil(int v, bool* visited, int parent) {
    visited[v] = true;

    Edge* crt = this->graph.getVertex(v)->edgeList.edge;

    while(crt->next != nullptr) {
        if (!visited[crt->value]) {
            if (isCycleUtil(crt->value, visited, v))
                return true;
        }
        else {
            if (crt->value != parent)
                return true;
        }
        crt = crt->next;
    }
    return false;
}

bool    Graph::isTree() {
    bool* visited = new bool[this->graph.size];
    int index = 0;

    for (int i = 0; i < this->graph.size; i++)
        visited[i] = false;
    
    Vertex* crt = this->graph.vertex;
    while (crt->nVertex != nullptr) {
        if (!visited[crt->value]) {
            if (isCycleUtil(crt->value, visited, -1))
                return true;
        }
    }
}


#endif // !GRAPH_H