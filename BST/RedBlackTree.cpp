#include <iostream>
#include <assert.h>

enum Color {RED,BLACK};

template <typename T>
struct Node {
    T data;
    Node *left, *right, *parent;
    Color color;
};

template <typename T>
struct RBTree {
    private:
        Node<T> *root;

    public:
        RBTree() {
            root = NULL;
        }
        
        // Not allowed to change the memberfunction
        bool isEmpty() const { return root==NULL; }
        Node<T>* get_root() const {return root;};
        Node<T>* get_parent(Node<T>* node) const;
        Node<T>* get_grand_parent(Node<T>* node) const;
        Node<T>* sibling(Node<T>* node) const;
        Node<T>* uncle(Node<T>* node) const;
        void rotate_left(Node<T>* node);
        void rotate_right(Node<T>* node);
        void insert(T data);
        void case_1_fix(Node<T>* node);
        void case_2_fix(Node<T>* node);
        void case_3_fix(Node<T>* node);
        void case_4_fix(Node<T>* node);
        void case_4_fix_step2(Node<T>* node);
        void repair(Node<T>* node);

        void print_inorder();
        void printBT(const std::string& prefix, const Node<T> *node, bool isLeft);
        void dump(Node<T>* node, int tabs);
        void dump();
        void inorder(Node<T>* root);
};

template <typename T>
Node<T>* RBTree<T>::get_parent(Node<T>* node) const {
    return node->parent;
};

template <typename T>
Node<T>* RBTree<T>::get_grand_parent(Node<T>* node) const {
    Node<T> *parent = get_parent(node);
    if(parent == NULL)
        return NULL; // No Parent = No Grand Parent
    return parent;
};

template <typename T>
Node<T>* RBTree<T>::sibling(Node<T>* node) const {
    Node<T> *parent = get_parent(node);
    if(parent == NULL)
        return NULL; // No Parent = No Grand Parent
    if(node == parent->left) 
        return parent->right;
    else 
        return parent->left;
};

template <typename T>
Node<T>* RBTree<T>::uncle(Node<T>* node) const {
    Node<T> *parent = get_parent(node);
    Node<T> *grand_parent = get_grand_parent(node);
    if(grand_parent == NULL) // No Grand Parent = No Uncle
        return NULL;
    return sibling(parent);
};

template <typename T>
void RBTree<T>::rotate_left(Node<T>* node) {
    Node<T>* new_node;
    new_node = node->right;
    node->right = new_node->left;
    if (new_node->left) {
      new_node->left->parent = node;
    }

    new_node->parent = node->parent;
    new_node->left = node;

    if (!node->parent) {
      root = new_node;
    }
    else if (node == node->parent->left) {
      node->parent->left = new_node;
    } else {
      node->parent->right = new_node;
    }
    node->parent = new_node;
};

template <typename T>
void RBTree<T>::rotate_right(Node<T>* node) {
    Node<T>* new_node;
    new_node = node->left;
    node->left = new_node->right;
    if (new_node->right) {
      new_node->right->parent = node;
    }

    new_node->parent = node->parent;
    new_node->right = node;

    if (!node->parent) {
      root = new_node;
    }
    else if (node == node->parent->left) {
      node->parent->left = new_node;
    } else {
      node->parent->right = new_node;
    }
    node->parent = new_node;
};


/**
 * When a node is inserted, the node is considered to be RED by default. 
 * 
 * Based on one of the four outcomes, we are going to fix it by some properties a RBT has: 
 * Property 1 (every node is either red or black) and Property 3 (all leaves are black) always holds.
 * Property 2 (the root is black) is checked and corrected with case 1.
 * Property 4 (red nodes have only black children) is threatened only by adding a red node, repainting a node from black to red, or a rotation.
 * Property 5 (all paths from any given node to its leaves have the same number of black nodes) is threatened only by adding a black node, repainting a node, or a rotation.
 * */
