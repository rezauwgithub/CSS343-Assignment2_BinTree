/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinTree.cpp
 * Author: rezan
 * 
 * Created on October 10, 2016, 4:57 PM
 */

#include "bintree.h"

#include <algorithm> // Used to implement max


// ------------------------------------ operator << ----------------------------
// Description: operator << overloaded to display the BST in accending order
// Features: Calls inOrderHelper() function passing in the ostream 
//			and reference to the root of the right hand side
// ----------------------------------------------------------------------------
ostream &operator <<(ostream &output, const BinTree &rightObj)
{
    rightObj.inOrderOutputHelper(output, rightObj.root);
    
    output << endl;
    
    return output;
} // End of operator <<


// ------------------------------------ inOrderOutputHelper --------------------
// Description: Private helper function that displays the BST in order
// Precondition: NONE
// Features: Traverses the BST using an in-order traversal algorithm 
// -----------------------------------------------------------------------------
void BinTree::inOrderOutputHelper(ostream& output, Node* currentNode) const
{
    if (currentNode != NULL)
    {
        inOrderOutputHelper(output, currentNode->left);
        output << *currentNode->data << " ";
        inOrderOutputHelper(output, currentNode->right);
    }
} // End of inOrderOutputHelper

// ------------------------------------ copy ----------------------------------
// Description: Private helper function for the operator =
// Precondition: 
// Features: recursively calls the function and 
//			 executes a post-order algorithm 
// ----------------------------------------------------------------------------
void BinTree::copy(Node* currentNode)
{
    if (currentNode != NULL)
    {
        // Creates a new NodeData pointer with source data.
        NodeData* newCopy = new NodeData(*currentNode->data);
        
        // Call insert function with newCopy passed in.
        insert(newCopy);
        
        // Go to left node
        copy(currentNode->left);
        
        // Go to right node
        copy(currentNode->right);
    }
} // End of clone


// -------------------------------- makeEmpty --------------------------------
// Description: Private 
// Precondition:
// Features: 
// ---------------------------------------------------------------------------
void BinTree::makeEmpty(Node* &currentNode)
{
    if (currentNode != NULL)
    {
        // Recursively empty the tree going left
        makeEmpty(currentNode->left);
        
        // Recursively empty the tree going right
        makeEmpty(currentNode->right);
        
        // Delete the NodeData object in the currentNode.
        delete currentNode->data;
        // NULL the pointer that was pointing to the NodeData object.
        currentNode->data = NULL;
        
        // Delete currentNode object
        delete currentNode;
        // NULL the pointer that was pointing to the Node Object.
        currentNode = NULL;
    }
} // End of makeEmpty

// ------------------------------------ isEqual ----------------------------
// Description: Compares two BST and returns a boolean if they are equal or not
// Precondition: NONE
// Features: Recursively traverses both trees comparing data 
// ----------------------------------------------------------------------------
bool BinTree::isEqual(Node* leftObj, Node* rightObj) const
{
    if ((leftObj == NULL) && rightObj == NULL)
    {
        // Two nodes that are NULL are consider equal.
        return true;
    }
    
    
    if ((leftObj != NULL) && (rightObj != NULL))
    {
        return (*leftObj->data == *rightObj->data) &&
                isEqual(leftObj->left, rightObj->left) &&
                isEqual(leftObj->right, rightObj->right);
    }
    
    
    return false;
} // End of isEqual


// ------------------------------------ insert --------------------------------
// Description: Private helper function
// Precondition:
// Features: 
// ----------------------------------------------------------------------------
bool BinTree::insert(Node* &currentNode, NodeData* data) 
{
    if (currentNode == NULL)
    {
        currentNode = new Node;
        currentNode->data = data;
        currentNode->left = NULL;
        currentNode->right = NULL;
        
        return true;
    }
    
    
    if (*data != *currentNode->data)
    {
        if (*data < *currentNode->data)
        {
            // Go to the node on the left.
            return insert(currentNode->left, data);
        }
        
        if (*data > *currentNode->data)
        {
            // Go to the node on the right.
            return insert(currentNode->right, data);
        }
    }
    
    // Returning false. Duplicate node detected.
    return false;

} // End of insert.


// ------------------------------------ retrieve ------------------------------
// Description: Private helper function
// Precondition: NONE
// Features: Recursively goes left and right until found. returns true if
//			 found and false otherwise. 
// ----------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData &data, NodeData* &dataRetrieved, Node* currentNode) const
{
    if (currentNode != NULL)
    {
        // Found the data
        if (data == *currentNode->data)
        {
            NodeData* returnData(currentNode->data);
            dataRetrieved = returnData;     // Node* to Note* &
            
            return true;
        }
        
        // Go to left node if data is smaller than currentNode
        if (data < *currentNode->data)
        {
            return retrieve(data, dataRetrieved, currentNode->left);
        }
        
        // Go to right node if data is larger than currentNode
        if (data > *currentNode->data)
        {
            return retrieve(data, dataRetrieved, currentNode->right);
        }
    }
    
    
    // The node was not found.
    dataRetrieved = NULL;
    return false;
} // End of retrieve


