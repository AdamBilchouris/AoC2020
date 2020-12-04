#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int GetSlope(std::vector<std::vector<char>> vec, int right, int down);
int GetSlope12(std::vector<std::vector<char>> vec);

int main()
{
    std::ifstream file("data.txt");
    
    std::string toRead;

    std::vector<std::vector<char>> map;

    while(std::getline(file, toRead))
    {
        std::vector<char> tempVec;

        for(char &c : toRead)
        {
            tempVec.push_back(c);
        }

        map.push_back(tempVec);
    }


    /*Part 1
    //int counter = 0;
    //1 down 3 right
    //i = down, j = right
    //x = 3*y (mod size of row)
    for(int i = 0; i < map.size(); i += 1)
    {
        //map[i].size() - 1 since we need the max index, not actual size.
        int j = (3 * i) % (map[i].size() - 1);

        if(map[i][j] == '#')
        {
            counter++;
        }
    }

    std::cout << "COUNTER = " << counter << std::endl;
    */

    //Part 2
    std::cout << "(1, 1) = " << GetSlope(map, 1, 1) << std::endl;
    std::cout << "(3, 1) = " << GetSlope(map, 3, 1) << std::endl;
    std::cout << "(5, 1) = " << GetSlope(map, 5, 1) << std::endl;
    std::cout << "(7, 1) = " << GetSlope(map, 7, 1) << std::endl;
    std::cout << "(1, 2) = " << GetSlope12(map) << std::endl;

    int a = GetSlope(map, 1, 1);
    int b = GetSlope(map, 3, 1);
    int c = GetSlope(map, 5, 1);
    int d = GetSlope(map, 7, 1);
    int e = GetSlope12(map);

    int part2 = a * b * c * d * e;

    std::cout << "PART2 Product= " << part2 << std::endl;

    return 0;
}

int GetSlope(std::vector<std::vector<char>> vec, int right, int down)
{
    int counter = 0;
    for(int i = 0; i < vec.size(); i += down)
    {
        //map[i].size() - 1 since we need the max index, not actual size.
        int j = (right * i) % (vec[i].size() - 1);

        if(vec[i][j] == '#')
        {
            counter++;
        }
    }

    return counter;
}

//Other way didnt work for some shit reason.
//Probably bc the vertical change was > 1
//🤷
int GetSlope12(std::vector<std::vector<char>> vec)
{
    int x = 0;
    int y = 0;
    int counter = 0;

    while(y < vec.size() - 1)
    {
        y += 2;
        x += 1;
        x = x % (vec[y].size() - 1);
        
        if(vec[y][x] == '#')
        {
            counter++;
        }
    }

    return counter;
}
