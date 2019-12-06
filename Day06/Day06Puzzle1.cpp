

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Planet
{
  public:
    std::string name;
    std::string orbits;
    Planet *OrbitedPlanet = nullptr;

    Planet(std::string NameIn, std::string Other)
    {
        this->name = NameIn;

        this->orbits = Other;
       // for (auto Plan : *Vec)
       // {
       //     
       // }
    }
};

int main()
{
    std::ifstream myfile("Day6Input.txt"); // hardcoded because lazy
    std::string input = "";
    int counter = 0;
    std::vector<Planet *> Planets;
    std::string delimiter = ")";
    std::string Name;
    std::string Orbited;

    Planets.push_back(new Planet("COM", ""));

    if (myfile.is_open())
    {
        while (myfile >> input)
        {
            Orbited = input.substr(0, input.find(delimiter));
            input.erase(0, input.find(delimiter) + delimiter.length());
            Name = input;
            Planets.push_back(new Planet(Name, Orbited));
            std::cout << "Planet created with name " << Name << " and base " << Orbited << std::endl;
        }
    }
    else
        std::cout << "Unable to open file";

    std::cout << "VectorSize: " << Planets.size() << std::endl;

    for (auto Plan : Planets)
    {
        for (auto Other : Planets)
        {
            if (Plan->orbits == Other->name)
                Plan->OrbitedPlanet = Other;
        }
    }

    for (auto Planet : Planets)
    {
        while (Planet->OrbitedPlanet != nullptr)
            {
               // std::cout << "Planet connection" << Planet->name << " " << Planet->OrbitedPlanet->name << std::endl;
                Planet = Planet->OrbitedPlanet;
                counter++;
                
            }
            //std::cout << std::endl;
    }

    std::cout << counter;
    return 0;
}
