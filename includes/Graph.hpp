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

/*
*   Pentru a adauga un Vertex nou folosesc o metoda din clasa VertexList
*    care imi adauga la capatul listei un nou nod.
*
*   @param  value   ->  valoarea ce se va stoca in Vertex-ul nou.   
*/

void    Graph::addVertex(int value) {
    graph.addVertex(value);
}

/*
*   Functia imi adauga o legatura in ambele directii, intrucat este un graf neorientat.
*
*   @param  source      ->  Vertex-ul sursa
*   @param  destination ->  Vertex-ul destinatie
*/

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

/*
*   Functia imi sterge un Vertex din Graph.
*
*   @param value    ->  Valoarea nodului pe care dorim sa-l stergem.
*/

void Graph::removeVertex(int value) {
    // Verificam daca graful nu este vid si daca acesta contine valoarea pe care ne dorim sa o stergem.
    if ( !(this->graph.isEmpty()) && (this->graph.contains(value) ) ) {
        // Pentru a evita erorile de link editare care ar putea sa apara in urma stergerii
        //  am ales sa parcurg lista prin intermediul a 2 pointeri. Cu primul parcurg pana cand nu identific
        // nodul ce il voi sterge, iar cu precedentul refac legaturile astfel incat sa nu pierd date.
        Vertex* crt = this->graph.vertex;
        Vertex* prev = this->graph.vertex;

        // Parcurg lista pana cand nu ajung la capatul ei sau pana cand nu am gasit valoarea cautata.
        while (crt != nullptr && crt->value != value) {
            prev = crt;
            crt = crt->nVertex;
        }

        // Daca nodul pe care il vom sterge este defapt capul listei, atunci facem un Pop().
        if (crt == this->graph.vertex) {
            if (crt->edgeList.isEmpty()) {
                this->graph.popFront();
            }
            else {
                while ( !(crt->edgeList.isEmpty()) ) {
                    this->graph.getVertex(crt->edgeList.popFront())->edgeList.removeEdge(value);
                }
                this->graph.popFront();
                return ;
            }
        }
        else {
            prev->nVertex = crt->nVertex;
        }

        // Ma asigur ca urmatorul este pe nullptr pentru ca cand voi apela destructorul acestuia
        //  sa nu pierd datele din el.
        crt->nVertex = nullptr;

        // Daca Vertex-ul pe care il vom sterge are legaturi spre alte noduri, sau alte noduri
        // sunt legate cu el, trebuie sa le stergem.
        if (crt->edgeList.edge != nullptr) {
            while ( !(crt->edgeList.isEmpty()) ) {
                this->graph.getVertex(crt->edgeList.popFront())->edgeList.removeEdge(value);
            }
        }

        // Dupa ce am eliberat Vertex-ul si nu mai are legaturi putem sa il stergem.
        delete crt;
        this->graph.size--;
    }
    else {
        cerr << "No vertex with value : { " << value << " }\n";
    }
}

/*
*   Functia imi sterge legaturi in ambele directii, de la nodul sursa spre destinatie
*    si invers, de la destinatie la sursa.
*/

