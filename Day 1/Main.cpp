#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream file("data.txt");

    std::vector<int> data;
    int temp;

    while(file >> temp)
    {
        data.push_back(temp);
    }

    file.close();

    int answer = -1;

    for(std::size_t i = 0; i < data.size(); i++)
    {
        for(std::size_t j = 0; j < data.size(); j++)
        {

            for(std::size_t k = 0; k < data.size(); k++)
            {
                if(i == j || i == k || j == k)
                {
                    continue;
                }

                if((data[i] + data[j] + data[k]) == 2020)
                {
                    answer = data[i] * data[j] * data[k];
                    break;
                }
            }
        }
    } 

    std::cout << "ANSWER = " << answer << std::endl;

    return 0;
}
