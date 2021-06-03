#include "BinaryTree.hpp"
#include "stdlib.h"

using namespace std;
using namespace ariel;

int main(){
    BinaryTree<int> tree;
    int option = 0;
    int value, fatherValue = 0;
    cout << "Welcom to Binary Tree program!\n";
    do{
        cout << endl <<endl;
        cout << "Please choose from the following:\n";
        cout << "0 - Exit the program.\n";
        cout << "1 - Add a new root to the tree.\n";
        cout << "2 - Add a left successor to existing node.\n";
        cout << "3 - Add a right successor to existing node.\n";
        cout << "4 - Print the tree.\n";
        cout << "Your choosing: ";
        cin >> option;
        cout << endl;
        switch (option)
        {
        //add root            
        case 1:
            cout<< "Enter a value: ";
            cin >> value;
            tree.add_root(value);
            cout << "The new root value is " + to_string(value)<<endl;
            break;
        //add left successor to a node
        case 2:
            cout<< "Enter the value of the father node: ";
            cin >> fatherValue;
            cout<< "\nEnter the value of the left node: ";
            cin >> value;
            try{
                tree.add_left(fatherValue, value);
            }catch(exception){
                 system("Color B5");
                cout<<"\nTree doesn't have a node with " + to_string(fatherValue) + " value!\n";
                break;
            }
            cout << to_string(value)+" is now the left son of "+ to_string(fatherValue)<<endl;
            break;
        //add right successor to a node
        case 3:
            cout<< "Enter the value of the father node: ";
            cin >> fatherValue;
            cout<< "\nEnter the value of the right node: ";
            cin >> value;
            try{
                tree.add_right(fatherValue, value);
            }catch(exception){
                cout<<"\nTree doesn't have a node with " + to_string(fatherValue) + " value!\n";
                break;
            }
            cout << to_string(value)+" is now the right son of "+ to_string(fatherValue)<<endl;
            break;
        case 4:
            cout << tree<<endl;
            break;
        default:
            break;
        }
        value = fatherValue = 0;
    }while (option != 0);
    
    
    return 0;
}