#include <vector>
#include <iostream>
#include <string>
#include <map>

struct Vertex {
    typedef std::pair<int, Vertex*> ve;
    std::vector<ve> adj;
    std::string name;
    Vertex(std::string s) : name(s) {}
};

class Graph {
    public:
        typedef std::map<std::string, Vertex*> vmap;
        vmap work;
        void addvertex(const std::string&);
        void addedge(const std::string& from, const std::string& to, int cost);
};

void Graph::addvertex(const std::string& name) {
    vmap::iterator itr = work.find(name);
    if(itr == work.end()) {
        Vertex *v;
        v = new Vertex(name);
        work[name] = v;
        return;
    }
    std::cout << "Vertex already exists!" << std::endl;
}

void Graph::addedge(const std::string& from, const std::string& to, int cost) {
    Vertex *f = (work.find(from)->second);
    Vertex *t = (work.find(to)->second);
    std::pair<int, Vertex*> edge = std::make_pair(cost, t);
    f->adj.push_back(edge);
}


int main() {
    Graph graph;
    graph.addvertex("firstname");
    graph.addvertex("secondname");
    graph.addedge("firstname", "secondname", 4);
}