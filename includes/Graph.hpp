#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.hpp"

class Graph {
private:
    VertexList graph;

    bool    _isCycleUtil(int, bool *, int);
    int     _vertexId(int);
    int     _valueById(int);

public:

    void    addEdge(int, int);
    void    removeEdge(int, int);
    void    addVertex(int);
    void    removeVertex(int);
    void    print();
    bool    isTree();
};

#endif // !GRAPH_H