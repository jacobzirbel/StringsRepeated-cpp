#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include "include/LinkedList.h"
#include "include/Node.h"

using namespace std::chrono;

using namespace std;

string getFile()
{
    string str = "";
    fstream newfile;

    // Build string
    newfile.open("txts/bible.txt", ios::in);
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

LinkedList makeList(const string &input)
{
    LinkedList list = LinkedList();
    long size = input.size();
    string str = "";
    int n = 0;
    for (string::size_type i = 0; i < size; i++)
    {
        char c = input[i];
        if (c == ' ')
        {
            list.Add(str, n);
            n++;
            str = "";
        }
        else
        {
            str += c;
        }
    }
    list.Add((string)"", n);
    return list;
}

vector<int> getLeads(LinkedList& inputList, std::map<string, int>& data)
{
    vector<int> leads = vector<int>();
    
    int size = inputList.Latest->N + 1;
    Node* node = inputList.First->Next;
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
    sort(leads.begin(), leads.end());
    return leads;
}

void byLeads(LinkedList& inputList, vector<int>& leads, std::map<string, int>& data)
{
    int n = 1;
    bool again = true;
    while(again)
    {
        n++;
        again = false;
        vector<int> nextLeads = vector<int>();
        auto size = leads.size();
        Node* currentNode = inputList.First;

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
        leads = nextLeads;
        sort(leads.begin(), leads.end());
    }
}

void writeFile(std::map<string, int>& result)
{
    ofstream myfile;
    myfile.open((string)"output" + (string)".txt");
    for ( const auto &keyValue : result ) {
        myfile << keyValue.first;
        myfile << ": ";
        myfile << keyValue.second << endl;
    }
    
    myfile.close();
}

int main()
{
    string str = getFile();
    
    auto start = high_resolution_clock::now();

    std::map<string, int> data = std::map<string, int>();
    std::map<string, int> finalData = std::map<string, int>();
    auto startMake = high_resolution_clock::now();

    LinkedList list = makeList(str);

    auto endMake = high_resolution_clock::now();
    auto durationMake = duration_cast<milliseconds>(endMake - startMake);
    cout << durationMake.count() << endl;
    vector<int> leads = getLeads(list, data);
    byLeads(list, leads, data);
    for ( const auto &keyValue : data ) {
        if(keyValue.second > 1)
        {
            finalData[keyValue.first] = keyValue.second;
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << duration.count() << endl;
    writeFile(finalData);
    return 0;
};
