#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

#define SSTR(x) static_cast<std::ostringstream &>(           \
                    (std::ostringstream() << std::dec << x)) \
                    .str() // to_string is broken under my mingw installation and I can't be arsed to reinstall right now

int GetOpcode(int Input)
{

    return Input % 100;
}

bool sortbysec(const std::pair<std::vector<int>, int> &a,
               const std::pair<std::vector<int>, int> &b)
{
    return (a.second < b.second);
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

    // std::cout << "Padded Opcode: " << aux << std::endl;

    return aux;
}

std::vector<int> RunComputer(std::vector<int> Code, int PhaseSetting, int Input, bool *ExitCondition, bool PhaseSet, int Index, bool *MachineDone)
{
    //long long int Index = 0;
    long long int Opcode = 0;
    long long int CalcIndex1 = 0;
    long long int CalcIndexAux = 0;
    long long int CalcIndexResult = 0;
    long long int MemLocation = 0;
    long long int Calc1 = 0;
    long long int Calc2 = 0;
    int Output = 0;
    std::string PaddedString;

    while (Opcode != 99)
    {
        switch (Opcode)
        {
        case 1: //ADD
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

            // std::cout << "Parameters: " << Code[Index + 1] << " and " << Code[Index + 2] << " and " << Code[Index + 3] << std::endl;
            // std::cout << "Added " << Calc1 << " and " << Calc2 << " and pushed to " << CalcIndexResult << std::endl;

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

            //  std::cout << "Parameters: " << Code[Index + 1] << " and " << Code[Index + 2] << " and " << Code[Index + 3] << std::endl;
            // std::cout << "Multiplied " << Calc1 << " and " << Calc2 << " and pushed to " << CalcIndexResult << std::endl;

            Index += 4; //IP incrementing
            break;

        case 3: //IN
            PaddedString = GetPaddedString(Code[Index], 3);
            CalcIndexResult = Code[Index + 1];
            //std::cout << "Input Requested: " << std::endl;
            //std::cin >> CalcIndexAux;
            if (!PhaseSet)
            {
                PhaseSet = true;
                Code[CalcIndexResult] = PhaseSetting;
                // std::cout << "Phase setting set to " << PhaseSetting << std::endl;
            }
            else
            {
                Code[CalcIndexResult] = Input;
                //  std::cout << "Input set to " << Input << std::endl;
            }

            Index += 2;
            break;

        case 4: //OUT
            PaddedString = GetPaddedString(Code[Index], 4);
            if (PaddedString[0] == '0')
            {
                CalcIndex1 = Code[Index + 1];
                //std::cout << Code[CalcIndex1] << std::endl;
                Code.push_back(Code[CalcIndex1]);
            }
            else
            {
                std::cout << Code[Index + 1] << std::endl;
                Code.push_back(Code[Index + 1]);
            }
            Index += 2;
            Code.push_back(Index);
            return Code;

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
    *ExitCondition = true;
    *MachineDone = true;
    //std::cout << "Exit condition reached" << std::endl;
    return Code;
}

int main()
{
    std::ifstream myfile("Day7Input.txt"); // hardcoded because lazy
    int input = 0;
    std::vector<int> Code;
    std::string PaddedString;
    std::vector<int> ThrusterInput;
    std::vector<std::pair<std::vector<int>, int>> Results;
    std::vector<std::vector<int>> CodeArray; // stores the memory state of each machine
    bool ExitCondition = false;
    bool PhaseSet = false;
    int index[5] = {0};
    int Iterator = 0;
    bool MachineDone[5] = {false};

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

    for (int i = 5; i < 10; i++)
        ThrusterInput.push_back(i);
    for (int i = 0; i < 5; i++)
    {
        CodeArray.push_back(Code); // filling the table of memory states
    }
    std::cout << "CodeSize before: " << CodeArray[0].size() << std::endl;

    do
    {
        ExitCondition = false;
        CodeArray.clear(); //resetting code array for each quintet of inputs
        for (int i = 0; i < 5; i++)
        {
            CodeArray.push_back(Code);
            index[i] = 0;
            MachineDone[i] = false;
        }
        PhaseSet = false;
        //std::cout << "iteration" << std::endl;
        input = 0;
        while (true)
        {
            Iterator = 0;
            for (int i : ThrusterInput)
            {
                //std::cout << Iterator << std::endl;
                if (!MachineDone[Iterator])
                {
                    CodeArray[Iterator] = RunComputer(CodeArray[Iterator], i, input, &ExitCondition, PhaseSet, index[Iterator], &MachineDone[Iterator]);
                    index[Iterator] = CodeArray[Iterator].back(); // getting the IP from CodeArray at Iterator into the IPArray at Iterator
                    CodeArray[Iterator].pop_back();               // throwing the IP out
                    if (!MachineDone[Iterator]) // mistake at first, need to actually halt the damn machine, and not just pop random values out of the codearray if it's not an output, but just a halt
                    {
                        input = CodeArray[Iterator].back(); // getting the output which in turn becomes the next input
                        CodeArray[Iterator].pop_back();     // throwing the output out
                    }
                }
                Iterator++;
            }
            PhaseSet = true;
            if (ExitCondition)
                break;
        }
        Results.push_back(std::make_pair(ThrusterInput, input));
        std::cout << input << std::endl;

    } while (std::next_permutation(ThrusterInput.begin(), ThrusterInput.end()));

    sort(Results.begin(), Results.end(), sortbysec);
    std::cout << Results.back().second << std::endl;
    std::cout << "Given by ";
    for (auto i : Results.back().first)
    {
        std::cout << i << " ";
    }

    return 0;
}