#include <string>
#include <iostream>
#include "include/Node.h"

Node::Node(std::string value, int n)
{
    Value = value;
    N = n;
    Next = nullptr;
}

Node::Node()
{
    N = -1;
    Value = "";
    Next = nullptr;
}

Node* Node::Get(int index)
{
    Node* current = this;
    if(current->N > index)
    {
        throw std::invalid_argument( "received negative value" );
    }
    while(current->N < index)
    {
        current = current->Next;
    }
    
    return current;
}

std::string Node::MakePhrase(int n)
{
    auto current = this;
    std::string phrase = "";
    while(n > 0)
    {
        if(current == nullptr)
        {
            return "";
        }
        phrase += current->Value + " ";
        current = current->Next;
        n--;
    }
    return phrase;
}
