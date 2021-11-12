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
    auto finalData = std::map<string, int>();
    auto program = Program("txts/bible.txt", finalData);
    return 0;
};
