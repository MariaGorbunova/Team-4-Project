// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Angela Chen

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include "StackADT.h"
#include <cstdlib>


template<class Key, class ItemType>
class BinarySearchTree : public BinaryTree<Key,ItemType>
{
private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<Key,ItemType>* _insert(BinaryNode<Key,ItemType>* nodePtr, BinaryNode<Key,ItemType>* newNode);
    
    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<Key,ItemType>* _remove(BinaryNode<Key,ItemType>* nodePtr,Key target,ItemType & successor, bool & success);
    
    // delete target node from tree, called by internal remove node
    BinaryNode<Key,ItemType>* deleteNode(BinaryNode<Key,ItemType>* targetNodePtr);
    
    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<Key,ItemType>* removeLeftmostNode(BinaryNode<Key,ItemType>* nodePtr, ItemType & successor);
    
    // search for target node
    BinaryNode<Key,ItemType>* findNode(BinaryNode<Key,ItemType>* treePtr, Key target) const;
    BinaryNode<Key,ItemType>* findNode(BinaryNode<Key,ItemType>* treePtr, Key ikey, ItemType target);
    
    
    void _printSameKey(void visit(ItemType &, int level), BinaryNode<Key,ItemType>*nodePtr, Key target);
    
    Stack <ItemType> _findDuplicates(BinaryNode<Key,ItemType> *nodePtr, Key target);
    
    
public:
    // constructors
    BinarySearchTree():BinaryTree<Key,ItemType>(){}
    BinarySearchTree(const BinarySearchTree<Key,ItemType> &obj):BinaryTree<Key,ItemType>(obj){}
    // insert a node at the correct location
    bool insert(Key ikey, const ItemType & newEntry);
    // remove a node if found
    bool remove(Key target,  ItemType & anEntry);
    // find a target node
    bool getEntry( Key ikey,ItemType & returnedItem) const;
    bool deleteEntry(Key ikey, ItemType & returnedItem);
    
    
    void printSameKey(void visit(ItemType &, int), Key target)
    {
        _printSameKey(visit, this->rootPtr, target);
    }
    
    Stack<ItemType> findDuplicates(Key target)
    {
        return _findDuplicates(this->rootPtr,target);
    }
    
    // find minum item content in the tree
    bool  findMin(ItemType & target);
    // find maxmum item content in the tree
    bool  findMax(ItemType & target);
    
};


///////////////////////// public function definitions ///////////////////////////
/****Implementation for insert function--to insert a node to a tree *********/
template<class Key, class ItemType >
bool BinarySearchTree <Key, ItemType >::insert(Key ikey,const ItemType & newEntry)
{
    //   BinaryNode<Key,ItemType>* newNodePtr = new BinaryNode<Key,ItemType>(newEntry,EntryKey);
    BinaryNode< Key,ItemType>* newNodePtr = new BinaryNode<Key,ItemType>(newEntry,ikey);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    this->count++;
    return true;
}
/****Implementation for remove function--to remove node from the ree ********/
template<class Key, class ItemType >
bool BinarySearchTree<Key,ItemType >::remove(Key target,ItemType & returnedItem)
{
    bool isSuccessful = false;
    this->rootPtr = _remove(this->rootPtr, target,returnedItem, isSuccessful);
    return isSuccessful;
}

/****Implementation for getEntry function--to find a node in a tree ********/
template<class Key, class ItemType >
bool BinarySearchTree< Key,ItemType >::getEntry(Key ikey, ItemType & returnedItem) const
{
    BinaryNode<Key,ItemType>* nodePtr;
    nodePtr = findNode(this->rootPtr, ikey);
    if (nodePtr)
    {
        returnedItem=nodePtr->getItem();
        return true;
    }
    else
        return false;
}

template<class Key, class ItemType >
bool BinarySearchTree< Key,ItemType >::deleteEntry(Key ikey, ItemType & returnedItem)
{
    BinaryNode<Key,ItemType>* nodePtr;
    nodePtr = findNode(this->rootPtr, ikey, returnedItem);
    cout << "time to delete this node " << *nodePtr->getItem() << endl;
    nodePtr = deleteNode(nodePtr);
    cout << "did it delete the node?" << *nodePtr->getItem() << endl;
    if (nodePtr)
    {
        returnedItem=nodePtr->getItem();
        return true;
    }
    else
        return false;
}

