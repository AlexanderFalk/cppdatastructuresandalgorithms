#include <iostream>
#include <utility>

enum Color {RED,BLACK};

template <typename Key, typename Value>
struct Node {
    Key key;
    Value value;
    Node *left, *right, *parent;
    Color color;
};

template <typename Key, typename Value, typename Compare = std::less<Key>>
struct RBTree {
    private:
        static Node<Key, Value> *root;
        //using const_iterator = Iterator;
    public:        
        // Iterator class to be used to access nodes of RBT
        struct Iterator { 
            private: 
                const Node<Key, Value>* current_node;
            public: 
            Iterator() noexcept : 
                current_node (root) { }
        
            Iterator(const Node<Key, Value>* parent_node) noexcept : 
                current_node (parent_node) { } 
        
            Iterator& operator=(Node<Key, Value>* parent_node) 
            { 
                this->current_node = parent_node; 
                return *this; 
            } 
    
            // Prefix ++ overload 
            Iterator& operator++() 
            { 
                if (current_node->left != NULL)
                    current_node = current_node->left;
                else
                    current_node = current_node->right;
                return *this; 
            } 
    
            // Postfix ++ overload 
            Iterator operator++(int) 
            { 
                Iterator iterator = *this; 
                ++*this; 
                return iterator; 
            } 
    
            bool operator!=(const Iterator& iterator) 
            { 
                return current_node != iterator.current_node; 
            } 
    
            int operator*() 
            { 
                return current_node->key; 
            } 
        };

        RBTree() {
            root = NULL;
        }

        RBTree(const Compare &comp) {
            // NOT IMPLEMENTED YET
        }

        ~RBTree() {
           //delete_node();
        }

        using key_type = Key;
        using mapped_type = Value;
        using value_type = std::pair<const key_type, mapped_type>;
        using key_compare = Compare;
        using iterator = Iterator;

        bool isEmpty() const { return root==NULL; }

        Node<key_type, mapped_type>* get_root() const {return root;};

        Node<key_type, mapped_type>* get_parent(Node<key_type, mapped_type>* node) const;

        Node<key_type, mapped_type>* get_grand_parent(Node<key_type, mapped_type>* node) const;

        Node<key_type, mapped_type>* sibling(Node<key_type, mapped_type>* node) const;

        Node<key_type, mapped_type>* uncle(Node<key_type, mapped_type>* node) const;

        void rotate_left(Node<key_type, mapped_type>* node);

        void rotate_right(Node<key_type, mapped_type>* node);

        std::pair<iterator, bool> insert(const value_type &value);

        //std::pair<iterator, bool> insert(value_type &&value);

        void repair(Node<key_type, mapped_type>* node);

        void delete_node(Node<key_type, mapped_type>* node);

        void dump(Node<key_type, mapped_type>* node, int tabs);

        void dump();

        // Forward declaration must be done 
        // in the same access scope 
        struct Iterator; 

        // Root of RBT wrapped in Iterator type 
        Iterator begin() 
        { 
            return Iterator(root); 
        } 

        // End of RBT wrapped in Iterator type 
        Iterator end() 
        { 
            return Iterator(nullptr); 
        } 
};