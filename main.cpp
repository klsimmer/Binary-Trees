//
//  main.cpp
//  hw5
//
//  Created by Kaytlin Simmer on 4/12/20.
//  Copyright © 2020 Kaytlin Simmer. All rights reserved.
//

#include <iostream>
//#include"ArgumentManager.h"
#include <string>
#include <fstream>
#include <queue>
#include <sstream>
using namespace std;

class BinaryTree
{
private:
    //node declaration
    struct node
    {
        int key;
        node* left;
        node* right;
        int height;
    };
    
    //root
    node* root;
    
    //add node
    void addLeafPrivate(int key, node* ptr)
    {
        if (root == NULL)
        {
            root = createLeaf(key);
        }
        else if (key < ptr->key)
        {
            if (ptr->left != NULL)
            {
                addLeafPrivate(key, ptr->left);
            }
            else
            {
                ptr->left = createLeaf(key);
            }
        }
        else if (key > ptr->key)
        {
            if (ptr->right != NULL)
            {
                addLeafPrivate(key, ptr->right);
            }
            else
            {
                ptr->right = createLeaf(key);
            }
        }
        //else
       // {
            //cout<<"ERROR: The key has already been added"<<endl;
       // }
    }
    
    //in order traversal
    void printInOrderPrivate(node* ptr)
    {
        if (root == NULL)
        {
            cout<<"Tree is empty"<<endl;
        }
        else
        {
            if (ptr->left != NULL)
            {
                printInOrderPrivate(ptr->left);
            }
            cout<<ptr->key<<" ";
            if (ptr->right != NULL)
            {
                printInOrderPrivate(ptr->right);
            }
        }
    }
    
    //Preorder traversal
    void printPreorderPrivate(node* ptr)
    {
        if (root == NULL)
        {
            cout<<"Tree is empty"<<endl;
        }
        else
        {
        cout << ptr->key << " ";
        if (ptr->left != NULL)
        {
        printPreorderPrivate(ptr->left);
        }
        if (ptr->right != NULL)
        {
        printPreorderPrivate(ptr->right);
        }
        }
    }
    
    void printPostorderPrivate(node* ptr)
    {
        if (root == NULL)
        {
            cout<<"Tree is empty"<<endl;
        }
        else
        {
            if (ptr->left != NULL)
            {
        printPostorderPrivate(ptr->left);
            }
            if (ptr->right != NULL)
            {
        printPostorderPrivate(ptr->right);
            }
        cout << ptr->key << " ";
        }
    }
    
    //return node
    node* returnNodePrivate(int key, node* ptr)
    {
        if (ptr == NULL)
        {
            return NULL;
        }
        else
        {
            if (ptr->key == key)
            {
                return ptr;
            }
            else
            {
                if (key < ptr-> key)
                {
                    return returnNodePrivate(key, ptr->left);
                }
                else
                {
                    return returnNodePrivate(key, ptr->right);
                }
            }
        }
    }
    
    
    
    //find smallest
    int findSmallestPrivate(node* ptr)
    {
        if (root == NULL)
        {
            cout<<"Tree is empty"<<endl;
            return -10000000;
        }
        else
        {
            if (ptr->left != NULL)
            {
                return findSmallestPrivate(ptr->left);
            }
            else
            {
                return ptr->key;
            }
        }
    }
    
    //remove node
    void removeNodePrivate(int key, node* parent)
    {
        if (root == NULL)
        {
            cout<<"Tree is empty"<<endl;
        }
        else
        {
            if (root->key == key)
            {
                removeRootMatch();
            }
            else
            {
                if (key < parent->key && parent->left != NULL)
                {
                    parent->left->key == key ?
                    removeMatch(parent, parent->left, true):
                    removeNodePrivate(key, parent->left);
                }
                else if (key > parent->key && parent->right != NULL)
                {
                    parent->right->key == key ?
                    removeMatch(parent, parent->right, false):
                    removeNodePrivate(key, parent->right);
                }
                else
                {
                    cout<<"ERROR: Key not found"<<endl;
                }
            }
        }
    }
    
    //remove helper
    void removeRootMatch()
    {
        if (root == NULL)
        {
            cout<<"Tree is empty"<<endl;
        }
        else
        {
            node* delptr = root;
           // int rootkey = root->key;
            int smallestInRightSubTree;
            //case 0 - 0 children
            if (root->left == NULL && root->right == NULL)
            {
                root = NULL;
                delete delptr;
            }
            //case 1 - 1 child
            else if (root->left == NULL && root->right != NULL)
            {
                root = root->right;
                delptr->right = NULL;
                delete delptr;
            }
            else if (root->left != NULL && root->right == NULL)
            {
                root = root->left;
                delptr->left = NULL;
                delete delptr;
            }
            //case 2 - has 2 children
            else
            {
                smallestInRightSubTree = findSmallestPrivate(root->right);
                removeNodePrivate(smallestInRightSubTree, root);
                root->key = smallestInRightSubTree;
            }
        }
    }
    
