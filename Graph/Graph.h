template <typename T>
struct UndirectedGraph{
    private:
        struct Node {
            Node *node;
            T data;
        }
        struct Edge {
            Node *from;
            Node *to;
            T weight;
        }

    public:
        void insert(Node &from, Node &to, T weight);
        T search(T data);
        bool isEmpty();
        void remove(T data);
}