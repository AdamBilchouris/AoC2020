#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <bitset>
#include <algorithm>
#include <map>
#include <cmath>
#include <set>
#include <utility>
#include <cstdlib>
#include <ctime>

typedef std::size_t Index; 
#define BIT_SIZE 36

void Part1();
void Part2();
std::vector<std::string> split(std::string s, char delimiter);
std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

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
    std::string mask;
    //unsigned long mask;
    //unsigned long mask2;
    //index, value
    std::map<int, unsigned long> mem;

    while(std::getline(file, toRead))
    {
        //std::cout << toRead << std::endl;
        std::vector<std::string> s = split(toRead, '=');
        for(Index i = 0; i < s.size(); i++)
        {
            s[i] = trim(s[i]);
        }

        if(s[0].compare("mask") == 0)
        {
            mask = s[1];
            /*
             * Smarter way
            //make all Xs a 0, make all other bits 0
            std::string maskS(BIT_SIZE, '0'); std::transform(s[1].begin(), s[1].end(), maskS.begin(), [](char c) { return c == 'X' ? '1' : '0'; });
            //make all X bits 0, keep the bits with value 1
            std::string mask2S(BIT_SIZE, '0'); std::transform(s[1].begin(), s[1].end(), mask2S.begin(), [](char c) { return c == 'X' ? '0' : c; });

            mask = std::bitset<BIT_SIZE>(maskS).to_ulong();
            mask2 = std::bitset<BIT_SIZE>(mask2S).to_ulong();
            //std::cout << mask << std::endl;
            //std::cout << mask2 << std::endl;
            */
        }

        else
        {
            int loc = -1;
            unsigned long val = -1;

            //mem[ -> 0, 1, 3, 4
            //... ] -> size() - 1
            //-4 for the mem[, -1 for the last ]
            std::string ss = s[0].substr(4, s[0].size() - 4 - 1);
            loc = std::stoul(ss);

            /*
             * Smarter way
            val = std::stoul(s[1]);
            //std::cout << ((val & mask) | mask2) << std::endl;
            mem[loc] = ((val & mask) | mask2);
            */

            std::bitset<BIT_SIZE> bval = std::bitset<BIT_SIZE>(std::stoul(s[1]));
            std::string sval = bval.to_string();

            for(Index i = 0; i < BIT_SIZE; i++)
            {
                switch(mask[i])
                {
                    case 'X':
                        break;
                    case '0':
                        sval[i] = '0';
                        break;
                    case '1':
                        sval[i] = '1';
                        break;
                }
            }

            val = std::stoul(sval, nullptr, 2);
            mem[loc] = val;
        }
    }

    std::uintmax_t sum = 0;
    for(auto m : mem)
    {
        sum += m.second;
    }

    std::cout << "Part 1 = " << sum << std::endl;
}

void Part2()
{
    std::ifstream file("data.txt");
    std::string toRead;
    std::string mask;
    //index, value
    std::map<unsigned long long, unsigned long long> mem;

    while(std::getline(file, toRead))
    {
        //std::cout << toRead << std::endl;
        std::vector<std::string> s = split(toRead, '=');
        for(Index i = 0; i < s.size(); i++)
        {
            s[i] = trim(s[i]);
        }

        if(s[0].compare("mask") == 0)
        {
            mask = s[1];
        }

        else
        {
            unsigned long long loc = -1;
            unsigned long long val = -1;

            std::string ss = s[0].substr(4, s[0].size() - 4 - 1);
            loc = std::stoul(ss);
            val = std::stoul(s[1]);

            std::bitset<BIT_SIZE> bval = std::bitset<BIT_SIZE>(loc);
            std::string sval = bval.to_string();

            for(Index i = 0; i < BIT_SIZE; i++)
            {
                switch(mask[i])
                {
                    case 'X':
                        sval[i] = 'X';
                        break;
                    case '0':
                        break;
                    case '1':
                        sval[i] = '1';
                        break;
                }
            }

            int noX = 0;

            for(Index i = 0; i < BIT_SIZE; i++)
            {
                if(sval[i] == 'X')
                {
                    noX += 1;
                }
            }

            noX = pow(2, noX);
            std::set<std::string> addresses;
            int changed = 0;

            while(changed < noX)
            {
                std::string temp = sval;
                for(Index i = 0; i < temp.size(); i++)
                {
                    if(temp[i] == 'X')
                    {
                        int type = rand() % 2;

                        switch(type)
                        {
                            case 0:
                                temp[i] = '0';
                                break;
                            case 1:
                                temp[i] = '1';
                                break;
                        }
                    }
                }

                if(addresses.find(temp) == addresses.end())
                {
                    addresses.insert(temp);
                    changed += 1;
                }
            }  

            for(auto it = addresses.begin(); it != addresses.end(); it++)
            {
                unsigned long long index = std::bitset<BIT_SIZE>(*it).to_ullong();
                mem[index] = val;
            }
        }
    }

    unsigned long long sum = 0;
    for(auto m : mem)
    {
        sum += m.second;
    }

    std::cout << "Part 2 = " << sum << std::endl;
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

//http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
std::string& ltrim(std::string& str, const std::string& chars)
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string& rtrim(std::string& str, const std::string& chars)
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string& trim(std::string& str, const std::string& chars)
{
    return ltrim(rtrim(str, chars), chars);
}
