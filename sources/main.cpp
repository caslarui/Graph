#include "../includes/Graph.hpp"

int main() {
    Graph graph;
    int N;
    int type;
    int nb1;
    int nb2;


    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> type;
        switch (type)
        {
        case 1:
            cin >> nb1;
            graph.addVertex(nb1);
            break;
        case 2:
            cin >> nb1 >> nb2;
            graph.addEdge(nb1, nb2);
            break;
        case 3:
            cin >> nb1;
            graph.removeVertex(nb1);
            break;
        case 4:
            cin >> nb1 >> nb2;
            graph.removeEdge(nb1, nb2);
            break;
        case 5:
            cout << graph.isTree() << endl;
            break;
        default:
            break;
        }
        // graph.print();
        // cout << endl;
    }
    return 0;
}