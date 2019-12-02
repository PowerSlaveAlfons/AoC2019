#include <fstream>
#include <string>
#include <iostream>
#include <vector>

std::vector<int> GetResultFromInputs(int a, int b, std::vector<int> Code)
{
    int Index = 0;
    int Opcode = 0;
    int CalcIndex1 = 0;
    int CalcIndex2 = 0;
    int CalcIndexAux = 0;
    int CalcIndexResult = 0;

    Code[1] = a; //this is the input for the Computer
    Code[2] = b;


    while (Opcode != 99)
    {
        switch (Opcode)
        {
            case 1: // this can be done prettier, but eh, it works
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
        //std::cout << Code[0] << std::endl;
        return Code;

}

int main()
{
	std::ifstream myfile("Day2Input.txt"); // hardcoded because lazy
    int input = 0;

    std::vector<int> Code;
    std::vector<int> OriginalCode;

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

    OriginalCode = Code;

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            Code = GetResultFromInputs(i,j, Code);
            if (Code[0] == 19690720)
            {
                std::cout << "Result found, inputs are:" << i << " " << j << std::endl;
                std::cout << "Answer:" << (100*i+j);
                return 0;
            }
            //std::cout << "Calculating for i, j: " << i << " " << j << "done, moving on" << std::endl;

            Code = OriginalCode;
        }
    }


	return 0;
}