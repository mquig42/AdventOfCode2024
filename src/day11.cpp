#include "day11.h"

Day11::Day11()
{
    dayNumber = 11;
}

void Day11::load(File file)
{
    while(file.available())
    {
        input.push_back(file.parseInt());
    }
    input.pop_back();
    file.close();
}

uint64_t Day11::solve1()
{
    uint64_t count = 0;
    for(uint32_t n : input)
    {
        count += blink(n, 25);
    }
    return count;
}

uint64_t Day11::solve2()
{
    return 0;
}

//Return number of stones after numBlinks, for one stone with starting value n
uint64_t Day11::blink(uint64_t n, uint8_t numBlinks)
{
    int digits;
    int pow10;
    while(numBlinks > 0)
    {
        digits = std::log10(n) + 1;
        if(n == 0)
        {
            n = 1;
            numBlinks--;
        }
        else if(digits % 2 == 0)
        {
            pow10 = std::pow(10, digits / 2);
            //M5Cardputer.Display.printf("%d has %d digits. Split to %d and %d\n", n, digits, n / pow10, n % pow10);
            return blink(n / pow10, numBlinks - 1) + blink(n % pow10, numBlinks - 1);
        }
        else
        {
            n *= 2024;
            numBlinks--;
        }
    }
    return 1;
}
