/**~*~*
   Stack template
*~**/
#ifndef STACK_ADT_H
#define STACK_ADT_H
#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
   // Structure for the stach nodes
   struct StackNode
   {
      T value;          // Value in the node
      StackNode *next;  // Pointer to next node
   };

   StackNode *top;     // Pointer to the stack top
   int count;

public:
   //Constructor
   Stack(){top = NULL; count = 0;}

   // Destructor
   ~Stack();

   // Stack operations
   bool push(T);// add nodes to the stack list
   bool pop(T &);//pop value out of stack
   bool isEmpty();//check whether the stack is empty
   int getCount();// get count of the arguemnt in stack
   T getTop( T &item);// get top of the stack, since top keeps changing, need
    // reference parameters
   void reverseStack();// reverse the argument order in the stack
};
/******************************************************************************
******************************************************************************/

/**~*~*
 Member function get count of arguments in the stack.
 *~**/
template <class T>
int Stack<T>::getCount()
{
    return count;
}

/**~*~*
 Member function get top of argument in the stack.
 Feedback:define getTop in a similar way with pop, change to bool
 *~**/
template <class T>
T Stack<T>::getTop(T &item)
{
    //check if stack is empty then CAN we get top.
    //If stack is empty, top will be NULL, PROBLEMS will occure.
    if(!isEmpty())
    {
    item=top->value;
    }
      return  item;
}


/**~*~*
  Member function push pushes the argument onto
  the stack. 
*~**/
template <class T>
bool Stack<T>::push(T item)
{
   StackNode *newNode; // Pointer to a new node

   // Allocate a new node. If memory full and allocate fail, return.
   newNode = new StackNode;
   if (!newNode)
       return false;
 // else, it means newNode got the memory, then we put value in it
   newNode->value = item;

   // Update links and counter
   newNode->next = top;
   top = newNode;
   count++;

   return true;
}

/**~*~*
  Member function pop pops the value at the top
  of the stack off, and copies it into the variable
  passed as an argument.
*~**/
template <class T>
bool Stack<T>::pop(T &item)
{
   StackNode *temp; // Temporary pointer

   // empty stack
   if (count == 0)
       return false;

   // pop value off top of stack
   item = top->value;
   temp = top->next;// use temp to update links
   delete top;// delete top node after value is popped out
   top = temp;//update top pointer to temp so that it still points to the first node
   count--;

   return true;
}

/**~*~*
 Member function reverseStack reverse the order of argument in stack
 *~**/
template <class T>
void Stack<T>::reverseStack()
{
    // Use there pointers to reverse Stack
    StackNode *preNode=nullptr, *currNode, *nextNode;
    currNode = top;
    
    while( currNode)
    {
        nextNode =currNode->next;
        currNode->next=preNode;
        preNode=currNode;
        currNode=nextNode;
    }
    top= preNode;
    
}

/**~*~*
  Member function isEmpty returns true if the stack
  is empty, or false otherwise.
*~**/
template <class T>
bool Stack<T>::isEmpty()
{
    // If count is 0, then the stack is empty
   return count == 0;
}

/**~*~*
 Destructor
 *~**/
template <class T>
Stack<T>::~Stack()
{
    // use two pointers, curr and next to destroy the list
    StackNode *currNode, *nextNode;
    
    // Position nodePtr at the top of the stack.
    currNode = top;
    
    // Traverse the list deleting each node.
    while (currNode) //while (currNode != NULL)
    {
        // initialize nextNode
        nextNode = currNode->next;
        // delete the node curr is currently poiting(if top, then delete the first node)
        delete currNode;
        // as long as curr!=NULL, keep updating curr ( use next)
        currNode = nextNode;
    }
}

#endif
