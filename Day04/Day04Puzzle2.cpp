#include <iostream>
#include <string>

int main()
{
    static const int RangeStart = 387638;
    static const int RangeEnd = 919123;
    bool islegal = true;
    bool inStreak = false;
    bool DubsConfirmed = false;
    bool SinkingDigit = false;
    int dubs = 0;
    int Counter = 0;
    std::string Converted;
    char last;
    char beforelast;
    int DubCounter = 0;
    int StreakCounter = 0;

    for (int Input = RangeStart; Input < RangeEnd; Input++) // this could be severely simplified, but hey, it works
    {
        islegal = true;
        DubCounter = 0;
        Converted = std::to_string(Input);
        dubs = false;
        last = '!';
        beforelast = '!';
        dubs = 0;
        DubsConfirmed = false;
        inStreak = false;
        SinkingDigit = false;
        StreakCounter = 0;
        for (char c : Converted)
        {
            if (c == last)
            {
                if (!inStreak)
                {
                    dubs++;
                    inStreak = true;
                    StreakCounter++;
                }
                else
                {
                    dubs = 0;
                    StreakCounter++;
                }
            }
            else
            {   
                inStreak = false;
                if (StreakCounter == 1)
                    DubsConfirmed = true;
                StreakCounter = 0;
            }
            if (c < last)
                SinkingDigit = true;
            last = c;
        }
        if (dubs < 1)
            islegal = false;

        if (DubsConfirmed)
            islegal = true;
        
        if (SinkingDigit)
            islegal = false;

        if (islegal)
        {
            Counter++;
            std::cout << Input << std::endl;
        }
    }

    std::cout << Counter << " candidates found" << std::endl;
}
