#include "Node.hpp"
#include <stack>

using namespace std;
namespace ariel
{
    template <typename T>
    class InOrderIterator
    {
        /*The object currently pointing at.*/
        Node<T> *current;
        /*Hold the nodes of the tree in in-order travel-set.*/
        std::stack<Node<T> *> node_stk;

    public:
        /*Constructor.*/
        InOrderIterator(Node<T> *node = nullptr)
        {
            Node<T> *curr = node;
            //adding all the left branch
            while (curr != nullptr)
            {
                node_stk.push(curr);
                curr = curr->left;
            }
            //if the tree has no nodes
            if (node_stk.empty())
            {
                current = nullptr;
            }
            else
            {
                current = node_stk.top();//pointing to the first element in in-order travel set
            }
        };

        /*Returns the current node value.*/
        T &operator*() const{ return current->value;}

        /*Returns the address of the current node.*/
        T *operator->() const{ return &(current->value);}

        /*Points to the next element in in-order travel-set.*/
        InOrderIterator &operator++()
        {
            //if the stack still has elements
            if (!node_stk.empty())
            {
                Node<T> *temp = node_stk.top();
                node_stk.pop();
                //adding the right sub-tree of temp
                if (temp->right != nullptr){
                    node_stk.push(temp->right);
                    temp = node_stk.top()->left;
                    //adding the left branch of new temp
                    while (temp != nullptr)
                    {
                        node_stk.push(temp);
                        temp = temp->left;
                    }
                }
                //if there are no more elements to travel 
                if (node_stk.empty())
                {
                    current = nullptr;
                }
                else{
                    current = node_stk.top();//pointing to the next element in in-order travel-set
                    }
            }
            //if the stack is empty - no more elements
            else{
                current = nullptr;
            }
            return *this;
        }
        /*Returns current element before going to the next element.*/
        InOrderIterator operator++(int){
            const InOrderIterator temp = *this;
            ++*this;
            return temp;
        }
        /*Equal operator.*/
        bool operator==(const InOrderIterator &other) const
        {
            return other.current == current;
        }
        /*Inequal operator.*/
        bool operator!=(const InOrderIterator &other) const
        {
            return other.current != current;
        }
    };
}