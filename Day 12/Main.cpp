#define __USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <cmath> //abs
typedef std::size_t Index; 


std::vector<std::pair<char, int>> ReadInput();
void Part1();
void Part2();
int getManhattan(int x1, int y1, int x2, int y2);
void process1(char c, int i, int &x, int &y, int &d);
//learnt that % isn't actually a (mod b)...
int mod(int a, int b) { return (a % b + b) % b; }
void process2(char c, int i, int &x, int &y, int &wx, int &wy);
std::pair<int, int> rotatePoint(int x1, int y1, int x2, int y2, double a);

int main()
{
    Part1();
    Part2();
    return 0;
}

std::vector<std::pair<char, int>> ReadInput()
{
    std::ifstream file("data.txt");
    std::string toRead;
    std::vector<std::pair<char, int>> ret;

    while(file >> toRead)
    {
        char c = toRead[0];
        int i = std::stoi(toRead.substr(1, toRead.length()));
        ret.push_back(std::make_pair(c, i));
    }

    return ret;
}

void Part1()
{
    std::vector<std::pair<char, int>> v = ReadInput();
    int x = 0, y = 0;
    //N = 0, E = 1, S = 2, W = 3
    int d = 1;

    for(Index i = 0; i < v.size(); i++)
    {
        process1(v[i].first, v[i].second, x, y, d);
    }

    std::cout << "Part 1: Manhattan = " << getManhattan(0, 0, x, y) << std::endl;
}

void Part2()
{
    std::vector<std::pair<char, int>> v = ReadInput();
    int x = 0, y = 0;
    int wx = 10, wy = 1;

    for(Index i = 0; i < v.size(); i++)
    {
        process2(v[i].first, v[i].second, x, y, wx, wy);
    }

    std::cout << "Part 2: Manhattan = " << getManhattan(0, 0, x, y) << std::endl;
}

int getManhattan(int x1, int y1, int x2, int y2)
{
    return (abs(x2 - x1) + abs(y2 - y1));
}

void process1(char c, int i, int &x, int &y, int& d)
{
    switch(c)
    {
        case 'N':
            y += i;
            break;
        case 'S':
            y -= i;
            break;
        case 'E':
            x += i;
            break;
        case 'W':
            x -= i;
            break;
        case 'L':
            //d = ((d - (i / 90)) % 4);
            d = mod((d - (i / 90)), 4);
            break;
        case 'R':
            d = mod((d + (i / 90)), 4);
            //d = ((d + (i / 90)) % 4);
            break;
        case 'F':
            switch(d)
            {
                case 0:
                    y += i;
                    break;
                case 1:
                    x += i;
                    break;
                case 2:
                    y -= i;
                    break;
                case 3:
                    x -= i;
                    break;
            }
            break;
        default:
            break;
    }
}

void process2(char c, int i, int &x, int &y, int &wx, int &wy)
{
    switch(c)
    {
        case 'N':
            wy += i;
            break;
        case 'S':
            wy -= i;
            break;
        case 'E':
            wx += i;
            break;
        case 'W':
            wx -= i;
            break;
        case 'L':
            //(0, 0) since the ship is the waypoint's origin.
            {
                std::pair<int, int> p = rotatePoint(0, 0, wx, wy, (i * M_PI)/180);
                wx = p.first;
                wy = p.second;
            }
            break;
        case 'R':
            //(0, 0) since the ship is the waypoint's origin.
            {
                i = -i;
                std::pair<int, int> p = rotatePoint(0, 0, wx, wy, (i * M_PI)/180);
                wx = p.first;
                wy = p.second;
            }
            break;
        case 'F':
            x += (i * wx);
            y += (i * wy);
            break;
        default:
            break;
    }
}

//x1, y1 = boat
//x2, y2 = waypoint
//a = degrees in radians for rotation
std::pair<int, int> rotatePoint(int x1, int y1, int x2, int y2, double a)
{
    //https://en.wikipedia.org/wiki/Rotation_(mathematics)#Two_dimensions
    //need to round otherwise it just returns the integer of the double operation
    int x3 = round(x1 + (cos(a) * (x2 - x1)) - (sin(a) * (y2 - y1)));
    int y3 = round(y1 + (sin(a) * (x2 - x1)) + (cos(a) * (y2 - y1)));

    return std::make_pair(x3, y3);
}
