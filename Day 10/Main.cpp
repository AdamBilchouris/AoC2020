#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

typedef std::size_t Index; 

std::vector<int> ReadInput();
void Part1();
void Part2();

int main()
{
    Part1();
    Part2();
    return 0;
}

std::vector<int> ReadInput()
{
    std::ifstream file("data.txt");
    int toRead;
    std::vector<int> values;

    while(file >> toRead)
    {
        values.push_back(toRead);
    }
    return values;
}

void Part1()
{
    std::vector<int> values;
    values.push_back(0);
    std::vector<int> tempValues = ReadInput();
    values.insert(values.end(), tempValues.begin(), tempValues.end());
    std::sort(values.begin(), values.end());
    values.push_back(values[values.size() - 1] + 3);

    std::vector<int> difference;
    int oneDiff = 0;
    int threeDiff = 0;

    for(Index i = 0; i < values.size() - 1; i++)
    {
        difference.push_back(values[i + 1] - values[i]); 
    }

    oneDiff = std::count(difference.begin(), difference.end(), 1);
    threeDiff = std::count(difference.begin(), difference.end(), 3);

    std::cout << "Part 1: Product = " << oneDiff * threeDiff << std::endl;
}

void Part2()
{
    std::vector<int> values;
    values.push_back(0);
    std::vector<int> tempValues = ReadInput();
    values.insert(values.end(), tempValues.begin(), tempValues.end());
    std::sort(values.begin(), values.end());
    values.push_back(values[values.size() - 1] + 3);

    std::vector<long> combinations (values.size());
    //Ways to get to 0 is 1.
    combinations[0] = 1;

    for(Index i = 0; i < values.size() - 1; i++)
    {
        //Check for out of range and if it is <= 3 jolts away from the current one
        //If both are true, then make the total number of ways to get to here
        //number of ways beforehand and any current value (which will just be the current value).
        //(0), 1, 4, 7, 10, 12, 15, 16, 19, (22) 
        //(0), 1, 4, 7, 10, 11, 12, 15, 16, 19, (22)
        //If we are at 10, we can go to 11 OR 12, OR both.
        //This means that both are valid paths, so we give both the number of combinations currently.
        //(i + 1) and (i + 2)
        //======================================================================
        //Make the index check up to +3, since every value is unique and in a sorted array, it
        //can only be at most 3 away if it is increasing by the whole time...
        
        for(int j = 1; j < 4; j++)
        {
            if((i + j < values.size()) && (values[i + j] - values[i] <= 3))
            {
                combinations[i + j] += combinations[i];
            }
        }
    }

    long total = combinations[combinations.size() - 1];

    std::cout << "Part 2: Combinations = " << total << std::endl;
}
