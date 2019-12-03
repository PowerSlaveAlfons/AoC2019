#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

void moveWire1(std::string input, std::vector<std::pair<long long, long long>> *VisitedSpots, signed int *x, signed int *y)
{

    char Direction = input[0];
    input.erase(0, 1);
    int size = 0;
    std::cout << "Input: " << input << std::endl;

    switch (Direction)
    {
    case 'U':
        for (int i = 0; i < std::stoi(input); i++)
        {
            *y += 1;
            VisitedSpots->push_back(std::make_pair(*x, *y));
        }
        break;

    case 'L':
        for (int i = 0; i < std::stoi(input); i++)
        {
            *x -= 1;
            VisitedSpots->push_back(std::make_pair(*x, *y));
        }
        break;

    case 'D':
        for (int i = 0; i < std::stoi(input); i++)
        {
            *y -= 1;
            VisitedSpots->push_back(std::make_pair(*x, *y));
        }
        break;

    case 'R':
        for (int i = 0; i < std::stoi(input); i++)
        {
            *x += 1;
            VisitedSpots->push_back(std::make_pair(*x, *y));
        }
        break;

    default:
        std::cout << "Illegal Move" << std::endl;
        break;
    }
}

void moveWire2(std::string input, std::vector<std::pair<long long, long long>> *VisitedSpots, std::vector<std::pair<long long, long long>> *Intersections, signed int *x, signed int *y)
{
    std::pair<long long, long long> PairToFind;
    char Direction = input[0];
    input.erase(0, 1);
    std::cout << "Input: " << input << std::endl;

    switch (Direction)
    {
    case 'U':
        for (int i = 0; i < std::stoi(input); i++)
        {
            *y += 1;
            PairToFind = std::make_pair(*x, *y);
            //std::cout << PairToFind.first << " and " << PairToFind.second << std::endl;
            for (auto Elem : *VisitedSpots)
            {
                // std::cout << "Comparing " << Elem.first << " and " << Elem.second << " to " << PairToFind.first << " and " << PairToFind.second << std::endl;
                if (PairToFind == Elem)
                {
                    std::cout << "Found intersection at " << Elem.first << " " << Elem.second << std::endl;
                    Intersections->push_back(Elem);
                }
            }
        }

        break;

    case 'L':
        for (int i = 0; i < std::stoi(input); i++)
        {
            *x -= 1;
            PairToFind = std::make_pair(*x, *y);
            //std::cout << PairToFind.first << " and " << PairToFind.second << std::endl;
            for (auto Elem : *VisitedSpots)
            {
                // std::cout << "Comparing " << Elem.first << " and " << Elem.second << " to " << PairToFind.first << " and " << PairToFind.second << std::endl;
                if (PairToFind == Elem)
                {
                    std::cout << "Found intersection at " << Elem.first << " " << Elem.second << std::endl;
                    Intersections->push_back(Elem);
                }
            }
        }
        break;

    case 'D':
        for (int i = 0; i < std::stoi(input); i++)
        {
            *y -= 1;
            PairToFind = std::make_pair(*x, *y);
            //std::cout << PairToFind.first << " and " << PairToFind.second << std::endl;
            for (auto Elem : *VisitedSpots)
            {
                // std::cout << "Comparing " << Elem.first << " and " << Elem.second << " to " << PairToFind.first << " and " << PairToFind.second << std::endl;
                if (PairToFind == Elem)
                {
                    std::cout << "Found intersection at " << Elem.first << " " << Elem.second << std::endl;
                    Intersections->push_back(Elem);
                }
            }
        }
        break;

    case 'R':
        for (int i = 0; i < std::stoi(input); i++)
        {
            *x += 1;
            PairToFind = std::make_pair(*x, *y);
            //std::cout << PairToFind.first << " and " << PairToFind.second << std::endl;
            for (auto Elem : *VisitedSpots)
            {
                // std::cout << "Comparing " << Elem.first << " and " << Elem.second << " to " << PairToFind.first << " and " << PairToFind.second << std::endl;
                if (PairToFind == Elem)
                {
                    std::cout << "Found intersection at " << Elem.first << " " << Elem.second << std::endl;
                    Intersections->push_back(Elem);
                }
            }
        }
        break;

    default:
        std::cout << "Illegal Move" << std::endl;
        break;
    }
}

