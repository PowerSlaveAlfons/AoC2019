

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void ComputeSeenAsteroids()
{
    return;
}

int main()
{
    std::ifstream myfile("Day10Input1.txt"); // hardcoded because lazy
    char input = 0;
    std::vector<std::vector<char>> InputArray;
    std::vector<char> Dummy;
    int IteratorX = 0;
    int IteratorY = 0;

    InputArray.push_back(Dummy);
    if (myfile.is_open())
    {
        while (myfile >> input)
        {
            InputArray.back().push_back(input);
            if (myfile.peek() == '\n')
                InputArray.push_back(Dummy);
        }
    }
    else
        std::cout << "Unable to open file";

    for (auto vec : InputArray)
    {
        for (auto ch : vec)
        {
            std::cout << ch;
            ComputeSeenAsteroids();
            IteratorY++;
        }
        IteratorY = 0;
        IteratorX++;
        std::cout << std::endl;
    }

    return 0;
}