//////////////////////////// private functions ////////////////////////////////////////////

/****Implementation for insert private function--to insert a node in a tree ********/

template<class Key, class ItemType>
BinaryNode<Key,ItemType>* BinarySearchTree<Key,ItemType>::_insert(BinaryNode<Key,ItemType>* nodePtr, BinaryNode<Key,ItemType>* newNodePtr)
{
    if(nodePtr)
    {
        //std::cout << newNodePtr->getKey() << " " <<  nodePtr->getKey() << std::endl;
        if(nodePtr->getKey().length() > 9 )
        {
            if(newNodePtr->getKey() < nodePtr->getKey())
            {
                newNodePtr->setLevel(newNodePtr->getLevel()+1);
                nodePtr ->setLeftPtr(_insert(nodePtr->getLeftPtr(),newNodePtr));
                //nodePtr ->setRightPtr(_insert(nodePtr->getRightPtr(),newNodePtr));
            }
            else
            {
                newNodePtr->setLevel(newNodePtr->getLevel()+1);
                nodePtr ->setRightPtr(_insert(nodePtr->getRightPtr(),newNodePtr));
                //nodePtr ->setLeftPtr(_insert(nodePtr->getLeftPtr(),newNodePtr));
            }
        }
        else
        {
            if(atoi(newNodePtr->getKey().c_str()) < atoi(nodePtr->getKey().c_str()))
            {
                newNodePtr->setLevel(newNodePtr->getLevel()+1);
                nodePtr ->setLeftPtr(_insert(nodePtr->getLeftPtr(),newNodePtr));
                //nodePtr ->setRightPtr(_insert(nodePtr->getRightPtr(),newNodePtr));
            }
            else
            {
                newNodePtr->setLevel(newNodePtr->getLevel()+1);
                nodePtr ->setRightPtr(_insert(nodePtr->getRightPtr(),newNodePtr));
                //nodePtr ->setLeftPtr(_insert(nodePtr->getLeftPtr(),newNodePtr));
            }
        }
        return nodePtr;
    }
    return newNodePtr;
}
/****Implementation for remove private function--to remove a target node in a tree ********/
/*template<class Key, class ItemType >
 BinaryNode<Key,ItemType>* BinarySearchTree<Key,ItemType>::_remove(BinaryNode<Key,ItemType>* nodePtr,Key target ,ItemType & returnedItem,bool & success)
 {
 //cout << returnedItem << " == " << nodePtr->getItem() << endl;
	if (!nodePtr )
	{
 success = false;
 return 0;
	}
 if (nodePtr->getKey() > target)
 nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(),target, returnedItem, success));
	else if (nodePtr->getKey() < target)
 nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(),target,returnedItem, success));
 else
 {
 nodePtr = deleteNode(nodePtr);
 this->count--;
 success = true;
 }
 
 
 
	return nodePtr;
 }*/

template<class Key, class ItemType >
BinaryNode<Key,ItemType>* BinarySearchTree<Key,ItemType>::_remove(BinaryNode<Key,ItemType>* nodePtr,Key target ,ItemType & returnedItem,bool & success)
{
    //cout << returnedItem << " == " << nodePtr->getItem() << endl;
    if (!nodePtr )
    {
        success = false;
        return NULL;
    }
    if (returnedItem == nodePtr->getItem())
    {
        nodePtr = deleteNode(nodePtr);
        this->count--;
        success = true;
    }
    else if (nodePtr->getKey() > target)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(),target, returnedItem, success));
    else if (nodePtr->getKey() <= target)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(),target,returnedItem, success));
    
    return nodePtr;
}


/****Implementation for delete private function--to delete a leaf node in a
 tree( three cases) ********/

