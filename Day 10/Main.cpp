#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <utility>
#include <set>
#include <tuple>

std::vector<std::pair<std::string, int>> ReadInput();
void Part1();
void Part2();

int main()
{
    Part1();
    Part2();
    return 0;
}

std::vector<std::pair<std::string, int>> ReadInput()
{
    std::ifstream file("data.txt");
    std::string toRead;
    std::vector<std::pair<std::string, int>> values;

    while(std::getline(file, toRead))
    {
        if(toRead.compare("") == 0)
        {
            break;
        }

        else
        {
            std::string instruction = toRead.substr(0, 3);
            std::string valueStr = toRead.substr(4, toRead.length() - 1);
            int value = std::stoi(valueStr);
            values.push_back(std::make_pair(instruction, value));
        }
    }
    return values;
}

void Part1()
{
}


void Part2()
{
}
