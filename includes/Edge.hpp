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

Edge::Edge(int value = -1, Edge* next = nullptr) {
    this->value = value;
    this->next = next;
}

Edge::Edge(const Edge* edge) {
    this->value = edge->value;
    this->next = edge->next;
}

Edge::~Edge()
{
    if(next)
        delete next;
    next = nullptr;
}

class EdgeList {
public:
    Edge*   edge;
    int     size;   
    
    EdgeList();
    ~EdgeList();
    void    addEdge(int);
    void    removeEdge(int);
    int     popFront();
    bool    contains(int);
    bool    isEmpty();

friend  ostream& operator<<(ostream&, const EdgeList &);
};

EdgeList::EdgeList() {
    // cout << "Constructor\n";
    this->edge = nullptr;
    this->size = 0;
}

EdgeList::~EdgeList()
{
    delete this->edge;
    this->edge = nullptr;
    this->size = 0;
}

bool EdgeList::isEmpty() {
    return size == 0;
}

bool    EdgeList::contains(int value) {
    if( !(this->isEmpty()) ) {
        Edge* crt = this->edge;
        while(crt != nullptr) {
            if(crt->value == value)
                return true;
            crt =  crt->next;
        }
    }
    else {
        cerr << "Edge List is empty\n";
    }
    return false;
}

void    EdgeList::addEdge(int value) {
    if (this == nullptr || this->isEmpty()) {
        this->edge = new Edge(value);
    }
    else {
        if ( !(this->contains(value)) ) {
            Edge* crt = this->edge;
            while(crt->next != nullptr)
                crt =  crt->next;
            crt->next = new Edge(value);
        }
        else {
            cerr << "Edge with value { " << value << " } already exists\n";
            return ;
        }
    }
    this->size++;
}

void    EdgeList::removeEdge(int value) {
    if (this->contains(value) && !this->isEmpty()) {
        Edge* crt = this->edge;
        Edge* prev = this->edge;
        while (crt != nullptr && crt->value != value) {
            prev = crt;
            crt = crt->next;
        }
        if (crt == this->edge) {
            this->edge = this->edge->next;
        }
        else {
            prev->next = crt->next;
        }
        crt->next = nullptr;
        delete crt;
    }
    else {
        cerr << "No edge with such value : { " << value <<" }\n";
        return ;
    }
    this->size--;
}

int     EdgeList::popFront() {
    int toRet = -1;
    if ( !(this->isEmpty()) ) {
        Edge* tmp = this->edge;
        this->edge = this->edge->next;
        tmp->next = nullptr;
        toRet = tmp->value;
        delete tmp;
        this->size--;
    }
    else {
        cerr << "Edge list is empty, no elements to pop" << endl;
    }
    return toRet;
}

ostream& operator<<(ostream& os, const EdgeList& list) {
    int size = list.size;
    os << "{ ";
    Edge* crt = list.edge;
    if (crt != nullptr) {
        while (size > 0) {
            os << crt->value <<" ";
            crt = crt->next;
            size--;
        }
    }
    os << " }";
    return os;
}



#endif // !Edge_H