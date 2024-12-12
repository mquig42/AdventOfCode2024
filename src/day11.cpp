#include "day11.h"

Day11::Day11()
{
    dayNumber = 11;
}

void Day11::load(File file)
{
    long n = 0;
    String line = file.readStringUntil('\n');
    for(char c : line)
    {
        if(c >= '0' && c <= '9')
        {
            n = n * 10 + c - '0';
        }
        else
        {
            increaseCount(counts, n, 1);
            n = 0;
        }
    }
    file.close();
}

uint64_t Day11::solve1()
{
    uint64_t sum = 0;

    for(int i = 0; i < 25; i++)
        blink();

    for(auto i : counts)
        sum += i.second;
    
    return sum;
}

//This gets up as far as 54 blinks, and counts grows slowly
//Further optimization might get it to 75
uint64_t Day11::solve2()
{
    uint64_t sum = 0;

    for(int i = 0; i < 50; i++)
        blink();

    for(auto i : counts)
        sum += i.second;
    
    return sum;
}

//Updates counts by one blink
//I'm storing a count of each distinct value. This is what I should have done from the beginning,
//since the first thing I thought after reading the description was "lanternfish"
void Day11::blink()
{
    std::unordered_map<uint64_t, uint32_t> newCounts;
    int digits, pow10;;
    for(auto i : counts)
    {
        digits = std::log10(i.first) + 1;
        if(i.first == 0)
        {
            increaseCount(newCounts, 1, i.second);
        }
        else if(digits % 2 == 0)
        {
            pow10 = std::pow(10, digits / 2);
            increaseCount(newCounts, i.first / pow10, i.second);
            increaseCount(newCounts, i.first % pow10, i.second);
        }
        else
        {
            increaseCount(newCounts, i.first * 2024, i.second);
        }
    }

    counts.clear();
    counts = newCounts;
}

void Day11::increaseCount(std::unordered_map<uint64_t, uint32_t> &c, uint64_t key, uint32_t value)
{
    if(c.count(key))
        c[key] += value;
    else
        c[key] = value;
}
