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
std::tuple<int, int, std::set<int>> FindBadInstruction(const std::vector<std::pair<std::string, int>>& instructions); //returns: <Instruction Index, Accumulator, usedIndices, inputFromFile>
std::vector<std::string> splitString(const std::string& str, char delimiter);
std::string trim(const std::string& str);

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
	std::tuple<int, int, std::set<int>> foundBad = FindBadInstruction(ReadInput());
	int currPos = std::get<0>(foundBad);
	int acc = std::get<1>(foundBad);
	
	std::cout << "Part 1: Accumulator = " << acc << std::endl;
}


void Part2()
{
	std::vector<std::pair<std::string, int>> instructions = ReadInput();
	int currPos = 0;
	int acc = 0;
	
	for(int i = 0; i < instructions.size(); i++)
	{
		if(instructions[i].first.compare("jmp") == 0)
		{
			instructions[i].first = "nop";
		}
		
		else if(instructions[i].first.compare("nop") == 0)
		{
			instructions[i].first = "jmp";
		}
		
		std::tuple<int, int, std::set<int>> foundBad = FindBadInstruction(instructions);
		currPos = std::get<0>(foundBad);
		
		if(currPos == instructions.size())
		{
			acc = std::get<1>(foundBad);
			break;
		}
		
		if(instructions[i].first.compare("jmp") == 0)
		{
			instructions[i].first = "nop";
		}
		
		else if(instructions[i].first.compare("nop") == 0)
		{
			instructions[i].first = "jmp";
		}
	}
	
	std::cout << "Part 2: Accumulator = " << acc << std::endl;
}

//returns: <Instruction Index, Accumulator>
std::tuple<int, int, std::set<int>> FindBadInstruction(const std::vector<std::pair<std::string, int>>& instructions)
{
	int acc = 0;
	int currPos = 0;
	
	std::set<int> usedIndices;
	
	while(1)
	{		
		if(usedIndices.find(currPos) != usedIndices.end())
		{
			break;
		}
		
		usedIndices.insert(currPos);
		
		if(instructions[currPos].first.compare("nop") == 0)
		{
			currPos += 1;
		}
		
		else if(instructions[currPos].first.compare("acc") == 0)
		{
			acc += instructions[currPos].second;
			currPos += 1;
		}
		
		else if(instructions[currPos].first.compare("jmp") == 0)
		{
			currPos += instructions[currPos].second;
		}
	}
	
	return std::make_tuple(currPos, acc, usedIndices);
}