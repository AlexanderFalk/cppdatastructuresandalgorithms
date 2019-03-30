template <typename T, typename W>
struct UndirectedGraph{
    private:
        struct Node {
            T data;
        }
        
        struct Edge {
            Node *from;
            Node *to;
            W weight;
        }

        Edge[] edges;

    public:
        void insert(Node &from, Node &to, T data, W weight);
        T search(T data);
        bool isEmpty();
        void remove(T data);
}