//---------------------------- sideways -------------------------------------
// Helper function for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
// ----------------------------------------------------------------------------
void BinTree::sideways(Node* currentNode, int level) const
{
    if (currentNode != NULL)
    {
        level++;
        sideways(currentNode->right, level);
        
        // Indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--)
        {
            cout << "    ";
        }
        
        cout << *currentNode->data << endl; // Display information of object
        sideways(currentNode->left, level);
    }
    
} // End of sideways


// ------------------------------------ getPtrToNode ----------------------------
// Description: Private helper function that traverses the tree with a given
//				NodeData and returns the Node* pointer associated with it
// Precondition: NONE
// Features: Traverses the tree using an "Dept First Search" approach with a given
//			 NodeData and returns the Node* pointer 
// ----------------------------------------------------------------------------
BinTree::Node* BinTree::getPtrToNode(const NodeData &data, Node* currentNode) const
{
    if (currentNode != NULL)
    {
        // Found
        if (data == *currentNode->data)
        {
            return currentNode;
        }
        
        // Go left
        if (data < *currentNode->data)
        {
            return getPtrToNode(data, currentNode->left);
        }
        
        // Go right
        if (data > *currentNode->data)
        {
            return getPtrToNode(data, currentNode->right);
        }
    }
    
    return NULL;
}


// ------------------------------------ getDepth ----------------------------
// Description: Private helper function
// Precondition:
// Features: 
// ----------------------------------------------------------------------------
int BinTree::getDepth(Node* currentNode) const
{
    // Base case
    if (currentNode == NULL)
    {
        return 0;
    }
    
    int left = 1 + getDepth(currentNode->left);
    int right = 1 + getDepth(currentNode->right);
    
    // Return the max of the two (left and right)
    return max(left, right);
} // End of getDepth


// ------------------------------------ bstreeToArray ------------------------
// Description: Builds a sorted array of NodeData* pointers from a BST 	
// Precondition: NONE
// Features: Traverses the BST tree using an in-order traversal 
//			 adding the NodeData* to each index of the array
// ----------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* array[], Node* currentNode, int &index)
{
    if (currentNode != NULL)
    {
        // Go Left
        bstreeToArray(array, currentNode->left, index);
        
        // Insert
        array[index++] = new NodeData(*currentNode->data);
        
        // Go Right
        bstreeToArray(array, currentNode->right, index);
    }
}


// ------------------------------------ arrayToBSTree ------------------------
// Description: Builds a balanced BST from 
//				a sorted array of NodeData* pointers
// Precondition: arrayToBSTree() helper function
//				 and sizeOf(..) already created
// Features: Refer to the private helper function
// ----------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* array[], int start, int end)
{
    if (start > end)
    {
        return;
    }
    
    
    int mid = start + ((end - start) / 2);
    NodeData* temp = new NodeData(*array[mid]);
    insert(temp);
    delete array[mid];
    
    // Call to private helper function
    arrayToBSTree(array, start, (mid - 1));
    arrayToBSTree(array, (mid + 1), end); 
}

// ------------------------------------ sizeOf ------------------------
// Description: Private function calculates the length of an array
// Precondition: NONE
// Features: loops through the array while not NULL and increments 
// ---------------------------------------------------------------------
int BinTree::sizeOf(NodeData* array[]) const
{
    int size = 0;
    
    // While not NULL, go ahead and proceed
    while (array[size] != NULL)
    {
        // Increment size
        size++;
    }
    
    return size;
}


// ------------------------------------ nodeCount ----------------------------
// Description: Private helper functions that returns
//				the number of nodes in a BST
// Precondition: NONE
// Features: Traverses the BST adding each node 
// ----------------------------------------------------------------------------
int BinTree::nodeCount(Node* currentNode) const
{
    if (currentNode == NULL)
    {
        return 0;
    }
    
    
    return 1 + nodeCount(currentNode->left) + 
               nodeCount(currentNode->right);
} // End of nodeCount


// ------------------------------------BinTree Constructor------------------------
// Description: Create an empty Binary Tree by initializing root to NULL
// ----------------------------------------------------------------------------
BinTree::BinTree() 
{
    // Create an empty Binary Tree
    root = NULL;
}

// ------------------------------------BinTree Copy Constructor------------------------
// Description: Create an empty Binary Tree by initializing root to NULL
//              Then the =operator is used to copy all the data from
//              the source object to the this new object
// Precondition: =operator must be implemented
// ----------------------------------------------------------------------------
BinTree::BinTree(const BinTree &sourceObj) 
{
    // Create an empty Binary Tree
    root = NULL;
    
    // Use the =operator to copy all data from sourceObj to this new object.
    *this = sourceObj;
}