    //remove helper
    void removeMatch(node* parent, node* match, bool left)
    {
        if (root == NULL)
        {
            cout << "Tree is empty" <<endl;
        }
        else
        {
            node* delptr;
           // int matchkey = match->key;
            int smallestInRightSubTree;
            //Case 0 - Match has 0 children
            if (match->left == NULL && match->right == NULL)
            {
                delptr = match;
                left == true ?
                parent ->left = NULL :
                parent -> right = NULL;
                delete delptr;
            }
            //Case 1 - Match has 1 child
            else if (match->left == NULL && match->right != NULL)
            {
                left == true ?
                parent ->left = match->right :
                parent -> right = match -> right;
                delptr = match;
                delete delptr;
            }
            else if (match->left != NULL && match->right == NULL)
            {
                left == true ?
                parent ->left = match->left :
                parent -> right = match ->left;
                match->left = NULL;
                delptr = match;
                delete delptr;
            }
            //Case 2 - Match has 2 children
            else
            {
                smallestInRightSubTree = findSmallestPrivate(match->right);
                removeNodePrivate(smallestInRightSubTree, match);
                match->key = smallestInRightSubTree;
            }
        }
    }
    
public:
    //constructor
    BinaryTree()
    {
        root = NULL;
    }
    
    //create node
    node* createLeaf(int key)
    {
        node* n = new node;
        n->key = key;
        n->left = NULL;
        n->right = NULL;
        return n;
    }
    
    //add node
    void addLeaf(int key)
    {
        addLeafPrivate(key, root);
    }
    
    // in order traversal
    void printInOrder()
    {
        printInOrderPrivate(root);
    }
    
    //preorder traversal
    void printPreorder()
    {
        printPreorderPrivate(root);
    }
    
    //postorder traversal
    void printPostorder()
    {
        printPostorderPrivate(root);
    }
    
    //return node
    node* returnNode (int key)
    {
        return returnNodePrivate(key, root);
    }
    
    //return root
    int returnRootKey()
    {
        if (root!=NULL)
        {
            return root->key;
        }
        else
        {
            return -100000000;
        }
    }
    
    //print children of node
    void printChildren (int key)
    {
        node* ptr = returnNode(key);
        if (ptr == NULL)
        {
            cout<<"Key is not in tree"<<endl;
        }
        else
        {
            cout<<"Parent Node = "<<ptr->key<<endl;
            ptr->left == NULL ?
            cout<<"Left child = NULL"<<endl:
            cout<<"left child = "<<ptr->left->key<<endl;
            ptr->right == NULL ?
            cout<<"Right child = NULL"<<endl:
            cout<<"Right child = "<<ptr->right->key<<endl;
        }
    }
    
    //find smallest
    int findSmallest()
    {
        return findSmallestPrivate(root);
    }
    
    //remove
    void removeNode(int key, node* parent)
    {
        removeNodePrivate(key, root);
    }
    
    //level
    void printLevel(node* ptr, int level)
    {
        //tree empty
        if (ptr == NULL)
        {
            return;
        }
        //tree has only one level
        if (level == 1)
        {
            cout << ptr->key << " ";
        }
        //tree has multiple levels
        else if (level > 1)
        {
            printLevel(ptr->left, level - 1);
            printLevel(ptr->right, level - 1);
        }
    }

};

int main()
{
    //ArgumentManager am(argc, argv);
    // const string input = am.get("input");
    //const string command = am.get("command");
     //const string output = am.get("output");
    
   // string input = "/Users/kaytlinsimmer/Desktop/hw5/input51.txt";
    string input = "/Users/kaytlinsimmer/Desktop/hw5/input52.txt";
    //string command = "/Users/kaytlinsimmer/Desktop/hw5/command51.txt";
    string command = "/Users/kaytlinsimmer/Desktop/hw5/command52.txt";
    string output = "/Users/kaytlinsimmer/Desktop/hw5/ans51.txt";
    int aKey;
    BinaryTree myTree;
    string str;
    
    //open input
    ifstream inFS (input);
    ifstream cmdFS(command);
    
    //check if open or empty
    if (!inFS.is_open())
    {
    cout << "Error: Could not open file!" << endl;
    return -1;
    }
    if (inFS.peek() == std::ifstream::traits_type::eof())
    {
    cout << "Error: File is empty!" << endl;
    return -1;
    }
    
    //add input to tree
    while (!inFS.eof())
    {
        inFS>>aKey;
        cout<<aKey<<"-";
        myTree.addLeaf(aKey);
        
    }
    cout<<endl;
    
    //process commands
    while(getline(cmdFS,str))
    {
        if (str.find("Inorder Traversal") != string::npos)
        {
            myTree.printInOrder();
            cout<<endl;
        }
        else if (str.find("Preorder Traversal") != string::npos)
        {
            myTree.printPreorder();
            cout<<endl;
        }
        else if (str.find("Postorder Traversal") != string::npos)
        {
            myTree.printPostorder();
            cout<<endl;
        }
        else if (str.find("Level") != string::npos)
        {
            int pos = str.find(" ");
            string sInt = str.substr(pos+1,1);
            int pri = stoi(sInt);
            cout<<pri<<endl;
            myTree.printLevel(myTree.returnNode(myTree.returnRootKey()),pri);
        }
    }
    
    
    

}
