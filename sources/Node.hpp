#pragma once
namespace ariel{
    template<typename T>
     struct Node
        {
            T value;
            Node *right;
            Node *left;
        
            Node(){right = left = nullptr;}
            Node(const T &value) : value(value) {right = left  = nullptr;}
            void add_leftN (Node* other){left = other;}
            void add_rightN (Node* other){right = other;}
        };
}
