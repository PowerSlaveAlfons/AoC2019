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
    case 1:                      //ADD
    case 2:                      //MUL
    case 7:                      //LESS
    case 8:                      //EQUALS
        while (aux.length() < 5) //3 Params
            aux = "0" + aux;
        break;
    case 3:                      //IN
    case 4:                      //OUT
        while (aux.length() < 3) //1 Param
            aux = "0" + aux;
        break;
    case 5:                      //JNZ
    case 6:                      //JIZ
        while (aux.length() < 4) //2 Params
            aux = "0" + aux;
        break;

    default:
        break;
    }

    std::cout << "Padded Opcode: " << aux << std::endl;

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
        case 1: //ADD
            PaddedString = GetPaddedString(Code[Index], 1);
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

            CalcIndexAux = Calc1 + Calc2;
            Code[CalcIndexResult] = CalcIndexAux;

            Index += 4; //IP incrementing
            break;

        case 2: //MUL
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
            Index += 4; //IP incrementing
            break;

        case 3: //IN
            PaddedString = GetPaddedString(Code[Index], 3);
            CalcIndexResult = Code[Index + 1];
            std::cout << "Input Requested: " << std::endl;
            std::cin >> CalcIndexAux;
            Code[CalcIndexResult] = CalcIndexAux;
            Index += 2;
            std::cout << "Memes" << std::endl;
            break;

        case 4: //OUT
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

        case 5: //JNZ
            PaddedString = GetPaddedString(Code[Index], 5);
            if (PaddedString[1] == '1') //Param 1
                Calc1 = Code[Index + 1];
            else
            {
                MemLocation = Code[Index + 1];
                Calc1 = Code[MemLocation];
            }
            if (PaddedString[0] == '1') //Param 2
                Calc2 = Code[Index + 2];
            else
            {
                MemLocation = Code[Index + 2];
                Calc2 = Code[MemLocation];
            }
            if (Calc1 == 0)
            {
                Index += 3;
                break;
            }
            else
            {
                Index = Calc2;
                break;
            }

        case 6: //JIZ
            PaddedString = GetPaddedString(Code[Index], 6);

            if (PaddedString[1] == '1') //Param 1
                Calc1 = Code[Index + 1];
            else
            {
                MemLocation = Code[Index + 1];
                Calc1 = Code[MemLocation];
            }
             if (PaddedString[0] == '1') //Param 2
                Calc2 = Code[Index + 2];
            else
            {
                MemLocation = Code[Index + 2];
                Calc2 = Code[MemLocation];
            }
            if (Calc1 != 0)
            {
                Index += 3;
                break;
            }
            else
            {
                Index = Calc2; //Param 2
                break;
            }

        case 7: //LESS
            PaddedString = GetPaddedString(Code[Index], 7);
            if (PaddedString[2] == '1') //Param 1
            {
                Calc1 = Code[Index + 1];
            }
            else
            {
                MemLocation = Code[Index + 1];
                Calc1 = Code[MemLocation];
            }
            CalcIndexResult = Code[Index + 3];

            if (PaddedString[1] == '1') //Param 2
                Calc2 = Code[Index + 2];
            else
            {
                MemLocation = Code[Index + 2];
                Calc2 = Code[MemLocation];
            }
            if (Calc1 < Calc2)
                Code[CalcIndexResult] = 1;
            else
                Code[CalcIndexResult] = 0;

            Index += 4;
            break;

        case 8: //EQUALS
            PaddedString = GetPaddedString(Code[Index], 7);
            if (PaddedString[2] == '1') //Param 1
            {
                Calc1 = Code[Index + 1];
            }
            else
            {
                MemLocation = Code[Index + 1];
                Calc1 = Code[MemLocation];
            }
            CalcIndexResult = Code[Index + 3];

            if (PaddedString[1] == '1') //Param 2
                Calc2 = Code[Index + 2];
            else
            {
                MemLocation = Code[Index + 2];
                Calc2 = Code[MemLocation];
            }
            if (Calc1 == Calc2)
                Code[CalcIndexResult] = 1;
            else
                Code[CalcIndexResult] = 0;

            Index += 4;
            break;

        default:
            break;
        }

        Opcode = GetOpcode(Code[Index]);
    }
    std::cout << "done" << std::endl;

    return 0;
}