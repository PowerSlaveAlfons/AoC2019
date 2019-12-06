

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
    std::vector<Planet *> OrbitingPlanets;
    bool visited = false;

    Planet(std::string NameIn, std::string Other)
    {
        this->name = NameIn;
        this->orbits = Other;
    }
};

bool SearchFromRoot(Planet *root, std::vector<std::string> &Path, std::string goal) // THank you very much google for this solution
{
    Path.push_back(root->name);
    if (root->name == goal)
        return true;

    for (auto Planet : root->OrbitingPlanets)
    {
        if (SearchFromRoot(Planet, Path, goal))
            return true;
    }
    Path.pop_back();
    return false;
}

int PrintPathBetweenPlanet(Planet *root, std::string source, std::string destination)
{
    std::vector<std::string> path1;
    std::vector<std::string> path2;
    int counter = 0;

    SearchFromRoot(root, path1, source);
    SearchFromRoot(root, path2, destination);

    int intersection = -1;
    int i = 0, j = 0;
    while (i != path1.size() || j != path2.size())
    {
        if (i == j && path1[i] == path2[j])
        {
            i++;
            j++;
        }
        else
        {
            intersection = j - 1;
            break;
        }
    }
    for (int i = path1.size() - 1; i > intersection; i--)
    {
        std::cout << path1[i] << " ";
        counter++;
    }

    for (int i = intersection; i < path2.size(); i++)
    {
        std::cout << path2[i] << " ";
        counter++;
    }

    return counter - 3;
}

int main()
{
    std::ifstream myfile("Day6Input.txt"); // hardcoded because lazy
    std::string input = "";
    int counter = 0;
    int JumpCounter = 0;
    std::vector<Planet *> Planets;
    std::string delimiter = ")";
    std::string Name;
    std::string Orbited;
    Planet *source;
    bool found = false;
    std::vector<bool> Visited;

    Planets.push_back(new Planet("COM", ""));

    if (myfile.is_open())
    {
        while (myfile >> input)
        {
            Orbited = input.substr(0, input.find(delimiter));
            input.erase(0, input.find(delimiter) + delimiter.length());
            Name = input;
            Planets.push_back(new Planet(Name, Orbited));
          //  std::cout << "Planet created with name " << Name << " and base " << Orbited << std::endl;
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
            {
                Other->OrbitingPlanets.push_back(Plan);
                Plan->OrbitedPlanet = Other;
            }
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

   /* for (auto Planet : Planets)
    {
        std::cout << "Planet " << Planet->name << " is orbitted by ";
        for (auto Plano : Planet->OrbitingPlanets)
            std::cout << Plano->name << " ";
        std::cout << std::endl;
    } */

    for (auto Planet : Planets)
    {
        if (Planet->name == "YOU")
            source = Planet;
    }

    //JumpCounter = Search("SAN", source, &JumpCounter);
    counter = PrintPathBetweenPlanet(Planets[0], "YOU", "SAN");
    std::cout << counter << std::endl;
    return 0;
}
