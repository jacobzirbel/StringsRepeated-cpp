#pragma once
#include "Node.h"
#include <string>

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    Node* First;
    Node* Latest;
    void Add(std::string value, int n);
};