template<class Key, class ItemType >
BinaryNode<Key,ItemType>* BinarySearchTree<Key,ItemType>::deleteNode(BinaryNode<Key,ItemType>* nodePtr)
{
    if (nodePtr->isALeaf())
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode<Key,ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode<Key,ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        ItemType newNodeValue;
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}
/****Implementation for removeLeftmostNode private function--to remove the  removeLeftmostNode in a
 tree( three cases) ********/

template<class Key, class ItemType >
BinaryNode<Key,ItemType>* BinarySearchTree<Key,ItemType>::removeLeftmostNode(BinaryNode<Key,ItemType>* nodePtr,ItemType & successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor = nodePtr->getItem();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }
}
/****Implementation for findNode private function--find a node in a
 tree( three cases) ********/

template<class Key, class ItemType >
BinaryNode<Key,ItemType>* BinarySearchTree<Key,ItemType>::findNode(BinaryNode<Key,ItemType>* nodePtr,Key target) const
{
    
    // Uses a binary search
    if (nodePtr == nullptr)
        return nodePtr;                        // Not found
    else if (nodePtr->getKey() == target)
    {
        //cout << nodePtr->getKey() << " == " << target << "?" << endl;
        return nodePtr;                     // Found
    }
    else if (nodePtr->getKey() > target)
        
    {    // Search left subtree
        // cout << nodePtr->getKey() << endl;
        //cout << nodePtr->getKey() << " > " << target << "?" << endl;
        return findNode(nodePtr->getLeftPtr(), target);
    }
    else
        // Search right subtree
        return findNode(nodePtr->getRightPtr(), target);
}

template<class Key, class ItemType >
BinaryNode<Key,ItemType>* BinarySearchTree<Key,ItemType>::findNode(BinaryNode<Key,ItemType>* nodePtr, Key ikey, ItemType target)
{
    //cout << "in findNode(ItemType target)" << endl;
    // Uses a binary search
    if (nodePtr == nullptr)
        return nodePtr;                        // Not found
    else if (nodePtr->getItem() == target)
    {
        //cout << nodePtr->getItem() << " == " << target << "?" << endl;
        return nodePtr;                     // Found
    }
    else if (nodePtr->getKey() > ikey)
        
    {    // Search left subtree
        // cout << nodePtr->getKey() << endl;
        //cout << nodePtr->getItem() << " > " << target << "?" << endl;
        return findNode(nodePtr->getLeftPtr(), ikey, target);
    }
    else
        // Search right subtree
        return findNode(nodePtr->getRightPtr(), ikey, target);
}


// find minum item content in the tree
template<class Key, class ItemType >
bool BinarySearchTree<Key,ItemType>::findMin(ItemType & target)
{
    if( this->rootPtr)
    {
        //target= this->findLeftmost(this->getLeftPtr() )-> getItem();
        target= this->findLeftmost();
        return true;
    }
    return false;
}
// find maxmum item content in the tree
template<class Key, class ItemType >
bool BinarySearchTree<Key,ItemType>::findMax(ItemType & target)
{
    if( this->rootPtr)
    {
        // target= this->findRightmost(this->getRightPtr() )->getItem();
        target= this->findRightmost();
        return true;
    }
    return false;
}

template<class Key, class ItemType >
void BinarySearchTree<Key,ItemType>::_printSameKey(void visit(ItemType &, int level), BinaryNode<Key,ItemType>*nodePtr, Key target)
{
    
    BinaryNode<Key,ItemType>* found = findNode(nodePtr, target);
    //cout << found->getKey() << endl;
    while(found)
    {
        ItemType item = found->getItem();
        visit(item, found->getLevel());
        //cout << "found->getRightPtr() is " << found->getRightPtr() << endl;
        found = findNode(found->getRightPtr(), target);
    }
    
}

template<class Key, class ItemType >
Stack <ItemType> BinarySearchTree<Key,ItemType>::_findDuplicates(BinaryNode<Key,ItemType>*nodePtr, Key target)
{
    Stack <ItemType> s;
    BinaryNode<Key,ItemType>* found = findNode(nodePtr, target);
    
    while(found)
    {
        ItemType item = found->getItem();
        s.push(item);
        found = findNode(found->getRightPtr(), target);
    }
    
    return s;
}

#endif
