#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Layer
{

private:
    int IteratorX = 0;
    int IteratorY = 0;

public:
    char values[6][25] = {'0'};
    Layer(){

    };

    bool addDigit(char Digit)
    {
        this->values[IteratorY][IteratorX] = Digit;
        IteratorX++;
        if (IteratorX > 24)
        {
            IteratorX = 0;
            IteratorY++;
        }
        if (IteratorY > 5)
        {
            return false;
        }
        return true;
    }
};

class Image
{
public:
    std::vector<Layer> Layers;
};

bool sortbysec(const std::pair<int, int> &a,
               const std::pair<int, int> &b)
{
    return (a.second < b.second);
}

int main()
{
    std::ifstream myfile("Day8Input.txt"); // hardcoded because lazy
    std::string input = "";
    Image *Picture = new Image();
    Layer *Layerino = new Layer();
    std::vector<int> DigitsPerLayer;
    std::vector<std::pair<int, int>> Results;
    bool Visible[6][25] = {false};
    char VisibilePicture[6][25] = {'3'};

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 25; j++)
            VisibilePicture[i][j] = '3';

    if (myfile.is_open())
    {
        while (myfile >> input)
        {
        }
    }
    else
        std::cout << "Unable to open file";

    for (auto cha : input)
    {
        if (!Layerino->addDigit(cha))
        {
            Picture->Layers.push_back(*Layerino);
            delete Layerino;
            Layerino = new Layer();
        }
    }

    for (auto Lay : Picture->Layers)
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 25; j++)
            {
                if (!Visible[i][j])
                {
                    switch (Lay.values[i][j])
                    {
                    case '0':
                        VisibilePicture[i][j] = 'x';
                        Visible[i][j] = true;
                        break;
                    case '1':
                        VisibilePicture[i][j] = '-';
                        Visible[i][j] = true;
                        break;
                    case '2':
                        break;

                    default:
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            std::cout << VisibilePicture[i][j]; // THank you, mspaint, for making me able to read that message, holy shit, that was more difficult than it needed to be
        }
        std::cout << std::endl;
    }

    return 0;
}
