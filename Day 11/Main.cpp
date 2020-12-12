#include <iostream>
#include <vector>
#include <fstream>

typedef std::size_t Index; 

std::vector<std::vector<char>> ReadInput();
void Part1();
void Part2();

//Part 1
bool nextGen(std::vector<std::vector<char>>& vec);
int neighbouringSeats(const std::vector<std::vector<char>>& vec, int r, int c);
bool checkSeat(const std::vector<std::vector<char>>& vec, int r, int c);

//Part2
bool nextGen2(std::vector<std::vector<char>>& vec);
int neighbouringSeats2(const std::vector<std::vector<char>>& vec, int r, int c);
bool checkSeat2(const std::vector<std::vector<char>>& vec, int r, int c, int d);

int main()
{
    Part1();
    Part2();
    return 0;
}

std::vector<std::vector<char>> ReadInput()
{
    std::ifstream file("data.txt");
    std::string toRead;
    std::vector<std::vector<char>> ret;
    std::vector<char> tempV;

    while(file >> toRead)
    {
        tempV.clear();

        for(Index i = 0; i < toRead.size(); i++)
        {
            tempV.push_back(toRead[i]);
        }

        ret.push_back(tempV);
    }

    return ret;
}

void Part1()
{
    std::vector<std::vector<char>> ret = ReadInput();

    //Keep looping until we have a steady state
    while(nextGen(ret))
    {
    }

    int occupied = 0;

    for(Index i = 0; i < ret.size(); i++)
    {
        for(Index j = 0; j < ret[i].size(); j++)
        {
            if(ret[i][j] == '#')
            {
                occupied += 1;
            }
        }
    }

    std::cout << "Part 1: Occupied Seats = " << occupied << std::endl;
}

void Part2()
{
    std::vector<std::vector<char>> ret = ReadInput();

    //Keep looping until we have a steady state
    while(nextGen2(ret))
    {
    }

    int occupied = 0;

    for(Index i = 0; i < ret.size(); i++)
    {
        for(Index j = 0; j < ret[i].size(); j++)
        {
            if(ret[i][j] == '#')
            {
                occupied += 1;
            }
        }
    }

    std::cout << "Part 2: Occupied Seats = " << occupied << std::endl;
}

//Basic cellular automata
//https://rosettacode.org/wiki/Conway%27s_Game_of_Life#Simple_Without_Classes
//void updateCells(...)
bool nextGen(std::vector<std::vector<char>>& vec)
{
    //Adjust the new state, keep the old state the same
    std::vector<std::vector<char>> newVec = vec;
    bool changed = false;

    for(Index i = 0; i < vec.size(); i++)
    {
        for(Index j = 0; j < vec[i].size(); j++)
        {
            if((vec[i][j] == 'L') && (neighbouringSeats(vec, i, j) == 0))
            {
                newVec[i][j] = '#';
                changed = true;
            }

            if((vec[i][j] == '#') && (neighbouringSeats(vec, i, j) >= 4))
            {
                newVec[i][j] = 'L';
                changed = true;
            }
        }
    }

    vec = newVec;

    return changed;
}

int neighbouringSeats(const std::vector<std::vector<char>>& vec, int r, int c)
{
    int neighbours = 0;

    //N
    if(checkSeat(vec, r - 1, c)) 
    {
        neighbours += 1;
    }
    //S
    if(checkSeat(vec, r + 1, c))
    {
        neighbours += 1;
    }

    //E
    if(checkSeat(vec, r, c + 1))
    {
        neighbours += 1;
    }

    //W
    if(checkSeat(vec, r, c - 1))
    {
        neighbours += 1;
    }
   
    //NE
    if(checkSeat(vec, r - 1, c + 1))
    {
        neighbours += 1;
    }

    //NW
    if(checkSeat(vec, r - 1, c - 1))
    {
        neighbours += 1;
    }

    //SE
    if(checkSeat(vec, r + 1, c + 1))
    {
        neighbours += 1;
    }

    //SW
    if(checkSeat(vec, r + 1, c - 1))
    {
        neighbours += 1;
    }

    return neighbours;
}
bool checkSeat(const std::vector<std::vector<char>>& vec, int r, int c)
{
    if((r < 0) || (r >= vec.size()) || (c < 0) || (c >= vec[r].size()))
    {
        return false;
    }

    return vec[r][c] == '#' ? true : false;
}

bool nextGen2(std::vector<std::vector<char>>& vec)
{
    std::vector<std::vector<char>> newVec = vec;
    bool changed = false;

    for(Index i = 0; i < vec.size(); i++)
    {
        for(Index j = 0; j < vec[i].size(); j++)
        {
            if((vec[i][j] == 'L') && (neighbouringSeats2(vec, i, j) == 0))
            {
                newVec[i][j] = '#';
                changed = true;
            }

            if((vec[i][j] == '#') && (neighbouringSeats2(vec, i, j) >= 5))
            {
                newVec[i][j] = 'L';
                changed = true;
            }
        }
    }

    vec = newVec;

    return changed;
}

int neighbouringSeats2(const std::vector<std::vector<char>>& vec, int r, int c)
{
    //Recursively find the seat in the direction, if there is one.
    int counter = 0;
    //N
    if(checkSeat2(vec, r - 1, c, 0))
    {
        counter += 1;
    }

    //S
    if(checkSeat2(vec, r + 1, c, 1))
    {
        counter += 1;
    }

    //E
    if(checkSeat2(vec, r, c + 1, 2))
    {
        counter += 1;
    }

    //W
    if(checkSeat2(vec, r, c - 1, 3))
    {
        counter += 1;
    }

    //NE
    if(checkSeat2(vec, r - 1, c + 1, 4))
    {
        counter += 1;
    }

    //NW
    if(checkSeat2(vec, r - 1, c - 1, 5))
    {
        counter += 1;
    }

    //SE
    if(checkSeat2(vec, r + 1, c + 1, 6))
    {
        counter += 1;
    }

    //SW
    if(checkSeat2(vec, r + 1, c - 1, 7))
    {
        counter += 1;
    }

    return counter;
}

bool checkSeat2(const std::vector<std::vector<char>>& vec, int r, int c, int d)
{
    //Out of range sanity check
    if((r < 0) || (r >= vec.size()) || (c < 0) || (c >= vec[r].size()))
    {
        return false;
    }

    if(vec[r][c] == '#')
    {
        return true;
    }

    if(vec[r][c] == 'L')
    {
        return false;
    }

    //Check the next one which is one of the 8 directions based on the current
    //one. Recursion seems best for this...
    switch(d)
    {
        //N
        case 0:
            return checkSeat2(vec, r - 1, c, 0);
        //S
        case 1:
            return checkSeat2(vec, r + 1, c, 1);
        //E
        case 2:
            return checkSeat2(vec, r, c + 1, 2);
        //W
        case 3:
            return checkSeat2(vec, r, c - 1, 3);
        //NE
        case 4:
            return checkSeat2(vec, r - 1, c + 1, 4);
        //NW
        case 5:
            return checkSeat2(vec, r - 1, c - 1, 5);
        //SE
        case 6:
            return checkSeat2(vec, r + 1, c + 1, 6);
        //SW
        case 7:
            return checkSeat2(vec, r + 1, c - 1, 7);
    }
}
