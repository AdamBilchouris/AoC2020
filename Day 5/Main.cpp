#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

void Part1();
void Part2();
int GetId(std::string str);

/*
First 7 characters will either be F or B;
	F is front (lower half)
	B is back (upper half)
Last 3 characters will either be L or R;
	L is left (lower half)
	R is right (upper half)

First 7 give the row, last 3 give the column

ID = (ROW * 8) + column
*/

int main()
{
	Part1();
	Part2();
    return 0;
}

//Highest ID on a boarding pass
void Part1()
{
	std::ifstream file("data.txt");
    std::string toRead;
	std::vector<std::string> passes;
	std::vector<int> ids;
	
	 while(std::getline(file, toRead))
	 {
		 if(toRead.compare("") == 0 || toRead.compare("\n") == 0)
		 {
			 //nothing
			 break;
		 }
		 
		 passes.push_back(toRead);
	 }
	 
	 for(int i = 0; i < passes.size(); i++)
	 {
		 ids.push_back(GetId(passes[i]));
	 }
	 
	 std::sort(ids.begin(), ids.end());
	 
	 std::cout << "Highest ID = " << ids[ids.size() - 1] << std::endl;
	 
	 /*
	 std::vector<std::string> tests = {"FBFBBFFRLR", "BFFFBBFRRR", "FFFBBBFRRR", "BBFFBBFRLL"};
	 std::vector<int> testResults;
	 
	 for(int i = 0; i < tests.size(); i++)
	 {
		 testResults.push_back(GetId(tests[i]));
	 }
	
	for(int i = 0; i < testResults.size(); i++)
	{
		std::cout << testResults[i] << std::endl;
	}*/
}

void Part2()
{
	std::ifstream file("data.txt");
    std::string toRead;
	std::vector<std::string> passes;
	std::vector<int> ids;
	
	 while(std::getline(file, toRead))
	 {
		 if(toRead.compare("") == 0 || toRead.compare("\n") == 0)
		 {
			 //nothing
			 break;
		 }
		 
		 passes.push_back(toRead);
	 }
	 
	 for(int i = 0; i < passes.size(); i++)
	 {
		 ids.push_back(GetId(passes[i]));
	 }
	 
	 std::sort(ids.begin(), ids.end());

	 //Binary search
	 int low = 0;
	 int high = ids.size() - 1;
	 int middle;
	 
	 while((high - low) > 1)
	 {
		 middle = (low + high) / 2;
		 
		 if((ids[low] - low) != (ids[middle] - middle))
		 {
			 high = middle;
		 }
		 
		 else if((ids[high] - high) != (ids[middle] - middle))
		 {
			 low = middle;
		}
	 }
	 std::cout << "Missing ID = " << ids[middle] + 1 << std::endl;
}

int GetId(std::string str)
{
	//Convert to binary instead, literally says its binary in the problem...
	std::replace(str.begin(), str.end(), 'F', '0');
	std::replace(str.begin(), str.end(), 'B', '1');
	std::replace(str.begin(), str.end(), 'L', '0');
	std::replace(str.begin(), str.end(), 'R', '1');
	
	int row = std::stoi(str.substr(0, 7), nullptr, 2);
	int col = std::stoi(str.substr(7, 10), nullptr, 2);
	
	return ((8 * row) + col);
	
	/*
	//old way, still works
	int lowR = 0;
	int highR = 128;
	
	int lowC = 0;
	int highC = 8;
	
	for(int i = 0; i < 7; i++)
	{
		switch(str[i])
		{
			case 'F':
			{
				highR = (lowR / 2) + (highR / 2);
				break;
			}
			
			case 'B':
			{
				lowR = (lowR / 2) + (highR / 2);
				break;
			}
		}
	}
	
	for(int i = 7; i < 10; i++)
	{
		switch(str[i])
		{
			case 'L':
			{
				highC = (lowC / 2) + (highC / 2);
				break;
			}
			
			case 'R':
			{
				lowC = (lowC / 2) + (highC / 2);
				break;
			}
		}
	}*/
	//return ((lowR * 8) + lowC);
}
