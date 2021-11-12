#include <string>
#include <iostream>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

#include "include/Program.h"
#include "include/LinkedList.h"
#include "include/Node.h"
using namespace std::chrono;

using namespace std;

Program::Program(string fileName, std::map<string, int> finalData) : FileName(fileName), FinalData(finalData)
{

    auto file = getFile();
    makeList(file);
    getLeads();
    byLeads();
    WriteFile();
}

void Program::WriteFile()
{
    ofstream myfile;
    myfile.open((string)"output-new" + (string)".txt");
    for ( const auto &keyValue : FinalData ) {
        myfile << keyValue.first;
        myfile << ": ";
        myfile << keyValue.second << endl;
    }
    
    myfile.close();
}

void Program::byLeads()
{
    int n = 1;
    bool again = true;
    while(again)
    {
        n++;
        again = false;
        vector<int> nextLeads = vector<int>();
        auto size = leads.size();
        Node* currentNode = inputList->First;
        auto data = std::map<string, int>();
        for(int index = 0; index < size; index++)
        {
            int i = leads[index];
            currentNode = currentNode->Get(i);
            string str = currentNode->MakePhrase(n);
            if(str != "")
            {
                if(data.count(str) == 0)
                {
                    data[str] = (i + 1) * -1;
                }
                else
                {
                    auto s = data[str];
                    if(s < 0)
                    {
                        nextLeads.push_back(s * -1 - 1);
                        nextLeads.push_back(i);
                        data[str] = 2;
                        again = true;
                    }
                    else
                    {
                        nextLeads.push_back(i);
                        data[str]++;
                    }
                }
            }
        };
        
        auto startGet = high_resolution_clock::now();
        for ( const auto &keyValue : data ) {
            if(keyValue.second > 1)
            {
                FinalData[keyValue.first] = keyValue.second;
            }
        }
        auto endGet = high_resolution_clock::now();
        auto durationGet = duration_cast<milliseconds>(endGet - startGet);
        cout << durationGet.count() << endl;

        leads = nextLeads;
        sort(leads.begin(), leads.end());
    }
}

void Program::getLeads()
{
    leads = vector<int>();
    auto data = std::map<string, int>();
    int size = inputList->Latest->N + 1;
    Node* node = inputList->First->Next;
    for(int i = 0; i < size; i++)
    {
        string val = node->Value;
        node = node->Next;
        string str = val + " ";
        if(data.count(str) == 0)
        {
            (data)[str] = -1 * (i + 1);
        }
        else
        {
            if((data)[str] < 0)
            {
                leads.push_back(data[str] * -1 - 1);
                leads.push_back(i);
                (data)[str] = 2;
            }
            else
            {
                leads.push_back(i);
                (data)[str]++;
            }
        };
    };
    for ( const auto &keyValue : data ) {
        if(keyValue.second > 1)
        {
            FinalData[keyValue.first] = keyValue.second;
        }
    }
    sort(leads.begin(), leads.end());
}

string Program::getFile()
{
    string str = "";
    fstream newfile;

    // Build string
    newfile.open(FileName, ios::in);
    if (newfile.is_open())
    {
        string tp;
        while (getline(newfile, tp))
        {
            str += " ";
            str += tp;
        }
        newfile.close();
    }
    // Uppercase
    for (auto &str : str)
        str = toupper(str);

    // Cleanup
    // Special Characters
    regex a("[.,\\/#!$%\\^&\\*;:{}=\\-_`~()\"\\[\\]]");
    // lines
    regex b("[\n]");
    regex c("\\d");
    regex d("\\s{1,}");
    regex e("^\\s");
    regex f("\\s$");
    // 
    str = regex_replace(str, a, "");
    str = regex_replace(str, b, " ");
    str = regex_replace(str, c, "");

    str = regex_replace(str, d, " ");
    str = regex_replace(str, e, "");
    str = regex_replace(str, f, "");
    return str + " ";
}

void Program::makeList(const string &input)
{
    inputList = new LinkedList();
    long size = input.size();
    string str = "";
    int n = 0;
    for (string::size_type i = 0; i < size; i++)
    {
        char c = input[i];
        if (c == ' ')
        {
            inputList->Add(str, n);
            n++;
            str = "";
        }
        else
        {
            str += c;
        }
    }
    inputList->Add((string)"", n);

}
