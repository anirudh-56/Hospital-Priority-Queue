/// @file prqueue.h
/// @author Anirudh Yallapragada, ayall2@uic.edu
/// @date November 8th, 2023
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class prqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;       // stored data for the p-queue
        bool dup;      // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;    // links to linked list of NODES with duplicate priorities
        NODE* left;    // links to left child
        NODE* right;   // links to right child
    };
    NODE* root; // pointer to root node of the BST
    int sz;     // # of elements in the prqueue
    NODE* curr; // pointer to next item in prqueue (see begin and next)
    
    void deleteRecur(NODE* node) {
        if(node == nullptr){
            return;
        }

        //Recursivley deleting each node
        deleteRecur(node->left);
        deleteRecur(node->right);

        NODE* temp = node->link;
        while(temp != nullptr){
            NODE* next = temp->link;
            delete temp;
            temp = next;
            sz--;
        }
        delete node;   
        sz--;     
    }

    // operator=
    void copyTree(NODE*& newNode, const NODE* node, NODE* parent = nullptr) {
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //

        if(node == nullptr){
            return;
        }

        //Copying values;
        newNode = new NODE();
        newNode->value = node->value;
        newNode->priority = node->priority;
        newNode->dup = node->dup;
        newNode->parent = parent;
        newNode->link = nullptr;
        

        //Recursively copying Tree
        copyTree(newNode->left, node->left, newNode);
        copyTree(newNode->right, node->right, newNode);    

        //Copying the duplicate values
        if(node->dup){
            NODE* currPrev = node->link;
            NODE* currNew = newNode;
            while(currPrev != nullptr){
                currNew->link = new NODE();
                currNew->link->value = currPrev->value;
                currNew->link->priority = currPrev->priority;
                currNew->link->dup = false;
                currNew->link->parent = newNode;
                currNew->link->link = nullptr;
                currNew = currNew->link;
                currPrev = currPrev->link;
            } 
        }    
    }

    void _recursiveString(NODE* node, ostream& output){
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
        if(node == nullptr){
            return;
        }
        _recursiveString(node->left, output); 
        if(node->dup){ //Recursivley printing any duplicate values
            NODE* temp = node;
            while(temp != nullptr){
                output << temp->priority << " value: " << temp->value << endl;
                temp = temp->link;
            }
        }
        else{ //Printing the values 
            output << node->priority << " value: " << node->value << endl;
        }
        _recursiveString(node->right, output);
    }

    bool equalsOverLoad(NODE* node1, NODE* node2) const{
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //

        if(node1 == nullptr && node2 == nullptr){
            return true;
        }

        if(node1 == nullptr || node2 == nullptr){
            return false;
        }

        if(node1->value != node2->value){
            return false;
        }

        if(!equalsOverLoad(node1->left, node2->left)){
            return false;
        }    

        if(!equalsOverLoad(node1->right, node2->right)){
            return false;
        }

        if(!equalsOverLoad(node1->link, node2->link)){
            return false;
        }   

        return true;
    }

