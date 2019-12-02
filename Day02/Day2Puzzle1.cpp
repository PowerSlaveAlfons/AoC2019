#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main()
{
	std::ifstream myfile("Day2Input.txt"); // hardcoded because lazy
    int input = 0;
    int Index = 0;
    int Opcode = 0;
    int CalcIndex1 = 0;
    int CalcIndex2 = 0;
    int CalcIndexAux = 0;
    int CalcIndexResult = 0;
    std::vector<int> Code;

	if (myfile.is_open())
	{
		while (myfile >> input)
		{
			if (myfile.peek() == ',')
                myfile.ignore();
            Code.push_back(input);
		}
	}   
	else std::cout << "Unable to open file";

    Code[1] = 12; //busywork for whatever reason
    Code[2] = 2;


    while (Opcode != 99)
    {
        switch (Opcode)
        {
            case 1:
                CalcIndex1 = Code[Index+1];
                CalcIndex2 = Code[Index+2];
                CalcIndexResult = Code[Index+3];
                CalcIndexAux = Code[CalcIndex1] + Code[CalcIndex2];
                Code[CalcIndexResult] = CalcIndexAux;
                Index += 4;
                break;

            case 2:
                CalcIndex1 = Code[Index+1];
                CalcIndex2 = Code[Index+2];
                CalcIndexResult = Code[Index+3];
                CalcIndexAux = Code[CalcIndex1] * Code[CalcIndex2];
                Code[CalcIndexResult] = CalcIndexAux;
                Index += 4;
                break;
        
            default:
                break;
        }

        Opcode = Code[Index];
        //std::cout << Opcode << std::endl;
    }
        //for (int i : Code)
        std::cout << Code[0] << std::endl;


	return 0;
}