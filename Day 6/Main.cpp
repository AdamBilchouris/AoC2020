#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

void Part1();
void Part2();

/*

*/

int main()
{
	Part1();
	Part2();
    return 0;
}


void Part1()
{
	std::ifstream file("data.txt");
	std::string toRead;
	std::vector<std::string> answers;
	std::string toAdd = "";
	
	while(std::getline(file, toRead))
	{
		if(toRead.compare("") == 0)
		{
			answers.push_back(toAdd);
			toAdd = "";
		}
		
		else
		{
			toAdd += toRead;
		}
	}
	
	for(int i = 0; i < answers.size(); i++)
	{
		std::string newString = "";
		
		for(int j = 0; j  < answers[i].size(); j++)
		{
			int k = j + 1;
			while(k < answers[i].size())
			{
				if(answers[i][j] == answers[i][k])
				{
					answers[i].erase(k, 1);
				}
				
				else
				{
					++k;
				}
			}
		}
	}
	
	int total = 0;
	for(int i = 0; i < answers.size(); i++)
	{
		total += answers[i].size();
	}
	
	std::cout << "Part 1: Sum = " << total << std::endl;
}

void Part2()
{
	std::ifstream file("data.txt");
	std::string toRead;
	std::vector<std::string> answers;
	std::vector<int> answersInt;
	std::string toAdd = "";
	int toAddInt = 0;
	
	while(std::getline(file, toRead))
	{
		if(toRead.compare("") == 0)
		{
			answers.push_back(toAdd);
			answersInt.push_back(toAddInt);
			toAdd = "";
			toAddInt = 0;
		}
		
		else
		{
			toAdd += toRead;
			toAddInt += 1;
		}
	}
	
	int total = 0;
	
	//Spaghetti
	for(int i = 0; i < answers.size(); i++)
	{
		std::map<char, int> tempMap;
		
		for(int j = 0; j < answers[i].size(); j++)
		{
			tempMap[answers[i][j]] += 1;
		}
		
		std::map<char, int>::iterator iter = tempMap.begin();
		std::map<char, int>::iterator endIter = tempMap.end();
		
		for(; iter != endIter;)
		{			
			if(iter->second != answersInt[i])
			{
				iter = tempMap.erase(iter);
			}
			
			else
			{
				iter++;
				total += 1;
			}
		}
	}
	
	std::cout << "Part 2: Sum = " << total << std::endl;
}