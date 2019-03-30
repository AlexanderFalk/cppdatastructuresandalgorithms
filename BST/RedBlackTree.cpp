#include <iostream>

template <typename T>
struct BSTree {

    private:
        enum Color {RED,BLACK};
        struct Node {
            T data;
            Node *left, *right;
            Color color;
        };
        Node *root;

    public:
        BSTree() {
            root = NULL;
        }

        // Not allowed to change the memberfunction
        bool isEmpty() const { return root==NULL; }
        struct Node* parent(struct Node* node);
        struct Node* grand_parent(struct Node* node);
        struct Node* sibling(struct Node* node);
        struct Node* uncle(struct Node* node);
        void insert(T data);
        void print_inorder();
        void inorder(Node* root);
        void recolor(BSTree *bstree);
        bool inbalanced();
};


struct Node* parent(struct Node* node) {
    return node->
};


/**
 * When a node is inserted, the node is considered to be RED by default
 * */
template <typename T>
void BSTree<T>::insert(T data) {
    Node *node = new Node;
    Node *parent;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->color = Color::RED;
    parent = NULL;

    // If the root node is NULL, then set the new node to the root node, and make the root node BLACK.
    if(isEmpty()) {
        root = node;
        root->color = Color::BLACK;
    }
    else {
        // Create a current node and set it to the root. 
        Node *current;
        current = root;

        // Loop through the tree to find the node's parent. 
        while(current) {
            parent = current;
            if(node->data > current->data) {
                current = current->right;
                if(node->color == Color::BLACK) {
                    // Parent Node is BLACK, therefore I am RED
                    current->color = Color::RED;
                } else {
                    current->color = Color::BLACK;
                }
            } else {
                current = current->left;
                if(node->color == Color::BLACK) {
                    // Parent Node is BLACK, therefore I am RED
                    current->color = Color::RED;
                } else {
                    current->color = Color::BLACK;
                }
            } 
        }

        if (node->data < parent->data) {
            parent->left = node;
        } else {
            parent->right = node;
        }
        
    }
}

template <typename T>
void BSTree<T>::print_inorder() {
    inorder(root);
}
template <typename T>
void BSTree<T>::inorder(Node *node) {
    if(node != NULL) {
        if(node->left) inorder(node->left);
        std::cout << " " << node->data << " ";
        if(node->right) inorder(node->right);
    }
    else return;
}


int main() {
    BSTree<int> tree;
    tree.insert(2);
    tree.insert(5);
    tree.insert(8);
    tree.print_inorder();
    return 0;
}