template <typename T>
void RBTree<T>::insert(T data) {
    // Create a Current node and set it to the root to traverse. 
    Node<T> *node, *parent, *current;
    parent = NULL;
    node = root;

    while(node) {
        // Set parent to the current node
        parent = node;
        if(node->data > current->data) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if(!parent) {
        current = root = new Node<T>;
        current->data = data;
        current->color = Color::BLACK;
        current->parent = current->left = current->right = NULL;
    } else {
        current = new Node<T>;
        current->data = data;
        current->color = Color::RED;
        current->parent = parent;
        current->left = current->right = NULL;
        
        if(current->data < parent->data) {
            parent->left = current;
        } else {
            parent->right = current;
        }
    }
    repair(current);
}

/**
 * After it is inserted, we are going to fix the tree - if needed.
 * We are looking at different properties to fix it:
 * 
 * 1) N is the root node, i.e., first node of red–black tree
 * 2) N's parent (P) is black
 * 3) P is red (so it can't be the root of the tree) and N's uncle (U) is red
 * 4) P is red and U is black
 * */
template<typename T>
void RBTree<T>::repair(Node<T>* node) {
    if(get_parent(node) == NULL) {
        case_1_fix(node);
    } else if(get_parent(node)->color == Color::BLACK) {
        case_2_fix(node);
    } else if(uncle(node) != NULL && uncle(node)->color == Color::RED) {
        case_3_fix(node);
    } else {
        case_4_fix(node);
    }
}

/**
 * Case 1: Current node is the root and therefore repainted BLACK to satisfy property 2 (root is black) and 
 * property 5 (black-height - all paths from a given node to a leaf has the same amount of black nodes)
 * */
template<typename T>
void RBTree<T>::case_1_fix(Node<T>* node) {
    if(get_parent(node) == NULL)
        node->color = Color::BLACK;
}

template<typename T>
void RBTree<T>::case_2_fix(Node<T>* node) {
    return;
}

/**
 * If both the parent P and the uncle U are red, then both of them can be repainted black and the grandparent G becomes red
 * */
template<typename T>
void RBTree<T>::case_3_fix(Node<T>* node) {
    get_parent(node)->color = Color::BLACK;
    uncle(node)->color = Color::BLACK;
    get_grand_parent(node)->color = Color::RED;
    // The grandparent may violate Property 2 (The root is black) if it is the root or Property 4 (Both children of every red node are black) if it has a red parent.
    repair(get_grand_parent(node));
}


/**
 * The parent P is red but the uncle U is black
 * */
template<typename T>
void RBTree<T>::case_4_fix(Node<T>* node) {
    Node<T> *parent = get_parent(node);
    Node<T> *grand_parent = get_grand_parent(node);

    if(node == parent->right && parent == grand_parent->left) {
        rotate_left(node);
        node = node->left;
    } else if(node == parent->left && parent == grand_parent->right) {
        rotate_right(node);
        node = node->right;
    }

    case_4_fix_step2(node);
}


template<typename T>
void RBTree<T>::case_4_fix_step2(Node<T>* node) {
    Node<T> *parent = get_parent(node);
    Node<T> *grand_parent = get_grand_parent(node);

    if(node == parent->left) 
        rotate_right(node);
    else
        rotate_left(node);

    parent->color = Color::BLACK;
    grand_parent->color = Color::RED;
}



template <typename T>
void RBTree<T>::print_inorder() {
    inorder(root);
}
template <typename T>
void RBTree<T>::inorder(Node<T> *node) {
    if(node != NULL) {
        if(node->left) inorder(node->left);
        std::cout << " " << node->data << " " << node->color;
        if(node->right) inorder(node->right);
    }
    else return;
}

template<typename T>
void RBTree<T>::dump() {
    dump(root, 0); 
}

template<typename T>
void RBTree<T>::dump(Node<T>* node, int tabs)
  {
    if (!node) {
      return;
    }

    dump(node->left, tabs + 1);

    for (int i = 0; i < tabs; ++i) {
      std::cout << "\t\t";
    }
    std::cout << node->data << (node->color ? "B" : "R") << "\n";

    dump(node->right, tabs + 1);
  }


int main() {
    RBTree<int> tree;
    tree.insert(2);
    tree.insert(5);
    tree.insert(8);

    tree.insert(22);
    tree.insert(3);
    tree.insert(4);
    
    tree.dump();
    return 0;
}