// ------------------------------------~BinTree-----------------------------------
// Description: Destructor destroys the BinTree by using the makeEmpty() function
// Precondition: makeEmpty() function must be implemented
// ----------------------------------------------------------------------------
BinTree::~BinTree() 
{
    makeEmpty();
}

// ------------------------------------makeEmpty-----------------------------------
// Description: Empties the BinTree
// ----------------------------------------------------------------------------
void BinTree::makeEmpty()
{
    makeEmpty(root);
}


// ------------------------------------isEmpty-----------------------------------
// Description: Returns true if the BinTree is empty
// ----------------------------------------------------------------------------
bool BinTree::isEmpty() const
{
    return (root == NULL);
}
\
// ------------------------------------ operator = -----------------------------
// Description: Assigns a Binary Search Tree 
// Precondition: copy(Node* currentNode) and makeEmpty() must exist, 
// with helper functions.
// Features: Empties the tree in the leftObj and copies over node data from rightObj.
// ----------------------------------------------------------------------------
BinTree &BinTree::operator =(const BinTree &rightObj)
{
    if (this != &rightObj)
    {
        makeEmpty();    // Empty this BinTree to prepare for copy
        
        // Copy over BinTree from rightObj
        copy(rightObj.root);
    }
    
    return *this;   // Return a reference to the pointer to support = chaining
}

// ------------------------------------ operator == ----------------------------
// Description: Determines if two Binary Search Trees are equal to each other.
// Precondition: isEqual() helper function must exist
// Features: Compares each node object on both left and right trees to determine 
// if they are equal
// ----------------------------------------------------------------------------
bool BinTree::operator ==(const BinTree &rightObj) const
{
    if (!isEmpty() && !rightObj.isEmpty())
    {
        // Call isEqual helper function
        return isEqual(root, rightObj.root);
    }
    
    
    // If we get here, this means the two BinTree's are not equal.
    // So, false should be returned
    return false;
}


// ------------------------------------ operator != ----------------------------
// Description: Determines if two Binary Search Trees are not equal to each other.
// Precondition: operator == overloaded
// Features: Negates the operator ==.
// ----------------------------------------------------------------------------
bool BinTree::operator !=(const BinTree &rightObj) const
{
    return !
            (*this == rightObj);
}


// ------------------------------------ Insert --------------------------------
// Description: Use private function Transfer the tree and insert the node
// Precondition: private insert function much exist
// Features: 
// ----------------------------------------------------------------------------
bool BinTree::insert(NodeData* data)
{
    return insert(root, data);
}


// ------------------------------------ retrieve ------------------------------
// Description: With a const NodeData&, this function returns a boolean
//				if the data exists and updates the NodeData* & variable
//				with that data that is found.
// Precondition: private retrieve(const NodeData &, NodeData* &, Node*) 
// helper function exists. 
// Features: Calls private retrieve helper function and provides root as 
// an additional parameter.
// ----------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData &data, NodeData* &dataRetrieved) const
{
    return retrieve(data, dataRetrieved, root);
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
// ----------------------------------------------------------------------------
void BinTree::displaySideways() const
{
    sideways(root, 0);
}


// ------------------------------------ getHeight ----------------------------
// Description: 
// Precondition: SPECIAL INSTRUCTION: For this function only, you do not get to 
//				know that the tree is a binary search tree. You must solve the 
//				problem for a general binary tree where data could be stored anywhere.
// Features: 
// ----------------------------------------------------------------------------
int BinTree::getHeight(const NodeData &data) const
{
    Node* ptrToNode = getPtrToNode(data, root);
    if (ptrToNode != NULL)
    {
        return getDepth(ptrToNode);
    }
}


// ------------------------------------ bstreeToArray ------------------------
// Description: Builds a balanced BST from 
//				a sorted array of NodeData* pointers
// Precondition: makeEmpty() , operator = and nodeCount() 
//		         and bstreeToArray() helper function have been created
// Features: Creates a new clone of BST and calls helper function
// ----------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* array[])
{
    // Creates a new copy of the BinTree
    BinTree bstree = *this;
    
    // Deletes the existing one
    makeEmpty();
    
    // Calls nodeCount to get the arraySize will use to allocation our new array
    int arraySize = nodeCount(root);
    array[arraySize];
    int index = 0;
    bstreeToArray(array, bstree.root, index);
       
} // End of bstreeToArray


// ------------------------------------ arrayToBSTree ------------------------
// Description: Builds a balanced BST from 
//				a sorted array of NodeData* pointers
// Precondition: arrayToBSTree() helper function
//				 and sizeOf(..) already created
// Features: Refer to the private helper function
// ----------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* array[])
{
    arrayToBSTree(array, 0, (sizeOf(array) - 1));
    
} // End of arrayToBSTree

