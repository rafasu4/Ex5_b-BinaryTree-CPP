#include "Node.hpp"
#include <stack>
using namespace std;
namespace ariel
{
    template <typename T>
    class PostOrderIterator
    {
    public:
         /*The object currently pointing at.*/
        Node<T> *current;
        /*Hold the nodes of the tree in in-order travel-set.*/
        std::stack<Node<T> *> node_stk;
        

    public:
        /*Constructor.*/
        PostOrderIterator(Node<T> *node = nullptr)
        {
            current = node;
            if (current != nullptr)
            {
                stack<Node<T> *> h;//creating a second stack for help
                h.push(current);
                while (!h.empty())
                {
                    Node<T>* temp = h.top();
                    h.pop();
                    node_stk.push(temp);//inserting the "in" node first - will be in the bottom of the original stack
                    //adding the left son (if exist) first for reverse order - will be on top of the original stack
                    if(temp->left != nullptr){
                        h.push(temp->left);
                    }
                    //adding the right son (if exist) second for reverse order - will be on after the too of the original stack
                    if(temp->right != nullptr){
                        h.push(temp->right);
                    }
                }
            current = node_stk.top();
            node_stk.pop();
            }
        };

        /*Returns the current node value.*/
        T &operator*() const{ return current->value;}

        /*Returns the address of the current node.*/
        T *operator->() const{ return &(current->value);}

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
        /*Returns current element before going to the next element.*/
        PostOrderIterator operator++(int)
        {
            const PostOrderIterator temp = *this;
            ++*this;
            return temp;
        }
        /*Equal operator.*/
        bool operator==(const PostOrderIterator &other) const{
            return other.current == current;}
        /*Inequal operator.*/
        bool operator!=(const PostOrderIterator &other) const
        {
            return other.current != current;
        }
    };
}