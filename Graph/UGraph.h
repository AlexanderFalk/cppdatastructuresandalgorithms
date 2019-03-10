/**
 * Algorthims 4th edition - Robert Sedgewick
 * Chapter 4. Page 526
 * From Java to C++
 * */
#include <vector>
template <typename T>
struct Node {
    T data;
    std::vector< Node<T>* > adjList;
};

template <typename T>
struct UGraph {
    const int V; // Number of vertices
    int E; // Number of edges
    // Adjacency lists
    std::vector< Node<T>* > adj;

    void addEdge(Node<T> *v, Node<T> *w);
    void printDatList();
    UGraph(int x) : V(x) {}
};