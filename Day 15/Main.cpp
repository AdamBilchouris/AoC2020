#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <cmath>

typedef std::size_t Index; 


void Part1();
void Part2();

int main()
{
    Part1();
    Part2();
    return 0;
}


void Part1()
{
    std::vector<int> numbers{18, 8, 0, 5, 4, 1, 20};
    Index i = numbers.size();
    while(i < 2020)
    {
        int prevNum = numbers[numbers.size() - 1];
        int newNum = 100;

        auto iter = std::find_if(numbers.rbegin() + 1, numbers.rend(), [prevNum](int j) { return j == prevNum; });
        if(prevNum != *iter)
        {
            newNum = 0;
        }

        else
        {
            int diff = std::distance(iter, numbers.rend());
            diff = -diff + (numbers.size());
            newNum = diff;
        }

        numbers.push_back(newNum);
        i++;
    }

    std::cout << "Part 1 = " << numbers[2019] << std::endl;
}

void Part2()
{
    /*
    //Part 1 Version, very slow, would probably die before it finishes
    std::vector<int> numbers{18, 8, 0, 5, 4, 1, 20};
    Index i = numbers.size();
    while(i < 30000000)
    {
        int prevNum = numbers[numbers.size() - 1];
        int newNum = 0;

        auto iter = std::find_if(numbers.rbegin() + 1, numbers.rend(), [prevNum](int j) { return j == prevNum; });
        if(prevNum != *iter)
        {
            newNum = 0;
        }

        else
        {
            int diff = std::distance(iter, numbers.rend());
            diff = -diff + (numbers.size());
            newNum = diff;
        }

        numbers.push_back(newNum);
        i++;
    }

    std::cout << "Part 2 = " << numbers[29999999] << std::endl;
    */
    
    std::vector<int> numbers{18, 8, 0, 5, 4, 1, 20};
    //Key = Value in the sequence
    //Value = Vector of previous occurences in the vector
    //Basically a lookup table
    std::unordered_map<int, std::vector<int>> sequence;

    for(Index j = 0; j < numbers.size(); ++j)
    {
        sequence[numbers[j]].push_back(j);
    }
    
    int prev = numbers.back();

    for(int i = numbers.size(); i < 30000000; i++)
    {
        //The number does not exist, OR only appears once in the vector of occurences
        if(sequence[prev].size() < 2)
        {
            prev = 0;
        }

        //The number has occured more than once
        else 
        {
            prev = sequence[prev][sequence[prev].size() - 1] - sequence[prev][sequence[prev].size() - 2];
        }

        sequence[prev].push_back(i);
    }

    std::cout << "Part 2 = " << prev << std::endl;
}
