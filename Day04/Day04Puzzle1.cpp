#include <iostream>
#include <string>

int main ()
{
    static const int RangeStart = 387638;
    static const int RangeEnd = 919123;
    bool islegal = true;
    bool dubs = false;
    int Counter = 0;
    std::string Converted;
    char last;
    
    for (int Input = RangeStart; Input < RangeEnd; Input++)
    {
        islegal = true;
        Converted = std::to_string(Input);
        dubs = false;
        last = '!';
        for (char c : Converted)
        {
            if (c == last)
                dubs = true;
            if (c < last)
                islegal = false;

            last = c;
        }
        if (dubs == false)
            islegal = false;

        if (islegal)
            Counter++;
    }

    std::cout << Counter << " candidates found" << std::endl;
}