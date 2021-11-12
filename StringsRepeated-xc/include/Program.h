#pragma once
#include <string>
#include "LinkedList.h"
#include "Node.h"

class Program
{
public:
    Program(std::string fileName, std::map<std::string, int> finalData);
    std::map<std::string, int>& FinalData;
    void WriteFile();
    
private:
    std::map<std::string, int> tempData;
    std::string FileName;
    std::string getFile();
    LinkedList* inputList;
    std::vector<int> leads;
    void makeList(const std::string &input);
    void getLeads();
    void byLeads();
    void saveData(std::map<std::string, int> data);
    void write(std::string msg);
};
