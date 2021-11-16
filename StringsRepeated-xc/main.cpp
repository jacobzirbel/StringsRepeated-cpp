#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include "include/Program.h"

using namespace std::chrono;

using namespace std;

int main()
{
    // g++ -sdt=c++20 *.cpp -o output && ./output
    std::map<string,int> finalData = std::map<string, int>();
    Program program = Program("txts/bible.txt", finalData);
    return 0;
};