public:

    // default constructor:
    prqueue() {
    
    // Creates an empty priority queue.
    // O(1)
        root = nullptr;
        sz = 0;
        curr = nullptr;
        
    }

    

    prqueue& operator=(const prqueue& other) {        
        if(this != &other){
            clear();
            copyTree(root, other.root);
            sz = other.sz;
        }
        return *this;
    }


    void clear() {
        //Clearing the list
        deleteRecur(root);
        root = nullptr;
        sz = 0;
        
    }
    

    ~prqueue() {
        
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
        clear();
        
    }
    

    void enqueue(T value, int priority) {
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities       

        NODE* newNode = new NODE;
        newNode->value = value;
        newNode->priority = priority;
        newNode->dup = false;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->parent = nullptr;
        newNode->link = nullptr;
        //Initializing a newNode and setting its associated values

        if(root == nullptr) { //If the tree is empty then the newNode is just the root
            root = newNode;
            sz++; //Size of 1 in the tree
            return;
        }

        NODE* curr = root; 
        NODE* prev = nullptr;
        //Two pointers to traverse through the tree

        while (curr != nullptr) {
            if(priority == curr->priority){ //Handling duplicates
                if(!curr->dup){ //If its not a duplicate
                    curr->dup = true;
                    curr->link = newNode;
                    newNode->parent = curr;
                    sz++;
                    return;
                }
                else{
                    NODE* temp = curr->link;
                    while(temp->link != nullptr){
                        temp = temp->link;
                    }
                    temp->link = newNode;
                    newNode->parent = curr;
                    sz++;
                    return;
                }
            }
            else if (priority < curr->priority){ //If priority is less than previous priority, curr is set to the left child
                    prev = curr;
                    curr = curr->left;
            }
            else if(priority > curr->priority){ //If priority is greater than previous priority, curr is set to the right child
                    prev = curr;
                    curr = curr->right;
            }   
        }


        if(priority < prev->priority){
            prev->left = newNode;
        }
        else if(priority > prev->priority){
            prev->right = newNode;
        }

        newNode->parent = prev;
        sz++;
        return; //Updating size and confirming insertion 
    }


    T dequeue() {
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities

        if(root == nullptr){ //If tree is empty
            return {}; //Return nothing, can't delete anything from an empty tree
        }
        
        NODE* currentNode = root;
        NODE* parentNode = nullptr;

        while(currentNode->left){
            parentNode = currentNode;
            currentNode = currentNode->left;
        }
        T valueOut = currentNode->value; //Value to be returned from priority queue


        if(currentNode->link){ 
            NODE* newNode = currentNode->link;
            if(parentNode){
                parentNode->left = newNode;
            }
            else{
                root = newNode;
            }
            newNode->left = currentNode->left;
            newNode->right = currentNode->right;
            newNode->parent = parentNode;
        }
        else{
            if(parentNode){
                parentNode->left = currentNode->right;
            }
            else{
                root = currentNode->right;
            }

            if(currentNode->right){
                currentNode->right->parent = parentNode;
            }
        }
        delete currentNode;
        sz--; //Decrementing size
        return valueOut; //Returning the next element from the priority queue, and confirming removal
    }


    int size() {
        // Returns the # of elements in the priority queue, 0 if empty O(1)
        return sz;
    
    }
    

    void begin() {
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //

        if(root != nullptr){ //If tree is not empty
            NODE* current = root; //Curr points to the root of tree
            while(current->left != nullptr){ //Traversing to the leftmost value, smallest value in the BST
                current = current->left; 
            }
            curr = current; //Curr points ot the leftmost pointer
        }
        else{
            curr = nullptr; //Else the tree is empty
        }
           
    }
    

    bool next(T& value, int &priority) {
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
        if(curr == nullptr){ //If list is empty
            return false;
        }

        //Returned values
        value = curr->value;
        priority = curr->priority; 

        if(curr->link != nullptr){
            curr = curr->link;
            return true;
        }

        //Traversing up through the tree to see if there's duplicates
        while(curr->parent != nullptr && curr->priority == curr->parent->priority){
            curr = curr->parent;
        }

        if(curr->right != nullptr){ ////If the curr has a right child 
            curr = curr->right;
            while(curr->left != nullptr){ ////Traversing to the leftmost node in its subtree
                curr = curr->left;
            }
            return true;
        }
        else{ //If there isnt a right child
            while(curr->parent != nullptr && curr->priority > curr->parent->priority){ //Finding a node where the priority is smaller than the curr priority
                curr = curr->parent;
            }

            if(curr->parent != nullptr){ 
                curr = curr->parent;
                return true;
            }

            curr = nullptr;
            return false;
        }
    }

    
    string toString() {
        stringstream ss;
        _recursiveString(root, ss);
        return ss.str();
    }
    

    T peek() {
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
        if(root == nullptr){
            return T();
        }

        NODE* currentNode = root;
        while(currentNode->left != nullptr){
            currentNode = currentNode->left;
        }

        return currentNode->value;
        
    }

    
    bool operator==(const prqueue& other) const {
        return equalsOverLoad(root, other.root);
    }
    

    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
