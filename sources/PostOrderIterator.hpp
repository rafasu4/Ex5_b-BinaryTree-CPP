#include "Node.hpp"
#include <stack>
using namespace std;
namespace ariel
{
    template <typename T>
    class PostOrderIterator
    {
    public:
        Node<T> *current;
        stack<Node<T> *> node_stk;
        

    public:
        /*Constructor.*/
        PostOrderIterator(Node<T> *node = nullptr)
        {
            current = node;
            if (current != nullptr)
            {
                stack<Node<T> *> h;
                h.push(current);
                while (!h.empty())
                {
                    Node<T>* temp = h.top();
                    h.pop();
                    node_stk.push(temp);
                    if(temp->left != nullptr){
                        h.push(temp->left);
                    }
                    if(temp->right != nullptr){
                        h.push(temp->right);
                    }
                }
            current = node_stk.top();
            node_stk.pop();
            }
        };

        /*Returns the current node value.*/
        T &operator*() const
        {
            return current->value;
        }

        /*Returns the address of the current node.*/
        T *operator->() const
        {
            return &(current);
        }

        /*Points to the next element in post-order travel-set.*/
        PostOrderIterator &operator++()
        {
            if(current != nullptr){
                if(!node_stk.empty()){
                    current = node_stk.top();
                    node_stk.pop();
               }
               else{
                   current = nullptr;
               }
            }
            return *this;
        }

        PostOrderIterator operator++(int)
        {
            const PostOrderIterator tmp = *this;
            ++*this;
            return tmp;
        }

        bool operator==(const PostOrderIterator &other) const
        {
            return other.current == current;
        }

        bool operator!=(const PostOrderIterator &other) const
        {
            return other.current != current;
        }
    };
}