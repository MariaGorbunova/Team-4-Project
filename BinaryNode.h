/// BinaryNode class
/// Dat Nguyen, modifyed my Angela Chen

#ifndef BINARY_NODE_H
#define BINARY_NODE_H

template<class Key, class ItemType >
class BinaryNode
{
private:
    ItemType item;
    int      level;
    Key     key;
    BinaryNode<Key,ItemType>* leftPtr;	  /// Pointer to left
    BinaryNode<Key,ItemType>* rightPtr;	 /// Pointer to right

public:
    
    // constructors
    BinaryNode(const ItemType & anItem, Key ikey )	{item = anItem; key = ikey; leftPtr = 0; rightPtr = 0; level = 1;}
    BinaryNode(const ItemType & anItem, Key ikey, BinaryNode<Key,ItemType>* left, BinaryNode<Key,ItemType>* right) {item = anItem; key = ikey;leftPtr = left; rightPtr = right;}
    // accessors
    void setItem(const ItemType & anItem) {item = anItem;}
    void setLeftPtr(BinaryNode<Key,ItemType>* left) {leftPtr = left;}
    void setRightPtr(BinaryNode<Key,ItemType>* right) {rightPtr = right;}
    void setLevel(int depth) { level = depth;} /// Vera added
    void setKey(Key ikey ){ key = ikey;}
    // mutators
    ItemType getItem()const{return item;}
    int getLevel() { return level;}
    Key getKey()const{return key;}
    BinaryNode<Key,ItemType>* getLeftPtr() const {return leftPtr;}
    BinaryNode<Key,ItemType>* getRightPtr() const {return rightPtr;}
    
    bool isALeaf() const {return (leftPtr == 0 && rightPtr == 0);}
  
};

#endif
