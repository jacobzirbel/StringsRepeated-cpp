#pragma once
#include <string>

class Node
{
public:
    Node(std::string value, int n);
    Node();
    int N;
    std::string Value;
    Node* Next;
    std::string MakePhrase(int n);
    Node* Get(int index);
};
