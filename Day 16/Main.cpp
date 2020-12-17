#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <regex>

typedef std::size_t Index; 

//name, such as class : (low, high)
std::unordered_map<std::string, std::tuple<int, int, int, int>> fields;
//name of the fields
std::vector<std::string> fieldString;
std::vector<int> myTicket;
std::vector<std::vector<int>> nearbyTickets;
//indices for tickets to remove in nearbyTickets
std::vector<int> ticketsRemove;

void ReadFile();
void Part1();
void Part2();
std::vector<std::string> explode(const std::string& s, char delim);
bool checkRange(int a, int b, int x) { return (a <= x && b >= x); }

int main()
{
    ReadFile();
    Part1();
    Part2();
    return 0;
}

void ReadFile()
{
    std::ifstream f("data.txt");
    std::string toRead;
    std::vector<std::string> sv;

    //regex
    //std::string fieldStr = "(\\w+): ([\\d]+)-([\\d]+) or ([\\d]+)-([\\d]+)";
    std::string fieldStr = "(\\w+(\\s\\w+)?): ([\\d]+)-([\\d]+) or ([\\d]+)-([\\d]+)";
    std::regex reg (fieldStr);
    std::smatch sm;

    while(std::getline(f, toRead))
    {
        if(toRead.compare("") == 0)
        {
            continue;
        }

        //Get my ticket
        if(toRead.compare("your ticket:") == 0)
        {
            std::getline(f, toRead);
            sv.clear();
            sv = explode(toRead, ',');

            for(int i = 0; i < sv.size(); i++)
            {
                myTicket.push_back(std::stoi(sv[i]));
            }

            continue;
        }

        //Get the other people's tickets
        if(toRead.compare("nearby tickets:") == 0)
        {
            while(std::getline(f, toRead))
            {
                sv.clear();
                sv = explode(toRead, ',');
                std::vector<int> iv;

                for(int i = 0; i < sv.size(); i++)
                {
                    iv.push_back(std::stoi(sv[i]));
                }

                nearbyTickets.push_back(iv);
            }
        }

        //Get the fields and ranges
        else
        {
            std::regex_match (toRead, sm, reg);

            if(sm.size() == 7)
            {
                fields[sm[1]] = std::make_tuple(std::stoi(sm[3]), std::stoi(sm[4]), std::stoi(sm[5]), std::stoi(sm[6]));
                fieldString.push_back(sm[1]);
            }
        }
    }

    f.close();
}

void Part1()
{
    //Check nearby tickets
    int counter = 0;
    int currVal = 0;
    int validC = 0;
    int invalidC = 0;

    //Go through each ticket
    for(Index i = 0; i < nearbyTickets.size(); i++)
    {
        currVal = 0;

        //Go through each ticket's values
        for(Index j = 0; j < nearbyTickets[i].size(); j++)
        {
            validC = 0;
            invalidC = 0;
            currVal = nearbyTickets[i][j];
            //Go through the fields
            for(auto iter = fields.begin(); iter != fields.end(); iter++)
            {
                auto k = iter->second;
                if(checkRange(std::get<0>(k), std::get<1>(k), currVal) || checkRange(std::get<2>(k), std::get<3>(k), currVal))
                {
                    validC += 1;
                }

                else
                {
                    invalidC += 1;
                }
            }

            //No fields are satisfied
            if(validC < 1)
            {
                counter += currVal;
                ticketsRemove.push_back(i);
                break;
            }
        }
    }

    std::cout << "Part 1 = " << counter << std::endl;
}

void Part2()
{
    std::vector<std::vector<int>> removed;
    std::copy(nearbyTickets.begin(), nearbyTickets.end(), std::back_inserter(removed));

    //Delete duplicate tickets
    for(int i = ticketsRemove.size() - 1; i >= 0; i--)
    {
        removed.erase(removed.begin() + ticketsRemove[i]);
    }

    int colCount = 0;
    std::vector<int> valsCheck;
    //field name : position in ticket (0 to n)
    //std::unordered_map<std::string, int> fieldPos;
    std::unordered_map<std::string, std::vector<int>> fieldPos;

    //Generate all possible indices for a given field
    for(Index i = 0; i < removed.size(); i++)
    {
        valsCheck.clear();
        for(Index j = 0; j < fields.size(); j++)
        {
            colCount = 0;
            auto iter = fields[fieldString[j]];
            int a1 = std::get<0>(iter);
            int b1 = std::get<1>(iter);
            int a2 = std::get<2>(iter);
            int b2 = std::get<3>(iter);

            for(Index k = 0; k < removed.size() && (j == 0); k++)
            {
                int val = removed[k][i];
                valsCheck.push_back(val);
            }

            for(Index k = 0; k < valsCheck.size(); k++)
            {
                bool inRange = (checkRange(a1, b1, valsCheck[k]) || checkRange(a2, b2, valsCheck[k]));
                if(inRange)
                {
                    colCount += 1;
                }
            }

            if(colCount == removed.size())
            {
                fieldPos[fieldString[j]].push_back(i);
            }
        }
    }

    std::vector<std::string> lowValsFirst;
    int lowest = 1;

    while(lowValsFirst.size() < fieldPos.size())
    {
        for(auto iter = fieldPos.begin(); iter != fieldPos.end(); iter++)
        {
            if((iter->second).size() <= lowest && (std::find(lowValsFirst.begin(), lowValsFirst.end(), iter->first) == lowValsFirst.end()))
            {
                lowValsFirst.push_back(iter->first);
                lowest = (iter->second).size();
            }
        }

        lowest += 1;
    }

    //indexed the same as lowValsFirst
    std::vector<int> confirmed;

    //Remove duplicates
    for(int i = 0; i < lowValsFirst.size(); i++)
    {
        confirmed.push_back(fieldPos[lowValsFirst[i]][0]);

        for(int j = i + 1; j < lowValsFirst.size(); j++)
        {
            for(int k = fieldPos[lowValsFirst[j]].size() - 1; k >= 0; k--)
            {
                if(fieldPos[lowValsFirst[j]][k] == fieldPos[lowValsFirst[i]][0])
                {
                    fieldPos[lowValsFirst[j]].erase(fieldPos[lowValsFirst[j]].begin() + k);
                }
            }
        }
    }

    long ans = 1;
    for(int i = 0; i < confirmed.size(); i++)
    {
        if(lowValsFirst[i].find("departure") != std::string::npos)
        {
            ans *= myTicket[confirmed[i]];
        }
    }

    std::cout << "Part 2 = "  << ans << std::endl;
}

std::vector<std::string> explode(const std::string& s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}
