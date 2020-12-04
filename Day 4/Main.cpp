#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

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
    std::ifstream file("data.txt");

    std::string toRead;
    std::string kv;
    int validCounter = 0;

    //byr, iyr, eyr, hgt, hcl, ecl, pid, cid
    bool personBool[] = {false, false, false, false, false, false, false, false};

    while(std::getline(file, toRead))
    {
        if(toRead.compare("") == 0)
        {
            if(personBool[0] && personBool[1] && personBool[2] && personBool[3] && personBool[4] && personBool[5] && personBool[6])
            {
                validCounter += 1;
            }

            for(int i = 0; i <= 7; i++)
            {
                personBool[i] = false;
            }
        }

        std::stringstream ss(toRead);
        while(getline(ss, kv, ' '))
        {
            std::string tempStr = kv.substr(0, 3);

            if(tempStr.compare("byr") == 0 && personBool[0] == false)
            {
                personBool[0] = true;
            }

            if(tempStr.compare("iyr") == 0 && personBool[1] == false)
            {
                personBool[1] = true;
            }

            if(tempStr.compare("eyr") == 0 && personBool[2] == false)
            {
                personBool[2] = true;
            }

            if(tempStr.compare("hgt") == 0 && personBool[3] == false)
            {
                personBool[3] = true;
            }

            if(tempStr.compare("hcl") == 0 && personBool[4] == false)
            {
                personBool[4] = true;
            }

            if(tempStr.compare("ecl") == 0 && personBool[5] == false)
            {
                personBool[5] = true;
            }

            if(tempStr.compare("pid") == 0 && personBool[6] == false)
            {
                personBool[6] = true;
            }

            if(tempStr.compare("cid") == 0 && personBool[7] == false)
            {
                personBool[7] = true;
            }
        }
    }

    std::cout << "Part1: VALID = " << validCounter << std::endl;
}

void Part2()
{
    std::ifstream file("data.txt");

    std::string toRead;
    std::string kv;
    int validCounter = 0;

    //byr, iyr, eyr, hgt, hcl, ecl, pid, cid
    bool personBool[] = {false, false, false, false, false, false, false, false};

    while(std::getline(file, toRead))
    {
        if(toRead.compare("") == 0)
        {
            if(personBool[0] && personBool[1] && personBool[2] && personBool[3] && personBool[4] && personBool[5] && personBool[6])
            {
                validCounter += 1;
            }

            for(int i = 0; i <= 7; i++)
            {
                personBool[i] = false;
            }
        }

        std::stringstream ss(toRead);
        while(getline(ss, kv, ' '))
        {
            std::string tempStr = kv.substr(0, 3);
            std::string value = kv.substr(kv.find(":")+ 1);

            if(tempStr.compare("byr") == 0 && personBool[0] == false)
            {
                int byr = std::stoi(value);

                if(byr <= 2020 && byr >= 1920)
                {
                    personBool[0] = true;
                }
            }

            if(tempStr.compare("iyr") == 0 && personBool[1] == false)
            {
                int iyr = std::stoi(value);

                if(iyr <= 2020 && iyr >= 2010)
                {
                    personBool[1] = true;
                }
            }

            if(tempStr.compare("eyr") == 0 && personBool[2] == false)
            {
                int eyr = std::stoi(value);

                if(eyr <= 2030 && eyr >= 2020)
                {
                    personBool[2] = true;
                }
            }

            if(tempStr.compare("hgt") == 0 && personBool[3] == false)
            {
                std::size_t unitExists = value.find("cm");
                std::size_t impExists = value.find("in");
                if(unitExists == std::string::npos && impExists == std::string::npos)
                {
                    //Not found
                    break;
                }

                std::string unit = value.substr(value.length() - 2);
                int height = std::stoi(value.substr(0, value.length() - 2));

                if(unitExists != std::string::npos)
                {
                    if(height <= 193 && height >= 150)
                    {
                        personBool[3] = true;
                    }
                }

                else
                {
                    if(height <= 76 && height >= 59)
                    {
                        personBool[3] = true;
                    }
                }
            }

            if(tempStr.compare("hcl") == 0 && personBool[4] == false)
            {
                std::size_t hasHash = value.find("#");
                if(hasHash == std::string::npos)
                {
                    //Not found
                    break;
                }

                std::string code = value.substr(1, value.length());

                std::regex reg("[0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f]");
                std::smatch sm;
                std::regex_match (code, sm, reg);

                if(sm.size() == 1)
                {
                    //std::cout << "MATCH = " << sm[0] << std::endl;
                    personBool[4] = true;
                }
            }

            if(tempStr.compare("ecl") == 0 && personBool[5] == false)
            {
                std::string value = kv.substr(kv.find(":")+ 1);

                if(value.compare("amb") == 0 || value.compare("blu") == 0 || value.compare("brn") == 0 || value.compare("gry") == 0
                        || value.compare("grn") == 0 || value.compare("hzl") == 0 || value.compare("oth") == 0)
                {                    
                    personBool[5] = true;
                }
            }

            if(tempStr.compare("pid") == 0 && personBool[6] == false)
            {
                std::string value = kv.substr(kv.find(":")+ 1);

                std::regex reg("\\d\\d\\d\\d\\d\\d\\d\\d\\d");
                std::smatch sm;
                std::regex_match (value, sm, reg);

                if(sm.size() == 1)
                {
                    personBool[6] = true;
                }
            }

            //Do not really need.
            if(tempStr.compare("cid") == 0 && personBool[7] == false)
            {
                personBool[7] = true;
            }
        }
    }

    std::cout << "Part 2: VALID = " << validCounter << std::endl;
}
