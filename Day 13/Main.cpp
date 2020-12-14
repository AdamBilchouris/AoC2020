#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <utility>

typedef std::size_t Index; 

std::vector<std::pair<int, int>> ReadInput();
void Part1();
void Part2();
std::vector<std::string> split(std::string s, char delimiter);
//unsigned long multInv(unsigned long a, unsigned long b);
//All our input are prime numbers (second line), so we can Euler's Theorem to
//get the multiplicative inverse of a.
//unsigned long multInv(unsigned long a, unsigned long b); //Do not need since all the IDs are prime...
unsigned long modExp(unsigned long a, unsigned long b, unsigned long p);

int main()
{
    Part1();
    Part2();
    return 0;
}

std::vector<std::pair<int, int>> ReadInput()
{
    std::ifstream file("data.txt");
    std::string toRead;
    //id, pos
    std::vector<std::pair<int, int>> ret;

    while(file >> toRead)
    {
        std::vector<std::string> s = split(toRead, ',');

        for(Index i = 0; i < s.size(); i++)
        {
            if(s[i].compare("x") != 0)
            {
                ret.push_back(std::make_pair(std::stoi(s[i]), i));
            }
        }
    }

    return ret; 
}

void Part1()
{
    std::vector<std::pair<int, int>> v = ReadInput();

    int time = v[0].first;
    std::vector<std::vector<int>> t;
    int smallest = -1;
    int wait = -1;
    int targetBus = -1;
    int targetWait = 100000;

    for(Index i = 1; i < v.size(); i++)
    {
        int div = time / v[i].first;

        //Get the next multiple of the ID's schedule
        smallest = (1 + div) * v[i].first;
        wait = smallest - time;
        if(wait < targetWait)
        {
            targetWait = wait;
            targetBus = v[i].first;
        }
    }

    std::cout << "Part 1 = " << (targetWait * targetBus) << std::endl;
}

void Part2()
{
    std::vector<std::pair<int, int>> v = ReadInput();

    //https://rosettacode.org/wiki/Chinese_remainder_theorem#C
    unsigned long p, i, prod = 1;
    unsigned long sum = 0;

    for(i = 1; i < v.size(); i++)
    {
        prod *= v[i].first;
    }

    for(i = 1; i < v.size(); i++)
    {
        p = prod / v[i].first;
        sum += (v[i].first - v[i].second) * modExp(p, v[i].first - 2, v[i].first) * p;
    }

    std::cout << "Part 2 = " << (sum % prod) << std::endl;

}

std::vector<std::string> split(std::string s, char delimiter)
{
    std::vector<std::string> ret;
    std::stringstream ss(s);
    std::string temp;

    while(std::getline(ss, temp, delimiter))
    {
        ret.push_back(temp);
    }

    return ret;
}

//rosettacode.org/wiki/Chinese_remainder_theorem#C
/*
unsigned long multInv(unsigned long a, unsigned long b)
{
    unsigned long b0 = b, t, q;
    unsigned long x0 = 0, x1 = 1;

    if(b == 1)
    {
        return 1;
    }

    while(a > 1)
    {
        q = a / b;
        t = b, b = a % b, a = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }

    if(x1 < 0)
    {
        x1 += b0;
    }

    return x1;
}
*/

//https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
unsigned long modExp(unsigned long a, unsigned long b, unsigned long p)
{
    unsigned long ret = 1;

    a = a % p;

    if(a == 0)
    {
        return 0;
    }

    while(b > 0)
    {
        //b is odd
        if(b % 2 == 1)
        {
            ret = (ret * a) % p;
        }

        b /= 2;
        a = (a * a) % p;
    }

    return ret;
}
