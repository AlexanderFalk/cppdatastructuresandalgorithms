#include <UGraph.h>
#include <iostream>

template <typename T>
void UGraph<T>::addEdge(Node<T> *v, Node<T> *w) {
    v->adjList.push_back(w);
    adj.push_back(v);
    E++;
}

template <typename T>
void UGraph<T>::printDatList() {
    for(int i = 0; i < adj.size(); ++i)
        std::cout << adj[i]->data << "\n";
}

int main() {
    UGraph<int> graph(5);

    Node<int> *v = new Node<int>();
    v->data = 3;
    Node<int> *w  = new Node<int>();
    w->data = 5;

    graph.addEdge(v, w);
    graph.printDatList();
}