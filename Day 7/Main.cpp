#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <utility>
#include <set>

class Bag
{
	public:
		std::string colour;
		std::vector<std::pair<std::string, int>> bags;
};

std::pair<std::vector<Bag>, std::set<std::string>> ReadInput();
void Part1();
void Part2();
int Part2Helper(int index, const std::vector<Bag>& bags);
std::vector<std::string> splitString(const std::string& str, char delimiter);
std::string trim(const std::string& str);

int main()
{
    Part1();
    Part2();
    return 0;
}

std::pair<std::vector<Bag>, std::set<std::string>> ReadInput()
{
	std::ifstream file("data.txt");
    std::string toRead;
	
	std::set<std::string> canHoldGold;
	std::vector<Bag> bags;
	
	std::string regexString = "([a-z]+ [a-z]+) bags contain (.*).";
	std::string regexStringNumber = "([0-9]+) ([a-z]+ [a-z]+)";
	std::regex reg(regexString);
	std::regex regNo(regexStringNumber);
	
	std::smatch sm;
	
    while(std::getline(file, toRead))
    {
        if(toRead.compare("") == 0)
        {
			break;
        }

        else
        {
			if(toRead.find("shiny gold") != std::string::npos)
			{
				std::vector<std::string> tempVector = splitString(toRead, ' ');
				
				if((tempVector[0] + " " + tempVector[1]).compare("shiny gold") != 0)
				{
					canHoldGold.insert(tempVector[0] + " " + tempVector[1]);
				}
			}
			
			std::regex_match (toRead, sm, reg);
			std::vector<std::string> tempVec;
			tempVec.push_back(sm[1]);
			std::vector<std::string> returnVec = splitString(sm[2], ',');
			tempVec.insert(tempVec.end(), returnVec.begin(), returnVec.end());
			
			for(int i = 0; i < tempVec.size(); i++)
			{
				tempVec[i] = trim(tempVec[i]);
			}
			
			Bag b;
			b.colour = sm[1];
			
			for(int i = 0; i < tempVec.size(); i++)
			{
				std::regex_search (tempVec[i], sm, regNo);
				if(sm.size() != 0)
				{
					int count = std::stoi(sm[1]);
					b.bags.push_back(std::make_pair (sm[2], count));
				}
			}
			
			bags.push_back(b);
        }
    }
	
	return std::make_pair(bags, canHoldGold);
}

void Part1()
{
    std::pair<std::vector<Bag>, std::set<std::string>> returnPair = ReadInput();
	std::vector<Bag> bags = returnPair.first;
	std::set<std::string> canHoldGold = returnPair.second;
	
	int prevIter = canHoldGold.size();
	int currIter = 0;
	
	while(prevIter != currIter)
	{
		prevIter = canHoldGold.size();
		for(int i = 0; i < bags.size(); i++)
		{
			for(int j = 0; j < bags[i].bags.size(); j++)
			{
				if(canHoldGold.find(bags[i].bags[j].first) != canHoldGold.end())
				{
					canHoldGold.insert(bags[i].colour);
					currIter = canHoldGold.size();
				}
			}
		}
	}
	std::cout << "Part 1 = " << canHoldGold.size() << std::endl;
}

void Part2()
{
	std::vector<Bag> bags = ReadInput().first;
	
	int indexOfGold = 0;
	for(int i  = 0; i < bags.size(); i++)
	{
		if(bags[i].colour.compare("shiny gold") == 0)
		{
			indexOfGold = i;
			break;
		}
	}
	
	int sum = Part2Helper(indexOfGold, bags) - 1;
	
	std::cout << "Part 2: Sum = " << sum << std::endl;
}

int Part2Helper(int index, const std::vector<Bag>& bags)
{
	int counter = 1;
	for(int i = 0; i < bags[index].bags.size(); i++)
	{
		int recIndex = -1;

		for(int j = 0; j < bags.size(); j++)
		{
			if(bags[j].colour.compare(bags[index].bags[i].first) == 0)
			{
				recIndex = j;
				break;
			}
		}
		
		counter = counter + bags[index].bags[i].second * Part2Helper(recIndex, bags);
	}
	
	return counter;
}


std::vector<std::string> splitString(const std::string& str, char delimiter)
{
	std::vector<std::string> vec;
    std::stringstream iss(str);
    std::string tempString;
	
	while(getline(iss, tempString, delimiter))
	{
		vec.push_back(tempString);
	}
	
	return vec;
}

std::string trim(const std::string& str)
{
    std::size_t first = str.find_first_not_of(' ');
	
    if (first == std::string::npos)
    {
        return str;
    }
	
    std::size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}