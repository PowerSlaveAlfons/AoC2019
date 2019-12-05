#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

#define SSTR(x) static_cast<std::ostringstream &>(           \
                    (std::ostringstream() << std::dec << x)) \
                    .str() // to_string is broken under my mingw installation and I can't be arsed to reinstall right now

int GetOpcode(int Input)
{

    return Input % 100;
}

std::string GetPaddedString(int Input, int Opcode)
{
    std::string aux = SSTR(Input);
    switch (Opcode)
    {
    case 1:
    case 2:
        while (aux.length() < 5)
            aux = "0" + aux;
        break;
    case 3:
    case 4:
        while (aux.length() < 3)
            aux = "0" + aux;
        break;

    default:
        break;
    }

    //std::cout << "Padded Opcode: " << aux << std::endl;

    return aux;
}

int main()
{
    std::ifstream myfile("Day5Input.txt"); // hardcoded because lazy
    long long int input = 0;
    long long int Index = 0;
    long long int Opcode = 0;
    long long int CalcIndex1 = 0;
    long long int CalcIndex2 = 0;
    long long int CalcIndexAux = 0;
    long long int CalcIndexResult = 0;
    long long int MemLocation = 0;
    long long int OpInput = 0;
    long long int Calc1 = 0;
    long long int Calc2 = 0;
    std::vector<int> Code;
    std::string PaddedString;

    //Code.push_back(1);

    if (myfile.is_open())
    {
        while (myfile >> input)
        {
            if (myfile.peek() == ',')
                myfile.ignore();
            Code.push_back(input);
        }
    }
    else
        std::cout << "Unable to open file";

    while (Opcode != 99)
    {
        switch (Opcode)
        {
        case 1:
            PaddedString = GetPaddedString(Code[Index], 1);
           // std::cout << PaddedString[2] << std::endl;
            if (PaddedString[2] == '1') //Param 1
            {
                Calc1 = Code[Index + 1];
              //  std::cout << "Calc1: " << Calc1 << std::endl;
            }
            else
            {
                MemLocation = Code[Index + 1];
                Calc1 = Code[MemLocation];
            }

            if (PaddedString[1] == '1') //Param 2
                Calc2 = Code[Index + 2];
            else
            {
                MemLocation = Code[Index + 2];
                Calc2 = Code[MemLocation];
            }
            CalcIndexResult = Code[Index + 3]; //Param 3, can't be immediate

            CalcIndexAux = Calc1 + Calc2;
            Code[CalcIndexResult] = CalcIndexAux;

         //   std::cout << "Parameters: " << Code[Index + 1] << " and " << Code[Index + 2] << " and " << Code[Index + 3] << std::endl;
         //   std::cout << "Added " << Calc1 << " and " << Calc2 << " and pushed to " << CalcIndexResult << std::endl;

            Index += 4; //IP incrementing
            break;

        case 2:
            PaddedString = GetPaddedString(Code[Index], 2);
            if (PaddedString[2] == '1') //Param 1
            {
                Calc1 = Code[Index + 1];
            }
            else
            {
                MemLocation = Code[Index + 1];
                Calc1 = Code[MemLocation];
            }

            if (PaddedString[1] == '1') //Param 2
                Calc2 = Code[Index + 2];
            else
            {
                MemLocation = Code[Index + 2];
                Calc2 = Code[MemLocation];
            }
            CalcIndexResult = Code[Index + 3]; //Param 3, can't be immediate

            CalcIndexAux = Calc1 * Calc2;
            Code[CalcIndexResult] = CalcIndexAux;

          //  std::cout << "Parameters: " << Code[Index + 1] << " and " << Code[Index + 2] << " and " << Code[Index + 3] << std::endl;
           // std::cout << "Multiplied " << Calc1 << " and " << Calc2 << " and pushed to " << CalcIndexResult << std::endl;

            Index += 4; //IP incrementing
            break;

        case 3:
            PaddedString = GetPaddedString(Code[Index], 3);
            CalcIndexResult = Code[Index + 1];
            std::cout << "Input Requested: " << std::endl;
            std::cin >> CalcIndexAux;
            Code[CalcIndexResult] = CalcIndexAux;
            Index += 2;
            break;

        case 4:
            PaddedString = GetPaddedString(Code[Index], 4);
            if (PaddedString[0] == '0')
            {
                CalcIndex1 = Code[Index + 1];
                std::cout << Code[CalcIndex1] << std::endl;
            }
            else
                std::cout << Code[Index + 1] << std::endl;

            Index += 2;
            break;

        default:
            break;
        }

        Opcode = GetOpcode(Code[Index]);
    }


    return 0;
}