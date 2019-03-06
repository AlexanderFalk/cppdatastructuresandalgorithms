#include <iostream>
// http://www.cplusplus.com/forum/general/1551/
template <typename T>
struct BSTree {

    private:
        struct Node {
            T data;
            Node *left, *right;
        };
        Node *root;

    public:
        BSTree() {
            root = NULL;
        }

        // Not allowed to change the memberfunction
        bool isEmpty() const { return root==NULL; }
        void insert(T data);
        void remove(T data);
        bool search(T data);
        T minValue(Node* node);
        void print_inorder();
        void inorder(Node* root);
};

template <typename T>
void BSTree<T>::insert(T data) {
    Node *node = new Node;
    Node *parent;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    parent = NULL;

    // If the root node is NULL, then set the new node to the root node. 
    if(isEmpty()) root = node;
    else {
        // Create a current node and set it to the root. 
        Node *current;
        current = root;

        // Loop through the tree to find the node's parent. 
        while(current) {
            parent = current;
            if(node->data > current->data) current = current->right;
            else current = current->left;
        }

        if (node->data < parent->data) {
            parent->left = node;
        } else {
            parent->right = node;
        }
        
    }
}

template <typename T>
void BSTree<T>::remove(T data) {

    bool foundMatch = false;
    if(isEmpty()) {
        std::cout << "The tree is empty. None to remove." << std::endl; 
        return;
    }

    Node* current = root;
    Node* parent;

    while(current != NULL) {
        if(current->data == data) {
            foundMatch = true;
            break;
        } else {
            parent = current;
            if(data>current->data) current = current->right;
            else current = current->left;   
        }
    }
    if(!foundMatch) {
        std::cout << "No data has been found with the argument" << std::endl;
        return;
    }

    /* There are three cases, where we need to react, when removing a node:
     1. We're removing a leaf node
             In this case, we are setting the corresponding link of the parent to NULL and remove the node
     2. We're removing a node with a single child
             The node is going to be cut from the tree and then links the single child directly to the parent of the removed node
     3. we're removing a node with 2 children
             This is complex. We need to find a minimum in the right subtree to be removed. Then we replace the minimum node with the node to be removed. 
             We now have two nodes with the same value. Now we can remove the node, we found the minimum value from. 
    */

    // #1 No childs
    if(current->left == NULL && current->right == NULL) {
        if(parent->left == current) delete parent->left;
        if(parent->right == current) delete parent->right;

    }
    
    // #2 A single child
    if((current->left == NULL && current->right != NULL) || current->left != NULL && current->right == NULL) {
        if(current->left != NULL && parent->left == current) {
            parent->left = current->left;
            delete current;
        } else if(current->right != NULL && parent->right == current) {
            parent->right = current->right;
            delete current;
        }
    }

    // #3 Two children
    if(current->left != NULL && current->right != NULL) {
        // Check the left node of the currents right if it is null
        if((current->right)->left == NULL) {
            // Check the right node of the currents right if it is null. If it is, then we delete if without worrying
            if((current->right)->right == NULL) {
                current->data = (current->right)->data;
                delete current->right;
                return;
            } else {
                // Otherwise, we need to remember to swap the pointer of the current right to the deleted nodes right. 
                current->data = (current->right)->data;
                current->right = (current->right)->right;
                delete (current->right)->right;
                return;
            }
        }

        Node *auxiliary = current;
        // Zigzagging through the tree to get the last minimum value 
        while((auxiliary->right)->left != NULL) {
            if(auxiliary->left == NULL) {
                current->data = auxiliary->data;
                delete auxiliary;
            }
        }
    }
}

template <typename T>
bool BSTree<T>::search(T data) {
    if(isEmpty()) {
        std::cout << "The tree is empty. None to remove." << std::endl; 
        return false;
    }

    Node *current = root;
    Node *parent;
    while(current != NULL) {
        if(current->data == data) {
            std::cout << "Found a match!" << std::endl; 
            return true;
        } else {
            parent = current;
            if(data>current->data) current = current->right;
            else current = current->left;   
        }
    }
    std::cout << "Found NO match!" << std::endl; 
    return false;
}

// Used to find the minimum value
template <typename T>
T BSTree<T>::minValue(Node *node){
    if(node->left == NULL) {
        return node->data;
    } else {
        node->left->minValue();
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
    tree.insert(4);
    tree.insert(12);
    tree.insert(11);
    tree.print_inorder();
    std::cout << "\n";
    tree.remove(5);
    tree.print_inorder();
    tree.search(8);
    return 0;
}