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
        this->values[IteratorX][IteratorY] = Digit;
        IteratorX++;
        if (IteratorX > 5)
        {
            IteratorX = 0;
            IteratorY++;
        }
        if (IteratorY > 24)
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
    int Index = 0;
    int Counter = 0;
    int CounterOnes = 0;
    int CounterTwos = 0;
    std::vector<std::pair<int, int>> Results;


    if (myfile.is_open())
    {
        while (myfile >> input)
        {
        }
    }
        else std::cout << "Unable to open file";

    for (auto cha : input)
    {
        if (!Layerino->addDigit(cha))
        {
            Picture->Layers.push_back(*Layerino);
            delete Layerino;
            Layerino = new Layer();
        }
    }   
    //std::cout << Picture->Layers.size();

    for (auto Lay : Picture->Layers)
    {
        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (Lay.values[j][i] == '0')
                    Counter++;
            }

        }
        Results.push_back(std::make_pair(Index, Counter));
        Counter = 0;
        Index++;
    }

    sort(Results.begin(), Results.end(), sortbysec);

    Layer Lay = Picture->Layers[Results[0].first];
    for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (Lay.values[j][i] == '1')
                    CounterOnes++;
                if (Lay.values[j][i] == '2')
                    CounterTwos++;
            }

        }
        
    std::cout << (CounterOnes * CounterTwos) << std::endl;

    return 0;
}
