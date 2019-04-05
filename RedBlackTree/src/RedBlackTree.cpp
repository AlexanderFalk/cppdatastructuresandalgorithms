#include <string>
#include <assert.h>
#include <RedBlackTree.h>

template <typename Key, typename Value>
struct Node_comparator {
    bool operator()(const Node<Key, Value>& node1, const Node<Key, Value>& node2) {
        if(node1.key == node2.key) 
            return true;
        return false;
    }
};

template <typename Key, typename Value, typename Compare>
Node<Key, Value>* RBTree<Key, Value, Compare>::get_parent(Node<Key, Value>* node) const {
    return node->parent;
};

template <typename Key, typename Value, typename Compare>
Node<Key, Value>* RBTree<Key, Value, Compare>::get_grand_parent(Node<Key, Value>* node) const {
    Node<Key, Value> *parent = get_parent(node);
    if(parent == NULL)
        return NULL; // No Parent = No Grand Parent
    return parent;
};

template <typename Key, typename Value, typename Compare>
Node<Key, Value>* RBTree<Key, Value, Compare>::sibling(Node<Key, Value>* node) const {
    Node<Key, Value> *parent = get_parent(node);
    if(parent == NULL)
        return NULL; // No Parent = No Grand Parent
    if(node == parent->left) 
        return parent->right;
    else 
        return parent->left;
};

template <typename Key, typename Value, typename Compare>
Node<Key, Value>* RBTree<Key, Value, Compare>::uncle(Node<Key, Value>* node) const {
    Node<Key, Value> *parent = get_parent(node);
    Node<Key, Value> *grand_parent = get_grand_parent(node);
    if(grand_parent == NULL) // No Grand Parent = No Uncle
        return NULL;
    return sibling(parent);
};

template <typename Key, typename Value, typename Compare>
void RBTree<Key, Value, Compare>::rotate_left(Node<Key, Value>* node) {
    Node<Key, Value>* new_node;
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

template <typename Key, typename Value, typename Compare>
void RBTree<Key, Value, Compare>::rotate_right(Node<Key, Value>* node) {
    Node<Key, Value>* new_node;
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
 * When a node is inserted, the node is conbranchred to be RED by default. 
 * 
 * Based on one of the four outcomes, we are going to fix it by some properties a RBT has: 
 * Property 1 (every node is either red or black) and Property 3 (all leaves are black) always holds.
 * Property 2 (the root is black) is checked and corrected with case 1.
 * Property 4 (red nodes have only black children) is threatened only by adding a red node, repainting a node from black to red, or a rotation.
 * Property 5 (all paths from any given node to its leaves have the same number of black nodes) is threatened only by adding a black node, repainting a node, or a rotation.
 * */

template <typename Key, typename Value, typename Compare>
auto RBTree<Key, Value, Compare>::insert(const value_type &value) -> std::pair<iterator, bool> {
    // Create a Current node and set it to the root to traverse. 
    Node<Key, Value> *node, *parent, *current;
    parent = NULL;
    node = root;

    while(node) {
        // Set parent to the current node
        parent = node;
        if(value.first < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    if(!parent) {
        current = root = new Node<Key, Value>;
        current->key = value.first;
        current->value = value.second;
        current->color = BLACK;
        current->parent = current->left = current->right = NULL;
        std::cout << "KEY: " << current->key << "\n";
        std::cout << "VALUE " << current->value << "\n";
    } else {
        current = new Node<Key, Value>;
        current->key = value.first;
        current->value = value.second;
        current->color = Color::RED;
        current->parent = parent;
        current->left = current->right = NULL;
        std::cout << "KEY: " << current->key << "\n";
        std::cout << "VALUE " << current->value << "\n";

        //bool isMatched = false;

        RBTree<Key, Value, Compare>::Iterator itr;
        for(itr = begin(); itr != end(); itr++) {
            // If we find a match in the RBT, then we leave, since we already have an existing key. 
            std::cout << *itr << "\n";
        }
        if(current->key < parent->key) {
            parent->left = current;
        } else {
            parent->right = current;
        }
    }

    // The next steps checks whether the RBT hold its rules
    // Create a temporary uncle node
    Node<Key, Value> *uncle;
    bool branch;
    // The while loop continues as long as the parent of the current node is not null and it is RED
    while(current->parent && current->parent->color == RED) {
        // If the parent of the current node is equal to its grandparents left node, then set grandparents right to the uncle
        if((branch = (current->parent == current->parent->parent->left))) {
            uncle = current->parent->parent->right;
        } else {
            // Else set the uncle to the grand parents left node.
            uncle = current->parent->parent->left;
        }

        // If the uncle is NOT NULL and it is RED, then set the currents parent to BLACK
        // Set Uncle to BLACK
        // Set Grand Parent to RED
        // And set current to the grand parent
        if(uncle && uncle->color == RED) {
            current->parent->color = BLACK;
            uncle->color = BLACK;
            current->parent->parent->color = RED;
            current = current->parent->parent;
        } else {
            // 
            if(current == (branch ? current->parent->right : current->parent->left)) {
                current = current->parent;
                branch ? rotate_left(current) : rotate_right(current);
            }

            current->parent->color = BLACK;
            current->parent->parent->color = RED;
            branch ? rotate_right(current->parent->parent) : rotate_left(current->parent->parent);
        }
    }

    root->color = BLACK;
    // Everything went good, return
    return std::make_pair(current, false);
}

template <typename Key, typename Value, typename Compare>
void RBTree<Key, Value, Compare>::dump() {
    dump(root, 0); 
}

template <typename Key, typename Value, typename Compare>
void RBTree<Key, Value, Compare>::dump(Node<Key, Value>* node, int tabs)
  {
    if (!node) {
      return;
    }

    dump(node->left, tabs + 1);

    for (int i = 0; i < tabs; ++i) {
      std::cout << "\t\t";
    }
    std::cout << node->key << (node->color ? "B" : "R") << "\n";

    dump(node->right, tabs + 1);
  }


int main() {
    RBTree<int, std::string, Node_comparator<int, std::string>> tree;
    std::pair <int,std::string> foo = std::make_pair (10,"asdasd");
    //tree.insert(foo);
    // tree.insert(5, "okj");
    // tree.insert(8, "as23");

    // tree.insert(22, "ikn");
    // tree.insert(3, "ushgre");
    // tree.insert(4, "sekjnr");
    // tree.insert(7, "iljreg");
    // tree.insert(99, "slejgls");
    // tree.insert(26, "sejnlths");
    
    // tree.dump();
    return 0;
}