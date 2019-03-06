#include <Graph.h>

template <typename T>
void UndirectedGraph::insert(Node &from, Node &to, T data){
    Edge *edge = new Edge;
    edge->from = from;
    edge->to = to;
    edge->data = data;
}