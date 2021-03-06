#include <string>
#include <iostream>
#include "include/LinkedList.h"
#include "include/Node.h"

LinkedList::LinkedList()
{
    Node* firstPtr = new Node();
    First = firstPtr;
    Latest = firstPtr;
}

LinkedList::~LinkedList()
{
    Node* nextToDelete = First->Next;
    delete First;
    while(nextToDelete != nullptr)
    {
        Node* thisOne = nextToDelete;
        nextToDelete = nextToDelete->Next;
        delete thisOne;
    }
}

void LinkedList::Add(std::string value, int n)
{
    Node* tempPtr = new Node(value, n);
    Latest->Next = tempPtr;
    Latest = tempPtr;
}