#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <numeric>
#include <algorithm>

std::vector<long> ReadInput();
void Part1();
void Part2();
long FindTroubledNumber(const std::vector<long> &vec, int offset);
long FindMin(const std::vector<long> &vec, int low, int high);
long FindMax(const std::vector<long> &vec, int low, int high);

int main()
{
    Part1();
    Part2();
    return 0;
}

std::vector<long> ReadInput()
{
    std::ifstream file("data.txt");
    std::string toRead;
    std::vector<long> ret;

    while(std::getline(file, toRead))
    {
        if(toRead.compare("") == 0)
        {
            break;
        }

        else
        {
            long val = std::stol(toRead);
            ret.push_back(val);
        }
    }
    return ret;
}

void Part1()
{
    long ret = FindTroubledNumber(ReadInput(), 25);
    std::cout << "Part 1 = " << ret << std::endl;
}


void Part2()
{
    long ret = FindTroubledNumber(ReadInput(), 25);
    std::vector<long> initial = ReadInput();

    long answer = -1;
    long sum = 0;
    int i, j = 0;
    bool quit = false;

    for(i = 0; i < initial.size() && !quit; i++)
    {
        j = i;
        sum = 0;

        while(sum < ret && !quit)
        {
            sum += initial[j];
            
            if((sum == ret) && ((j - i) > 1))
            {
                quit = true;
            }

            j++;
        }
    }

    long min = FindMin(ReadInput(), i, j);
    long max = FindMax(ReadInput(), i, j);

    answer = min + max;
    std::cout << "Part 2 = " << answer << std::endl;
}

long FindTroubledNumber(const std::vector<long> &vec, int offset)
{
    int startIndex = offset;
    std::vector<long> initial = ReadInput();
    long val = 0;
    bool found = false;
    std::vector<long> foundVals;

    for(int i = startIndex; i < initial.size(); i++)
    {
        val = initial[i];
        found = false;
        for(int j = i - 1; j >= i - startIndex; j--)
        {
            for(int k = i - 2; k >= i - startIndex - 1; k--)
            {
                if(found)
                {
                    break;
                }

                if(initial[j] + initial[k] == val)
                {
                    foundVals.push_back(val);
                    found = true;
                    break;
                }
            }
        }
    }

    long problemValue = -1;
    for(int i = 0; i < foundVals.size(); i++)
    {
        if(initial[i + startIndex] != foundVals[i])
        {
            problemValue = initial[i + startIndex];
            break;
        }
    }

    return problemValue;
}


long FindMin(const std::vector<long> &vec, int low, int high)
{
    long min = vec[low];
    for(int k = low; k <= high; k++)
    {
        if(min > vec[k])
        {
            min = vec[k];
        }
    }

    return min;
}

long FindMax(const std::vector<long> &vec, int low, int high)
{
    long max = 0;
    for(int k = low; k <= high; k++)
    {
        if(max < vec[k])
        {
            max = vec[k];
        }
    }

    return max;
}
