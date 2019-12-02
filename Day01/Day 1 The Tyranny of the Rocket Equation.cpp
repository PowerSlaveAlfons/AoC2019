

#include <iostream>
#include <fstream>
#include <string>

void getFuel(int *input, int *output) // recursive function to get the fuel for the fuel (for the fuel for the fuel ...)
{
	int aux = 0;
	if (*input < 6)
	{ 	
		return;
	}

	else
	{
		aux = *input / 3;
		aux -= 2;
		*output += aux;
		*input = aux;
		getFuel(input, output);
	}
}

int main()
{
    std::cout << "Hello World!\n";
	std::ifstream myfile("Day1Input.txt"); // hardcoded because lazy
	int input = 0;
	int auxInput = 0;
	int FuelFuel = 0;
	int FuelSum = 0;
	if (myfile.is_open())
	{
		while (myfile >> input)
		{
			FuelFuel = 0;
			auxInput = input / 3;
			auxInput -= 2;
			FuelSum += auxInput; 
			getFuel(&auxInput, &FuelFuel); // in order to solve Puzzle 1, just remove this call and the next line
			FuelSum += FuelFuel;
		}
	}
	else std::cout << "Unable to open file";

	std::cout << FuelSum;
	return 0;
}

