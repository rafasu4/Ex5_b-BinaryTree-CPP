#include "Node.hpp"
#include <stack>

using namespace std;
namespace ariel
{
    template <typename T>
    class PreOrderIterator
    {
    public:
        Node<T> *current;
        std::stack<Node<T> *> node_stk;

    public:
        /*Constructor.*/
        PreOrderIterator(Node<T> *node = nullptr)
        {
            current = node;
            if(current != nullptr){
                node_stk.push(current);
            }
        };

        /*Returns the current node value.*/
        T &operator*() const{return current->value;}

        /*Returns the address of the current node.*/
        T *operator->() const{ return &(current->value);}

        /*Points to the next element in in-order travel-set.*/
        PreOrderIterator &operator++()
        {
            //if the stack still has elements
            if (!node_stk.empty())
            {
                Node<T> *temp = node_stk.top();
                node_stk.pop();
                //adding the right sub-tree of temp
                if (temp->right != nullptr)
                {
                    node_stk.push(temp->right);
                }
                 if (temp->left != nullptr)
                {
                    node_stk.push(temp->left);
                }
                //if there are no more elements to travel 
                if (node_stk.empty())
                {
                    current = nullptr;
                }
                else
                {
                    current = node_stk.top();//pointing to the next element in in-order travel-set
                }
            }
            //if the stack is empty - no more elements
            else
            {
                current = nullptr;
            }
            return *this;
        }

        PreOrderIterator operator++(int)
        {
            const PreOrderIterator temp = *this;
            ++*this;
            return temp;
        }

        bool operator==(const PreOrderIterator &other) const
        {
            return other.current == current;
        }

        bool operator!=(const PreOrderIterator &other) const
        {
            return other.current != current;
        }
    };
}