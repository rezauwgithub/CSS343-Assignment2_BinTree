// ---------------------- BinTree.h ------------------------- 
// 
// Programmer's Name: Reza Naeemi  
// Course Section Number: CSS 343 B 
// Creation Date: 10/10/2016 
// Date of Last Modification: 10/10/2016 
// -------------------------------------------------------------------------- 
// Purpose - Create an Abstract Data Type (ADT) of a Binary Search Tree
// ---------------------------------------------------------------- 
// Featured functions:
//		insert(), retrieve(), displaySideways(), getHeight, 
//		bstreeToArray(), and arrayToBSTree().
//
// 
// Note: This program has been tested on Linux with Valgrind. 
//		No memory leaks were found by me.
// ----------------------------------------------------------------------------


// Columns should be less than 80 characters
// ----------------------------------------------------------------------------|

#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <string>

#include "nodedata.h"

class BinTree {
    
    friend ostream &operator << (ostream &output, const BinTree &rightObj);
   
    
    private:
        struct Node
        {
            NodeData* data;         // Pointer to data object
            Node* left;             // Pointer to left subtree
            Node* right;            // Pointer to right subtree
        };
        
        Node* root;                 // Pointer to root of the tree
        
        
     /////////////////////private helper functions/////////////////////////
        
        // Helper for <<operator
        void inOrderOutputHelper(ostream &output, Node* currentNode) const;
        
        // Helper copy function for the =operator
        void copy(Node* currentNode);
        
        // Helper function for the makeEmpty() public function
        void makeEmpty(Node* &currentNode);
        
        // Helper function for the ==operator(...) to determine if both sides are equal
        bool isEqual(Node* leftObj, Node* rightObj) const;
        
        // Helper function for the insert(NodeData* data) public function
        bool insert(Node* &currentNode, NodeData* data);
        
        // Helper function for the retrieve(const NodeData &data, NodeData* &dataRetreived) const public function
        bool retrieve(const NodeData& data, NodeData* &dataRetrieved, Node* currentNode) const;
        
        // Helper function for the public displaySideways() function
        void sideways(Node* currentNode, int level) const;
        
        // Helper functions for the getHeight() public function
        // (Both helper functions are used to support this one public function.)
        Node* getPtrToNode(const NodeData &data, Node* currentNode) const;
        int getDepth(Node* currentNode) const;
        
        // Helper function for the bstreeToArray() public function
        void bstreeToArray(NodeData* array[], Node* currentNode, int &index);
        
        // Helper functions for the arrayToBSTree() public function
        // (Both helper functions are used to support this one public function.)
        void arrayToBSTree(NodeData* array[], int start, int end);
        int sizeOf(NodeData* array[]) const;
        
        // Helper function for the bstreeToArray() public function
        int nodeCount(Node* currentNode) const;
    
    public:
        // Constructor
        BinTree();
        // Copy Constructor
        BinTree(const BinTree &sourceObj);
        // Destructor (Uses the makeEmpty() function)
        virtual ~BinTree();
        // Make the tree empty
        void makeEmpty();
        bool isEmpty() const;
        BinTree &operator =(const BinTree &rightObj);
        bool operator ==(const BinTree &rightObj) const;
        bool operator !=(const BinTree &rightObj) const;
        bool insert(NodeData* data);
        bool retrieve(const NodeData &data, NodeData* &dataRetrieved) const;
        // Display the tree sideways
        void displaySideways() const;
        
        // Gets the height of the tree
        int getHeight(const NodeData &data) const;
        // Converts the tree to an array
        void bstreeToArray(NodeData* array[]);
        // Converts the array to a tree
        void arrayToBSTree(NodeData* array[]);

};

#endif /* BINTREE_H */