void Graph::removeEdge(int source, int destination) {
    if (graph.contains(source)) {
        if (graph.contains(destination)) {
            graph.getVertex(source)->edgeList.removeEdge(destination);
            graph.getVertex(destination)->edgeList.removeEdge(source);
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

/*
*   O functie ajutatoare care imi afiseaza Graful.
*/

void    Graph::print() {
    cout << this->graph;
}

/*
*   Este o functie ajutatoare care imi parcurge si imi determina daca exista un cliclu
*    in graph.
*   
*   @param currVertex   ->  Vertexul curent pe care ne aflam
*   @param visited      ->  Un vector in care salvez ca nodul a fost visitat
*   @param parent       ->  Vertexul sursa, carei ii aparte lista de adiacenta
*/

bool    Graph::_isCycleUtil(int currVertex, bool* visited, int parent) {
    // Marcam nodul care corespunde Vertexului curent ca fiind vizitat.
    visited[currVertex] = true;

    // Fac rost vertexul curent, in acesta este salvata totodata si lista de adiacenta de care
    //  voi avea nevoie ulterior ca sa identific Vertex-urile cu care acesta mai este legat.
    Vertex* edgeList = this->graph.getVertex(_valueById(currVertex)); 
    int edgeSize = edgeList->edgeList.size;

    // Verific conditia in care un Vertexul curent este liber, adica nu are conexiune cu alte
    //  noduri. Prin urmare Graful meu nu poate fi un arbore daca are un astfel de caz.
    if (edgeSize == 0)
        return true;

    // Verific cu ce alte Vertex-uri mai este conectat nodul meu curent.
    for (int i = 0; i < edgeSize; i++) {

        // Am supraincarcat operatorul de subscript[], acesta imi returneaza valoarea
        //  ce este stocata in lista pe pozitia "i". Iar in cazul de fata am nevoie de
        //  ID-ul nodului corespunzator, ci nu valoarea din acesta.
        int idVertex = _vertexId(edgeList->edgeList[i]);

        // Deoarece graful este neorientat, avem Edge-uri in ambele parti, prin urmare
        //  trebuie sa verificam toate nodurile mai putin cel sursa.
        if (idVertex != parent) {
            // Daca am depistat un nod care deja a fost vizitat atunci exista un ciclu
            if (visited[idVertex]) {
                edgeList = nullptr;
                return true;
            } 
            else {
                // In caz contrat, continuam sa parcurgem graful pana nu vizitam toate nodurile
                if (_isCycleUtil(idVertex, visited, currVertex)) {
                    edgeList = nullptr;
                    return true;
                }
            }
        }
    }
    edgeList = nullptr;
    return false;
}

/*
*   Folosind parcurgerea BFS, traversam graful nostru reprezentat printr-o
*   lista de adiacenta si verificam daca exista cicluri inchise sau noduri
*   neconectate.
*
*   @return True in cazul in care graful este arbore, False in caz contrat.
*/

bool    Graph::isTree() {
    if (this->graph.isEmpty())
        return true;

    bool* visited = new bool[this->graph.size];

    // Initializam vectorul nodurilor vizitate
    for (int i = 0; i < this->graph.size; i++) {
        visited[i] = false;
    }
    
    // Parcurgem toate vertexurile si le verificam listele de adiacenta.
    for (int i = 0; i < this->graph.size; i++) {
        if (visited[i] == false) {

            // Daca s-a depistat un Vertex care inca nu a fost verificat il verificam.
            if (this->_isCycleUtil(i, visited, -1)) {
                delete[] visited;
                return false;
            }
        }
    }
    delete[] visited;
    return true;
}

/*
*   Returneaza ID-ul Vertex-ului pe care il identificam in functie de
*   valoarea ce este salvata in nod.
*
*   @param value -> Valoarea nodului caruia am dori sa-i aflam index-ul.
*   @return ID-ul Nodului.
*/


int     Graph::_vertexId(int value) {
    if (this->graph.contains(value)) {
        for (int i = 0; i < this->graph.size; i++) {
            if (value == (this->graph[i]) )
                return i;
        }
    }
    else {
        cerr << "No vertex with value { " << value << " }\n";
    }
    return -1;
}

/*
*   Returneaza valoarea ce este stocata in Vertex-ul cu id-ul respectiv.
*   
*
*   @param Id -> este numarul de ordine ce ii corespune fiecarui Vertex.
*   @return Valoarea Vertex-ului.
*/
int     Graph::_valueById(int id) {
    if (id < this->graph.size) {
        for (int i = 0; i <= id; i++) {
            if (id == i)
                return this->graph[i];
        }
    }
    else {
        cerr << "ID : " << id << " out of bounds\n";
    }
    return -1;
}


#endif // !GRAPH_H