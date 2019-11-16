#include "../includes/Graph.hpp"

int main() {
    Graph test;

    test.addVertex(1);
    test.addVertex(2);
    test.addVertex(3);
    test.addVertex(4);
    test.addEdge(2,3);
    test.addEdge(2,3);
    test.addEdge(3,4);
    test.addEdge(2,4);
    test.print();
    test.removeVertex(6);
    test.addEdge(1,3);
    test.addEdge(3,1);
    cout << "After delete\n";
    test.print();
    return 0;
}