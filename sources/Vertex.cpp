#include "../includes/Vertex.hpp"

/*
*   Constructor de initializare cu parametri
*/

Vertex::Vertex(int value = -1, Vertex* nVertex = nullptr) {
    this->value = value;
    this->nVertex = nVertex;
}

/*
*   Destructor care imi apeleaza si destructorul listei de adiacenta
*/

Vertex::~Vertex() {
    this->edgeList.~EdgeList();
    if(nVertex != nullptr)
        delete nVertex;
    nVertex = nullptr;
}

/*
*   Am supraincarcat operatorul de atribuire pentru a ma asigura 
*   ca pointerii vor fi conectati corect in urma unei atribuiri de obiecte.
*/

Vertex Vertex::operator=(const Vertex& other) {
    this->edgeList = other.edgeList;
    this->nVertex = other.nVertex;
    this->value = other.value;
}

/*
*   Contructor de initializare fara parametri.
*/

VertexList::VertexList() {
    this->vertex = nullptr;
    this->size = 0;
}

/*
*   Destructor recursiv
*/

VertexList::~VertexList() {
    delete this->vertex;
    this->vertex = nullptr;
    this->size = 0;
}

/*
*   Metoda care imi verifica daca lista de Vertexuri este goala.
*
*   @return ->  True daca e goala, False in caz contrar.
*/

bool VertexList::isEmpty() {
    return this->size == 0;
}

/*
*   Verifica daca lista contine o instanta cu valoarea primita ca parametru.   
*
*   @param  value   ->  Valoarea ce este cautata
*   @return ->  True daca e prezenta, Fals in caz contrar.
*/

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
            return false;
        }
    }
    return false;
}

/*
*	Metoda care imi adauga un Vertex la capatul listei
*/

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
            return ;
        }
    }
    this->size++;
}

/*
*	Metoda imi returneaza un nod din lista mea care are valoarea solicitata.
*
*	@param	value	-> valoarea cautata.
*	@return	Un pointer catre Vertex-ul gasit, nullptr daca nu exista un astfel
*		de nod cu astfel de valoare.
*/

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
            return nullptr;
        }
    }
    return nullptr;
}

/*
*	Metoda imi sterge primul element din capul listei
*
*	@return	->	valoarea ce a fost stearsa.
*/

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
    return toRet;
}

/*
*	Supraincarcarea operatorului de indexare pentru a accesa mai usor elementele
*	 din lista mea.
*	
*	@param	index ->	Pozitia pe care dorim sa o accesam  0 <= index < size.
*	@return	Valoarea ce a fost identificata pe pozitia solicitata.
*/

int     VertexList::operator[](int index) {
    Vertex* crt;
    if(index < this->size && index >= 0) {
        crt = this->vertex;
        while(index > 0) {
            crt = crt->nVertex;
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
            os <<"\n";
            crt = crt->nVertex;
            size--;
        }
    }
    return os;
}
