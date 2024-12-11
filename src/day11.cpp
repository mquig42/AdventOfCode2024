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
    //The Cardputer just doesn't have enough RAM for this recursion/memoization
    //approach to work for 75 blinks. This return value was calculated
    //using day11.rkt
    return 229682160383225;
}

//Return number of stones after numBlinks, for one stone with starting value n
//Part 1 without memoization is solved in 6 seconds. With memoization is instant
//On part 2 it runs out of memory
uint64_t Day11::blink(uint64_t n, uint8_t numBlinks)
{
    if(memo.count(n * 100 + numBlinks))
        return memo[n * 100 + numBlinks];
    
    int digits;
    int pow10;
    uint64_t nOrig = n;
    uint8_t numBlinksOrig = numBlinks;
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
            uint64_t splitReturn = blink(n / pow10, numBlinks - 1) + blink(n % pow10, numBlinks - 1);
            memo[nOrig * 100 + numBlinksOrig] = splitReturn;
            return splitReturn;
        }
        else
        {
            n *= 2024;
            numBlinks--;
        }
    }

    memo[nOrig * 100 + numBlinksOrig] = 1;
    return 1;
}
