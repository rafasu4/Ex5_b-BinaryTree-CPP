
#pragma once
#include "Node.hpp"
#include "PreOrederIterator.hpp"
#include "InOrderIterator.hpp"
#include "PostOrderIterator.hpp"
#include <iostream>

namespace ariel
{
    template <typename T>
    class BinaryTree
    {
        Node<T> *root;

    public:
        /*Constructor.*/
        BinaryTree() : root(nullptr) {}

        BinaryTree(const BinaryTree &other)
        {
            //if there is a root to the tree
            if (other.root != nullptr)
            {
                root = new Node<T>(other.root->value);
                deepCopy(other.root, root);
            }
        }

        ~BinaryTree()
        {
            removeAllNodes(root);
        }

           /*Adds a new root to the tree. In case one already exist, replace it.*/
        BinaryTree &add_root(const T &t)
        {
            //if tree doesn't have root - create new one
            if (root == nullptr)
            {
                root = new Node<T>(t);
            }
            else
            {
                root->value = t; //updating value
            }
            return *this;
        }
        

        /*Adds left son to the first argument. If one already exist, replaces it.*/
        BinaryTree &add_left(T father, T leftSon)
        {
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
            //if father node doesn't have a left son - create new one
            if (f->left == nullptr)
            {
                Node<T> *left = new Node<T>(leftSon);
                f->left = left;
                left->parent = f; //updating new node's father
            }
            else
            {
                f->left->value = leftSon; //updating value
            }
            return *this;
        }

        /*Adds right son to the first argument. If one already exist, replaces it.*/
        BinaryTree &add_right(T father, T rightSon)
        {
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
            //if father node doesn't have a left son - create new one
            if (f->right == nullptr)
            {
                Node<T> *right = new Node<T>(rightSon);
                f->right = right;
                right->parent = f; //updating new node's father
            }
            else
            {
                f->right->value = rightSon; //updating value
            }
            return *this;
        }

       

        /************************************* Operator Functions *************************************/
        friend ostream &operator<<(ostream &os, const BinaryTree &tree) { return os; }
        
        BinaryTree &operator=(const BinaryTree<T> &other)
        {
            //if it's not the same object
            if(this != &other){
                //if there is a root to deep copy
                if(other.root != nullptr){
                    root->value = other.root->value;
                    deepCopy(other.root, root);//copying the rest of the tree
                }
            }
            return *this;
        }

        auto begin() { return begin_inorder(); }

        auto end() { return end_inorder(); }

        auto begin_preorder(){return PreOrderIterator<T>(root);}

        auto end_preorder(){return PreOrderIterator<T>(nullptr);}

        auto begin_inorder(){return InOrderIterator<T>(root);}

        auto end_inorder(){return InOrderIterator<T>(nullptr);}

        auto begin_postorder(){return PostOrderIterator<T>(root);}

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
        /*Deletes all nodes from the tree.*/
        void removeAllNodes(Node<T> *node)
        {
            if (node != nullptr)
            {
                removeAllNodes(node->right);
                removeAllNodes(node->left);
                delete node;
            }
        }

        /*Returns In-Order Iterator to the given value in the tree. Returns null pointer if one doesn't exist. */
        Node<T> *search(Node<T> *node, T value)
        {
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
    };

}