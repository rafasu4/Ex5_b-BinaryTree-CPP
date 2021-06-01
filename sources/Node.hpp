#pragma once
// #include <iostream>
// using namespace std;
// namespace ariel{
//     template<typename T>
//      struct Node
//         {
//             T data;
//             Node *right;
//             Node *left;
//             Node *parent;
        
//             Node(){right = left = nullptr;}
//             Node(const T &data) : data(data) {right = left = parent = nullptr;}
//             void add_leftN (Node* other){left = other;}
//             void add_rightN (Node* other){right = other;}
//         };
// }
namespace ariel{
    template<typename T>
    class Node{
    public:
        T value;
        Node *left= nullptr;
        Node *right= nullptr;
        Node *parent= nullptr;
        Node()= default;
        Node(const T &val) : value(val), parent(nullptr), left(nullptr), right(nullptr){
            this->value = val;
        };
        bool operator==(const Node &rhs) const {
            return rhs.value==this->value&&rhs.left==this->left&&rhs.right==this->right&&this->parent==rhs.parent;
        }

        bool operator!=(const Node &rhs) const {
            return rhs.value!=this->value&&rhs.left!=this->left&&rhs.right!=this->right&&this->parent!=rhs.parent;
        }
//            friend std::ostream& operator<<(std::ostream& os,const Node& node){return os;};
    };
}