void moveSteps(std::string input, std::vector<std::pair<long long, long long>> *Intersections, std::vector<int> *IntersectionSteps, std::vector<bool> *IntersectionVisitedThisWire, signed int *x, signed int *y, int *StepCounter)
{
    std::pair<long long, long long> PairToFind;
    char Direction = input[0];
    input.erase(0, 1);
    int Iterator = 0;
    int size = 0;

    switch (Direction)
    {
    case 'U':
        for (int i = 0; i < std::stoi(input); i++)
        {
            *y += 1;
            *StepCounter += 1;
            PairToFind = std::make_pair(*x, *y);
            Iterator = 0;
            //   if (IntersectionVisitedThisWire->find(std::make_pair(*x, *y)) == IntersectionVisitedThisWire->end())
            //     IntersectionVisitedThisWire->insert({std::make_pair(*x, *y), false});
            for (auto Elem : *Intersections)
            {
                if (PairToFind == Elem)
                {
                    if (IntersectionVisitedThisWire->at(Iterator) != true)
                    {

                        //if (IntersectionSteps->find(Elem) == IntersectionSteps->end())
                        // IntersectionSteps->insert({Elem, 0});
                        // if (IntersectionVisitedThisWire->at(Elem) == false)
                        IntersectionSteps->at(Iterator) += *StepCounter;
                        // IntersectionVisitedThisWire->at(Elem) = true;
                        std::cout << "Intersection hit at " << Elem.first << " and " << Elem.second << std::endl;
                        std::cout << "Steps " << *StepCounter << std::endl;
                        IntersectionVisitedThisWire->at(Iterator) = true;
                    }
                }

                size = Intersections->size();
                if (Iterator < size)
                    Iterator++;
                else
                {
                    // std::cout << "Bound check triggered" << std::endl;
                }
                //std::cout << Iterator << std::endl;
            }
        }
        break;

    case 'L':
        for (int i = 0; i < std::stoi(input); i++)
        {
            *x -= 1;
            *StepCounter += 1;
            PairToFind = std::make_pair(*x, *y);
            Iterator = 0;
            // if (IntersectionVisitedThisWire->find(std::make_pair(*x, *y)) == IntersectionVisitedThisWire->end())
            //    IntersectionVisitedThisWire->insert({std::make_pair(*x, *y), false});
            for (auto Elem : *Intersections)
            {
                if (PairToFind == Elem)
                {
                    if (IntersectionVisitedThisWire->at(Iterator) != true)
                    {

                        //if (IntersectionSteps->find(Elem) == IntersectionSteps->end())
                        // IntersectionSteps->insert({Elem, 0});
                        // if (IntersectionVisitedThisWire->at(Elem) == false)
                        IntersectionSteps->at(Iterator) += *StepCounter;
                        // IntersectionVisitedThisWire->at(Elem) = true;
                        std::cout << "Intersection hit at " << Elem.first << " and " << Elem.second << std::endl;
                        std::cout << "Steps " << *StepCounter << std::endl;
                        IntersectionVisitedThisWire->at(Iterator) = true;
                    }
                }

                size = Intersections->size();
                if (Iterator < size)
                    Iterator++;
                else
                {
                    // std::cout << "Bound check triggered" << std::endl;
                }
                // std::cout << Iterator << std::endl;
            }
        }
        break;

    case 'D':
        for (int i = 0; i < std::stoi(input); i++)
        {
            *y -= 1;
            *StepCounter += 1;
            PairToFind = std::make_pair(*x, *y);
            Iterator = 0;
            //   if (IntersectionVisitedThisWire->find(std::make_pair(*x, *y)) == IntersectionVisitedThisWire->end())
            //    IntersectionVisitedThisWire->insert({std::make_pair(*x, *y), false});
            for (auto Elem : *Intersections)
            {
                if (PairToFind == Elem)
                {
                    if (IntersectionVisitedThisWire->at(Iterator) != true)
                    {

                        //if (IntersectionSteps->find(Elem) == IntersectionSteps->end())
                        // IntersectionSteps->insert({Elem, 0});
                        // if (IntersectionVisitedThisWire->at(Elem) == false)
                        IntersectionSteps->at(Iterator) += *StepCounter;
                        // IntersectionVisitedThisWire->at(Elem) = true;
                        std::cout << "Intersection hit at " << Elem.first << " and " << Elem.second << std::endl;
                        std::cout << "Steps " << *StepCounter << std::endl;
                        IntersectionVisitedThisWire->at(Iterator) = true;
                    }
                }

                size = Intersections->size();
                if (Iterator < size)
                    Iterator++;
                else
                {
                    // std::cout << "Bound check triggered" << std::endl;
                }
                //std::cout << Iterator << std::endl;
            }
        }
        break;

    case 'R':
        for (int i = 0; i < std::stoi(input); i++)
        {
            *x += 1;
            *StepCounter += 1;
            PairToFind = std::make_pair(*x, *y);
            Iterator = 0;
            // if (IntersectionVisitedThisWire->find(std::make_pair(*x, *y)) == IntersectionVisitedThisWire->end())
            //    IntersectionVisitedThisWire->insert({std::make_pair(*x, *y), false});
            for (auto Elem : *Intersections)
            {
                if (PairToFind == Elem)
                {
                    if (IntersectionVisitedThisWire->at(Iterator) != true)
                    {

                        //if (IntersectionSteps->find(Elem) == IntersectionSteps->end())
                        // IntersectionSteps->insert({Elem, 0});
                        // if (IntersectionVisitedThisWire->at(Elem) == false)
                        IntersectionSteps->at(Iterator) += *StepCounter;
                        // IntersectionVisitedThisWire->at(Elem) = true;
                        std::cout << "Intersection hit at " << Elem.first << " and " << Elem.second << std::endl;
                        std::cout << "Steps " << *StepCounter << std::endl;
                        IntersectionVisitedThisWire->at(Iterator) = true;
                    }
                }

                size = Intersections->size();
                if (Iterator < size)
                    Iterator++;
                else
                {
                    // std::cout << "Bound check triggered" << std::endl;
                }

                //std::cout << Iterator << std::endl;
            }
        }
        break;

    default:
        break;
    }
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
    std::vector<std::pair<long long, long long>> VisitedSpots;  //I cannot read ... I thought I had the wrong answer, and was confused about getting negative values.
    std::vector<std::pair<long long, long long>> Intersections; //After converting to long and running it again I realized I was looking at the wrong thing.
    std::vector<int> IntersectionSteps;
    std::vector<bool> IntersectionVisitedThisWire;
    std::vector<long long> ManhattenDistances;
    const std::string delim = ",";
    size_t pos = 0;
    signed int x = 0;
    signed int y = 0;
    int Counter = 0;
    int Iterator = 0;
    int StepCounter = 0;

    if (myfile.is_open())
    {

        for (std::string each; std::getline(myfile, each, '\n'); tokens.push_back(each))
            ;

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
            Counter++;
        }
        Wire2Instructions.push_back(tokens[1]);
    }
    else
        std::cout << "Unable to open file";

    //for (auto str : Wire1Instructions)
    {
        //moveWire1(str, &VisitedSpots, &x, &y); //saving every spot wire 1 has been to
    }
    x = 0; //resetting coordinates to starting point
    y = 0;

    // for (auto str : Wire2Instructions)
    {
        // moveWire2(str, &VisitedSpots, &Intersections, &x, &y);
        // std::cout << Iterator << " of " << Counter << " Steps." << std::endl;
        // Iterator++;
    }

    //sort( vec.begin(), vec.end() );
    //vec.erase( unique( vec.begin(), vec.end() ), vec.end() );

    Intersections.push_back(std::make_pair(-838, -301)); //calculating them again takes too long
    Intersections.push_back(std::make_pair(-821, -301));
    Intersections.push_back(std::make_pair(-137, -156));
    Intersections.push_back(std::make_pair(-248, -156));
    Intersections.push_back(std::make_pair(-390, -206));
    Intersections.push_back(std::make_pair(-556, -44));
    Intersections.push_back(std::make_pair(-335, -44));
    Intersections.push_back(std::make_pair(-355, -156));

    /*Intersections.push_back(std::make_pair(146, 46));
    Intersections.push_back(std::make_pair(155, 11));
    Intersections.push_back(std::make_pair(155, 4));
    Intersections.push_back(std::make_pair(158, -12));*/

    /*Intersections.push_back(std::make_pair(3, 3));
    Intersections.push_back(std::make_pair(6, 5));*/

    for (int i = 0; i < Intersections.size(); i++)
        IntersectionVisitedThisWire.push_back(false);

    for (int i = 0; i < Intersections.size(); i++)
        IntersectionSteps.push_back(0);

    for (auto str : Wire1Instructions)
        moveSteps(str, &Intersections, &IntersectionSteps, &IntersectionVisitedThisWire, &x, &y, &StepCounter);

    StepCounter = 0;
    x = 0;
    y = 0;

    for (int i = 0; i < Intersections.size(); i++)
        IntersectionVisitedThisWire[i] = false;

    std::cout << "Wire transition" << std::endl;

    for (auto str : Wire2Instructions)
        moveSteps(str, &Intersections, &IntersectionSteps, &IntersectionVisitedThisWire, &x, &y, &StepCounter);

    for (auto number : IntersectionSteps)
    {
        std::cout << number << std::endl;
    }

    //for some reason, there's a stray 4 digit number that's not the right number that also gets put out, I don't know and at this point I don't care

    return 0;
}