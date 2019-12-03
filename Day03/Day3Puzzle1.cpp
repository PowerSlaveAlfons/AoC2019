#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

void moveWire1(std::string input, std::vector<std::pair<int, int>> *VisitedSpots, signed int *x, signed int *y)
{

    char Direction = input[0];
    input.erase(0, 1);
    int size = 0;

    switch (Direction)
    {
    case 'U':
        *y += std::stoi(input);
        size = VisitedSpots->size();
        VisitedSpots->push_back(std::make_pair(*x, *y));
        std::cout << VisitedSpots->at(VisitedSpots->back()).first << " and " VisitedSpots->at(VisitedSpots.back).second << std::endl;
        break;

    case 'L':
        *x -= std::stoi(input);
        size = VisitedSpots->size();
        VisitedSpots->push_back(std::make_pair(*x, *y));
        std::cout << VisitedSpots->at(VisitedSpots->back()).first << " and " VisitedSpots->at(VisitedSpots.back).second << std::endl;
        break;

    case 'D':
        *y -= std::stoi(input);
        size = VisitedSpots->size();
        VisitedSpots->push_back(std::make_pair(*x, *y));
        std::cout << VisitedSpots->at(VisitedSpots->back()).first << " and " VisitedSpots->at(VisitedSpots.back).second << std::endl;
        break;

    case 'R':
        *x += std::stoi(input);
        size = VisitedSpots->size();
        VisitedSpots->push_back(std::make_pair(*x, *y));
        std::cout << VisitedSpots->at(VisitedSpots->back()).first << " and " VisitedSpots->at(VisitedSpots.back).second << std::endl;
        break;

    default:
        std::cout << "Illegal Move" << std::endl;
        break;
    }
}

std::pair<int, int> moveWire2(std::string input, std::vector<std::pair<int, int>> *VisitedSpots, signed int *x, signed int *y)
{
    std::vector<std::pair<int, int>> Intersections;
    std::pair<int, int> PairToFind;
    char Direction = input[0];
    input.erase(0, 1);

    switch (Direction)
    {
    case 'U':
        PairToFind = std::make_pair(*x, *y);
        *y += std::stoi(input);
        for (auto Elem : *VisitedSpots)
        {
            if (PairToFind == Elem)
            {
                std::cout << "Found intersection at " << Elem.first << " " << Elem.second << std::endl;
                return PairToFind;
            }
        }

        break;

    case 'L':
        *x -= std::stoi(input);
        PairToFind = std::make_pair(*x, *y);
        for (auto Elem : *VisitedSpots)
        {
            if (PairToFind == Elem)
            {
                std::cout << "Found intersection at " << Elem.first << " " << Elem.second << std::endl;
                return PairToFind;
            }
        }
        break;

    case 'D':
        PairToFind = std::make_pair(*x, *y);
        *y -= std::stoi(input);
        for (auto Elem : *VisitedSpots)
        {
            if (PairToFind == Elem)
            {
                std::cout << "Found intersection at " << Elem.first << " " << Elem.second << std::endl;
                return PairToFind;
            }
        }
        break;

    case 'R':
        PairToFind = std::make_pair(*x, *y);
        *x += std::stoi(input);
        for (auto Elem : *VisitedSpots)
        {
            if (PairToFind == Elem)
            {
                std::cout << "Found intersection at " << Elem.first << " " << Elem.second << std::endl;
                return PairToFind;
            }
        }
        break;

    default:
        std::cout << "Illegal Move" << std::endl;
        break;
    }
    return std::make_pair(0, 0);
}

int main()
{
    std::ifstream myfile("Day3Input.txt"); // hardcoded because lazy
    std::vector<std::pair<int, int>> Wire1Path;
    std::string input;
    std::string auxString;
    std::vector<std::string> tokens;
    std::vector<std::string> Wire1Instructions;
    std::vector<std::string> Wire2Instructions;
    std::vector<std::pair<int, int>> VisitedSpots;
    const std::string delim = ",";
    size_t pos = 0;
    signed int x = 0;
    signed int y = 0;
    std::vector<std::pair<int, int>> Intersections;

    if (myfile.is_open())
    {

        for (std::string each; std::getline(myfile, each, '\n'); tokens.push_back(each))
            ;

        //std::cout << tokens[0] << std::endl;

        while ((pos = tokens[0].find(',')) != std::string::npos)
        {
            auxString = tokens[0].substr(0, pos);
            Wire1Instructions.push_back(auxString);
            tokens[0].erase(0, pos + delim.length());
        }
        Wire1Instructions.push_back(tokens[0]);
        while ((pos = tokens[1].find(',')) != std::string::npos)
        {
            auxString = tokens[1].substr(0, pos);
            Wire2Instructions.push_back(auxString);
            tokens[1].erase(0, pos + delim.length());
        }
        Wire2Instructions.push_back(tokens[1]);
    }
    else
        std::cout << "Unable to open file";

    for (auto str : Wire1Instructions)
    {
        moveWire1(str, &VisitedSpots, &x, &y); //saving every spot wire 1 has been to
    }
    x = 0; //resetting coordinates to starting point
    y = 0;

    for (auto str : Wire2Instructions)
    {
        Intersections.push_back(moveWire2(str, &VisitedSpots, &x, &y));
    }

    //std::cout << "Tokensize: " << tokens.size() << std::endl;

    for (auto pair : Intersections)
    {
        std::cout << pair.first << " and " << pair.second << std::endl;
    }

    return 0;
}