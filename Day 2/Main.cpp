#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

int main()
{
    std::ifstream file("data.txt");
    std::vector<int> lows;
    std::vector<int> highs;
    std::vector<char> chars;
    std::vector<std::string> strings;

    std::vector<std::string> valids;
    
    std::string toRead;
    
    while(std::getline(file, toRead))
    {
        std::istringstream iss(toRead);
        std::string low, high, charS, str;
        
        std::getline(iss, low, '-');
        std::getline(iss, high, ' ');
        std::getline(iss, charS, ':');
        iss >> str;

        int lowInt = std::stoi(low);
        int highInt = std::stoi(high);

        //Insert into vectors
        lows.push_back(lowInt);
        highs.push_back(highInt);
        chars.push_back(charS[0]);
        strings.push_back(str);
    }

    //Part 1
    /*
    for(std::size_t i = 0; i < lows.size(); i++)
    {
        int counter = 0;

        for(std::size_t j = 0; j < strings[i].size(); j++)
        {
            if(chars[i] == strings[i][j])
            {
                counter += 1;
            }
        }

        if(counter < lows[i])
        {
            continue;
        }

        if(counter > highs[i])
        {
            continue;
        }

        if(counter >= lows[i] && counter <= highs[i])
        {
            valids.push_back(strings[i]);
        }
    }
    */

    for(std::size_t i = 0; i < lows.size(); i++)
    {
        int counter = 0;

        int actualLow = lows[i] - 1;
        int actualHigh = highs[i] - 1;

        if(strings[i][actualLow] == chars[i])
        {
            std::cout << "STR : " << strings[i][actualLow] << " | CHAR : " << chars[i] << std::endl;
            counter += 1;
        }

        if(strings[i][actualHigh] == chars[i])
        {
            std::cout << "STR : " << strings[i][actualHigh] << " | CHAR : " << chars[i] << std::endl;
            counter += 1;
        }


        if(counter == 1)
        {
            valids.push_back(strings[i]);
        }

        std::cout << "COUNTER = " << counter << std::endl;

        std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    }

    std::cout << "Valid passwords = " << valids.size() << std::endl;
    return 0;
}
