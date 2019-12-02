#include "../includes/Edge.hpp"
/*
*   Contructor de initializare cu parametri.
*/

Edge::Edge(int value = -1, Edge* next = nullptr) {
    this->value = value;
    this->next = next;
}

/*
*   Contructor de copiere.
*/

Edge::Edge(const Edge* edge) {
    this->value = edge->value;
    this->next = edge->next;
}

/*
*   Destructor recursiv.
*/

Edge::~Edge()
{
    if(this->next)
        delete this->next;
    this->next = nullptr;
}

/*
*   Constructor de initializare fara parametri.
*/

EdgeList::EdgeList() {
    this->edge = nullptr;
    this->size = 0;
}

/*
*   Destructor
*/

EdgeList::~EdgeList()
{
    if (this->edge)
        delete this->edge;
    this->edge = nullptr;
    this->size = 0;
}

/*
*   Metoda care imi verifica daca lista de Edge-uri este goala.
*
*   @return ->  True daca e goala, False in caz contrar.
*/

bool EdgeList::isEmpty() {
    return size == 0;
}

/*
*   Verifica daca lista contine o instanta cu valoarea primita ca parametru.   
*
*   @param  value   ->  Valoarea ce este cautata
*   @return ->  True daca e prezenta, Fals in caz contrar.
*/

bool    EdgeList::contains(int value) {
    if( !(this->isEmpty()) ) {
        Edge* crt = this->edge;
        while(crt != nullptr) {
            if(crt->value == value)
                return true;
            crt =  crt->next;
        }
    }
    return false;
}

/*
*	Metoda care imi adauga un Edge la capatul listei
*/

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
            return ;
        }
    }
    this->size++;
}

/*
*   Metoda respectiva imi sterge din lista mea Edge-ul cu valoarea
*       pe care o primeste ca parametru.
*/

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
        return ;
    }
    this->size--;
}

/*
*	Metoda imi sterge primul element din capul listei
*
*	@return	->	valoarea ce a fost stearsa.
*/

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
    return toRet;
}

/*
*	Supraincarcarea operatorului de indexare pentru a accesa mai usor elementele
*	 din lista mea.
*	
*	@param	index ->	Pozitia pe care dorim sa o accesam  0 <= index < size.
*	@return	Valoarea ce a fost identificata pe pozitia solicitata.
*/

int     EdgeList::operator[](int index) {
    Edge* crt;

    if(index < this->size && index >= 0) {
        crt = this->edge;
        while(index > 0) {
            crt = crt->next;
            index--;
        }
    }
    else {
        return -1;
    }
    return crt->value;
}

/*
*	Supraincarcarea operatorului de introducere in stream.
*/

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
