#ifndef EDGE_H
#define EDGE_H

#include <iostream>

using namespace std;

class Edge {
public:
    int value;
    Edge* next;

    Edge();
    Edge(int, Edge *);
    Edge(const Edge *);
    ~Edge();    
};

class EdgeList {
public:
    Edge*   edge;
    int     size;   
    
    EdgeList();
    ~EdgeList();


    void    addEdge(int);
    void    removeEdge(int);
    int     popFront();
    int     operator[](int);
    bool    contains(int);
    bool    isEmpty();

friend  ostream& operator<<(ostream&, const EdgeList &);
};

#endif // !Edge_H