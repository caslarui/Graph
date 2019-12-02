#ifndef VERTEX_H
#define VERTEX_H

#include "Edge.hpp"

class Vertex {
public:
    EdgeList edgeList;
    Vertex* nVertex;
    int value;
 
 
    Vertex(int, Vertex *);
    ~Vertex();


    Vertex  operator=(const Vertex&);
};

class VertexList {
public:
    Vertex* vertex;
    int     size;

    VertexList();
    ~VertexList();

    Vertex* getVertex(int);
    void    addVertex(int);
    bool    contains(int);
    bool    isEmpty();
    int     popFront();
    int     operator[](int);

friend  ostream& operator<<(ostream&, const VertexList &);
};

#endif // !VERTEX_HPP
