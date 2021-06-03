#pragma once
#include "Node.hpp"
#include "PreOrederIterator.hpp"
#include "InOrderIterator.hpp"
#include "PostOrderIterator.hpp"
#include <iostream>

namespace ariel
{
    /*This class represents a binary tree which composed of nodes - where each node holds value and
    pointers to its two successors - right and left sons.*/
    template <typename T>
    class BinaryTree
    {
        /*This tree root.*/
        Node<T> *root;

    public:

    /************************************* C'tors *************************************/
        /*C'tor..*/
        BinaryTree() : root(nullptr) {}
        /*Copy c'tor.*/
        BinaryTree(const BinaryTree &other){
            //if there is a root to the tree
            if (other.root != nullptr)
            {
                root = new Node<T>(other.root->value);
                deepCopy(other.root, root);
            }
        }
        /*Move constructor.*/
        BinaryTree(BinaryTree &&other) noexcept: root(move(other.root)){}
        /*Destructor.*/
        ~BinaryTree(){
            removeAllNodes(root);//recursive function which deletes all the nodes in the tree.
        }
        /*Adds a new root to the tree. In case one already exist, replace it.*/
        BinaryTree &add_root(const T t){
            //if tree doesn't have root - create new one
            if (root == nullptr){
                root = new Node<T>(t);
            }
            else{
                root->value = t; //updating value
            }
            return *this;
            }
        /*Adds left son to the first argument. If one already exist, replaces it.*/
        BinaryTree &add_left(T father, const T leftSon){
            if (root == nullptr){
                throw invalid_argument("No root in the tree!");
            }
            Node<T> *f = search(root, father);
            //if father node isn't in the tree
            if (f == nullptr)
            {
                throw invalid_argument("No such node in the tree!");
            }
            //if father node doesn't have a left son - create new one
            if (f->left == nullptr)
            {
                Node<T> *left = new Node<T>(leftSon);
                f->left = left;
            }
            else
            {
                f->left->value = leftSon; //updating value
            }
            return *this;
        }
        /*Adds right son to the first argument. If one already exist, replaces it.*/
        BinaryTree &add_right(T father, T rightSon){
            if (root == nullptr)
            {
                throw invalid_argument("No root in the tree!");
            }
            Node<T> *f = search(root, father);
            //if father node isn't in the tree
            if (f == nullptr)
            {
                throw invalid_argument("No such node in the tree!");
            }
            //if father node doesn't have a right son - create new one
            if (f->right == nullptr)
            {
                Node<T> *right = new Node<T>(rightSon);
                f->right = right;
            }
            else
            {
                f->right->value = rightSon; //updating value
            }
            return *this;
        }

        const Node<T>* getRoot() const{return root;}

        /************************************* Operators Functions *************************************/
        friend ostream &operator<<(ostream &os, const BinaryTree &tree) {
            BinaryTree::printBT(os, "", tree.getRoot() , false);
             return os; }
        
        BinaryTree &operator=(const BinaryTree<T> other){
            //if it's not the same object
            if(this != &other){
                removeAllNodes(root);//releasing all previouse nodes in the tree
                //if there is a root to deep copy
                if(other.root != nullptr){
                    root = new Node<T>(other.root->value);
                    deepCopy(other.root, root);//copying the rest of the tree
                }
            }
            return *this;
        }
        /*Move assignment operator.*/
        BinaryTree &operator=(BinaryTree<T> &&other) noexcept{
            //if it's not the same object
            if(this != &other){
                removeAllNodes(root);//releasing all previouse nodes in the tree
                //if there is a root to deep copy
                if(other.root != nullptr){
                    root = new Node<T>(other.root->value);
                    moveCopy(other.root, root);//copying the rest of the tree
                }
            }
            return *this;
        }
        /************************************* APIs *************************************/
        /*Returns a pointer to the start of the tree in in-order travel-set.*/
        auto begin() { return begin_inorder(); }
        /*Returns a pointer to the end of the tree in in-order travel-set.*/
        auto end() { return end_inorder(); }
        /*Returns a pointer to the start of the tree in pre-order travel-set.*/
        auto begin_preorder(){return PreOrderIterator<T>(root);}
        /*Returns a pointer to the end of the tree in pre-order travel-set.*/
        auto end_preorder(){return PreOrderIterator<T>(nullptr);}
        /*Returns a pointer to the start of the tree in in-order travel-set.*/
        auto begin_inorder(){return InOrderIterator<T>(root);}
        /*Returns a pointer to the end of the tree in in-order travel-set.*/
        auto end_inorder(){return InOrderIterator<T>(nullptr);}
        /*Returns a pointer to the start of the tree in post-order travel-set.*/
        auto begin_postorder(){return PostOrderIterator<T>(root);}
        /*Returns a pointer to the end of the tree in post-order travel-set.*/
        auto end_postorder(){return PostOrderIterator<T>();}
        
        private:
        /*Deep copy of a tree.*/
        void deepCopy(const Node<T> *other, Node<T> *current){
            if(other->left != nullptr){
                current->left = new Node<T>(other->left->value);
                deepCopy(other->left, current->left);
            }
            if(other->right != nullptr){
                current->right = new Node<T>(other->right->value);
                deepCopy(other->right, current->right);
            }
        }
        /*Move copy.*/
        void moveCopy(Node<T> *other, Node<T> *current){
            if(other->left != nullptr){
                current->left = other->left;
                moveCopy(current->left, other->left);
            }
             if(other->right != nullptr){
                current->right = other->right;
                moveCopy(current->right, other->right);
            }
            delete other;
        }
        /*Deletes all nodes from the tree.*/
        void removeAllNodes(Node<T> *node){
            if (node != nullptr)
            {
                removeAllNodes(node->right);
                removeAllNodes(node->left);
            }
            delete node;
        }
        /*Returns In-Order Iterator to the given value in the tree. Returns null pointer if one doesn't exist. */
        Node<T> *search(Node<T> *node, T value){
            if (node->value == value)
            {
                return node;
            }
            Node<T> *ans = nullptr;
            if (node->left != nullptr && ans == nullptr)
            {
                ans = search(node->left, value);
                if (ans != nullptr)
                {
                    return ans;
                }
            }
            if (node->right != nullptr && ans == nullptr)
            {
                ans = search(node->right, value);
                if (ans != nullptr)
                {
                    return ans;
                }
            }
            return ans;
        }
        /*Taken from GeeksForGeeks.*/
        static void printBT(ostream& os,  const string& prefix, const Node<T>* node, bool isLeft){
            if( node != nullptr ){
                os << prefix;
                if(isLeft){
                    os << "├──";
                }
                else{
                    os << "└──" ;
                }
                // print the value of the node
                os << node->value << endl;
                // enter the next tree level - left and right branch
                printBT(os, prefix + (isLeft ? "│   " : "    "), node->left, true);
                printBT(os, prefix + (isLeft ? "│   " : "    "), node->right, false);
            }
        }
    };
}