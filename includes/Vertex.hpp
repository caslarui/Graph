#ifndef VERTEX_H
#define VERTEX_H

#include "Edge.hpp"

class Vertex
{
public:
    EdgeList edgeList;
    Vertex* nVertex;
    int value;
 
 
    Vertex(int, Vertex *);
    ~Vertex();
};

Vertex::Vertex(int value = -1, Vertex* nVertex = nullptr) {
    this->value = value;
    this->nVertex = nVertex;
}

Vertex::~Vertex() {
    this->edgeList.~EdgeList();
    if(nVertex != nullptr)
        delete nVertex;
    nVertex = nullptr;
}

class VertexList
{
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

friend  ostream& operator<<(ostream&, const VertexList &);
};

VertexList::VertexList() {
    this->vertex = nullptr;
    this->size = 0;
}

VertexList::~VertexList() {
    delete this->vertex;
    this->vertex = nullptr;
    this->size = 0;
}

bool VertexList::isEmpty() {
    return this->size == 0;
}

bool VertexList::contains(int value) {
    Vertex* crt;
    if ( !(this->isEmpty()) ) {
        crt = this->vertex;
        while(crt != nullptr) {
            if (crt->value == value)
                return true;
            crt = crt->nVertex;
        }
    }
    else {
        if (crt == nullptr) {
            cerr << "No vertex with value : { " << value << " } in list\n";
            return false;
        }
        cerr << "Edge List is empty\n";
    }
    return false;
}

void VertexList::addVertex(int value) {
    if (this->isEmpty()) {
        this->vertex = new Vertex(value);
    }
    else {
        if ( !(this->contains(value)) ) {
            Vertex* crt = this->vertex;
            while(crt->nVertex != nullptr)
                crt =  crt->nVertex;
            crt->nVertex = new Vertex(value);
        }
        else {
            cerr << "Vertex with value { " << value << " } already exists\n";
            return ;
        }
    }
    this->size++;
}

Vertex* VertexList::getVertex(int value) {
        Vertex* crt;
    if ( !(this->isEmpty()) ) {
        crt = this->vertex;
        while(crt != nullptr) {
            if (crt->value == value)
                return crt;
            crt = crt->nVertex;
        }
    }
    else {
        if (crt == nullptr) {
            cerr << "No vertex with value : { " << value << " } in list\n";
            return nullptr;
        }
        cerr << "Edge List is empty\n";
    }
    return nullptr;
}

int VertexList::popFront() {
    int toRet = -1;
    if ( !(this->isEmpty()) ) {
        Vertex* tmp = this->vertex;
        this->vertex = this->vertex->nVertex;
        tmp->nVertex = nullptr;
        toRet = tmp->value;
        delete tmp;
        this->size--;
    }
    else {
        cerr << "Edge list is empty, no elements to pop" << endl;
    }
    return toRet;
}

ostream& operator<<(ostream& os, const VertexList& list) {
    int size = list.size;
    Vertex* crt = list.vertex;

    if(list.size == 0) {
        os << "[ ] x\n";
        return os;
    }
    if (crt != nullptr) {
        while (size > 0) {
            os << "[ ";
            os << crt->value << " ] => ";
            if( !(crt->edgeList.isEmpty()) ) {
                os << crt->edgeList;
            }
            os << "\n";
            crt = crt->nVertex;
            size--;
        }
    }
    return os;
}

#endif // !VERTEX_HPP
