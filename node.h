/// Dat Nguyen
#ifndef NODE_H
#define NODE_H
#include "iPhone.h"

class Node
{
    iPhone*	data;
    Node*	next;
public:
    /// constructor
    Node(iPhone* ptrIn)
    {
        data = ptrIn;
        next = nullptr;
    }
    /// getters
    iPhone* getData() const
    {
        return data;
    }

    Node* getNext() const
    {
        return next;
    }

    /// setters
    void setData(iPhone* ptr)
    {
        data = ptr;
    }

    void setNext(Node* ptr)
    {
        next = ptr;
    }
};

#endif
